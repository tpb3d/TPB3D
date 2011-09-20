// Copyright (C) 2008 James P Michels III
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Diagnostics;
using System.IO;

using OpenTK.Graphics;
using OpenTK;
using OpenTK.Input;

using OOGL;
using OOGL.Shaders;
using OOGL.GUI.VertexStructures;

namespace OOGL.GUI.Abstract
{
    public abstract class BaseFrame : BaseControl, IDisposable
    {
        private static readonly Point nullLocation = new Point(int.MinValue, int.MinValue);

        private Rectangle titleRectangle = new Rectangle(0, 0, 0, 0);

        private Point moveMouseStart = nullLocation;
        private Point moveFrameStart;
        private Point sizeMouseStart = nullLocation;
        private Size sizeFrameStart;

		private FrameBuffer frameBuffer;

        private PositionTexture[] frameBufferQuad = new PositionTexture[4];
        private bool update = true;

        public BaseFrame(BaseFrameMgr frameMgr, byte windowType, string name)
            : base(frameMgr, null)
        {
            this.frameMgr = frameMgr;
            this.windowType = windowType;
            this.name = name;

            TitleColor = BorderColor;

            this.titleFont = frameMgr.TitleBarFont;

            this.frameMgr.AddWindow(this);            
        }

        public virtual void Dispose()
        {
            if (frameBuffer != null) frameBuffer.Dispose();
        }

        private string GetSettingFile(string workspacePath)
        {
            return string.Format(@"{0}{1}{2}.window.ini", workspacePath, Path.DirectorySeparatorChar, name);
        }

        public void LoadSettings(string workspacePath)
        {
            Dictionary<string, string> settings = new Dictionary<string, string>();
            using (FileStream file = File.OpenRead(GetSettingFile(workspacePath)))
            {
                using (StreamReader r = new StreamReader(file))
                {
                    string line;
                    while ((line = r.ReadLine()) != null)
                    {
                        string[] rows = line.Split('=');
                        if (rows != null && rows.Length == 2)
                        {
                            settings[rows[0].Trim()] = rows[1].Trim();
                        }
                    }
                }
            }

            int x = int.Parse(settings["X"]);
            int y = int.Parse(settings["Y"]);
            int height = int.Parse(settings["Height"]);
            int width = int.Parse(settings["Width"]);

            Location = new Point(x, y);
            Size = new Size(width, height);
        }

        public void SaveSettings(string workspacePath)
        {
            using (FileStream file = File.Create(GetSettingFile(workspacePath)))
            {
                using (StreamWriter w = new StreamWriter(file))
                {
                    w.WriteLine(string.Format("X={0}", X));
                    w.WriteLine(string.Format("Y={0}", Y));
                    w.WriteLine(string.Format("Height={0}", Height));
                    w.WriteLine(string.Format("Width={0}", Width));
                }
            }
        }

        public virtual void ScaleScreenSize(Size oldSize, Size newSize)
        {
        	this.NeedUpdate();
        	
//            const int oneHundred = 10000;
//            const int ninty = 9000;
//            const int nintyNine = 9900;
//            const int one = 100;
//
//            Rectangle normalized = new Rectangle();
//            normalized.X = Location.X * oneHundred / oldSize.Width;
//            if (normalized.X < 0) normalized.X = 0;
//            if (normalized.X > nintyNine) normalized.X = nintyNine;
//
//            normalized.Width = Size.Width * oneHundred / oldSize.Width;
//            if (normalized.Width < one) normalized.Width = one;
//            if (normalized.Width >= ninty) normalized.Width = ninty;
//
//            normalized.Y = Location.Y * oneHundred / oldSize.Height;
//            if (normalized.Y < one) normalized.Y = one;
//            if (normalized.Y > nintyNine) normalized.Y = nintyNine;
//
//            normalized.Height = Size.Height * oneHundred / oldSize.Height;
//            if (normalized.Height < one) normalized.Height = one;
//            if (normalized.Height > nintyNine) normalized.Height = nintyNine;
//
//            Location = new Point(newSize.Width * normalized.X / oneHundred, newSize.Height * normalized.Y / oneHundred);
//            Size = new Size(newSize.Width * normalized.Width / oneHundred, newSize.Height * normalized.Height / oneHundred);
        }

        public override void NeedUpdate()
        {
            this.update = true;
        }

        protected readonly byte windowType;
        public byte WindowType
        {
            get
            {
                return this.windowType;
            }
        }

        protected readonly string name;
        public string Name
        {
            get
            {
                return this.name;
            }
        }

        private string text;
        public string Text
        {
            get
            {
                return text;
            }
            set
            {
                text = value;
                NeedUpdate();
            }
        }

        private Font titleFont;
        public Font TitleFont
        {
            get
            {
                return titleFont;
            }
            set
            {
                titleFont = value;
                NeedUpdate();
            }
        }

        private Color titleColor = Color.SteelBlue;
        public Color TitleColor
        {
            get
            {
                return titleColor;
            }
            set
            {
                titleColor = value;
                NeedUpdate();
            }
        }

        public override BaseFrame Frame
        {
        	get
	        {
	        	return this;
	        }
        }
        
        protected Matrix4 modelViewProjection = Matrix4.Identity;
        public Matrix4 ModelViewProjection
        {
        	get
        	{
        		return modelViewProjection;
        	}
        }

        public override Size Size
        {
            get
            {
                return base.Size;
            }
            set
            {
                if (value.Height > frameMgr.MaxWindowSize.Height) value.Height = frameMgr.MaxWindowSize.Height;
                if (value.Width > frameMgr.MaxWindowSize.Width) value.Width = frameMgr.MaxWindowSize.Width;

                base.Size = value;
                NeedUpdate();
            }
        }

        public override bool OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle screenControlRect = ClientToScreen(controlRectangle);
            Rectangle screenTitleBar = ControlToScreen(titleRectangle);

            if (screenControlRect.Contains(e.X, e.Y) == false && screenTitleBar.Contains(e.X, e.Y) == false) return false;

            Rectangle screenSizeBar = screenControlRect;
            screenSizeBar.X = screenControlRect.Right - 10;
            screenSizeBar.Width = 10;
            screenSizeBar.Y = screenControlRect.Bottom - 10;
            screenSizeBar.Height = 10;
            
            if (screenTitleBar.Contains(e.X, e.Y))
            {
                moveMouseStart = new Point(e.X, e.Y);
                moveFrameStart = Location;
                frameMgr.FocusedControl = this;
                return true;
            }

            if (screenSizeBar.Contains(e.X, e.Y))
            {
                sizeMouseStart = new Point(e.X, e.Y);
                sizeFrameStart = Size;
                frameMgr.FocusedControl = this;
                return true;
            }

            base.OnMouseDown(sender, e);

            return true;
        }

        public override void OnMouseUp(object sender, MouseButtonEventArgs e)
        {

            if (moveMouseStart != nullLocation)
            {
                moveMouseStart = nullLocation;
            }

            if (sizeMouseStart != nullLocation)
            {
                sizeMouseStart = nullLocation;
            }

            base.OnMouseUp(sender, e);
        }

        public override void OnMouseMove(object sender, MouseMoveEventArgs e)
        {
            if (moveMouseStart != nullLocation)
            {
                Location = new Point(moveFrameStart.X + e.X - moveMouseStart.X, moveFrameStart.Y + e.Y - moveMouseStart.Y);
            }

            if (sizeMouseStart != nullLocation)
            {
                Size = new Size(sizeFrameStart.Width + e.X - sizeMouseStart.X, sizeFrameStart.Height + e.Y - sizeMouseStart.Y);
            }
        }

        public override Rectangle ScreenToFrame(Rectangle childRectangle)
        {
            childRectangle.Offset(-titleRectangle.X, -titleRectangle.Y);
            return childRectangle;
        }

        public virtual void Update(double gameTime)
        {
            if (update == false) return;
            update = false;

            UpdateTitleRect();
            UpdateFrameBuffer();

            try
            {
            	frameBuffer.Use();

				GL.ClearColor(0, 255 , 0 , 0);
				GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
				GL.Disable(EnableCap.DepthTest);				
				
				GL.MatrixMode(MatrixMode.Projection);
				GL.LoadMatrix(OOGL.Matrix4Helper.ToOpenGL(Matrix4Helper.CreateOrthographicProjection(0, frameBuffer.width, 0, frameBuffer.height, 0, 1)));

				GL.MatrixMode(MatrixMode.Modelview);
				GL.LoadMatrix(OOGL.Matrix4Helper.ToOpenGL(Matrix4.Identity));

                GL.ActiveTexture(TextureUnit.Texture0);
                GL.Enable(EnableCap.Texture2D);

                DrawToFrameBuffer(gameTime);
                
                GL.Enable(EnableCap.DepthTest);
            }
            finally
            {
            	FrameBuffer.UseDefault(FrameMgr.GameWindow.Width, FrameMgr.GameWindow.Height);
            }
        }

        private void UpdateTitleRect()
		{
			RectangleF extent = frameMgr.textPrinter.Measure(text, titleFont).BoundingBox; 
			if (extent.Height == 0 || extent.Width == 0 || String.IsNullOrEmpty(text))
            {
				extent.Width = 20;
				extent.Height = 10;
            }
            else
            {
                extent.Width = extent.Width * (text.Length + 1) / text.Length;
            }

            titleRectangle.Width = (int)extent.Width + 6;
            titleRectangle.Height = (int)extent.Height + 2;
            if (titleRectangle.Width > Width)
            {
                titleRectangle.Width = 0;
                titleRectangle.Height = 0;
            }
            titleRectangle.X = controlRectangle.X;
            titleRectangle.Y = controlRectangle.Y - titleRectangle.Height;
        }

        private void UpdateFrameBuffer()
        {
            int texWidth = Width + 1;
            int texHeight = Height + titleRectangle.Height + 1;
            
            if(Extentions.IsAvailable(Extentions.ArbTextureNonPowerOfTwo) == false)
            {
                texWidth = (int)Math.Pow(2, Math.Ceiling(Math.Log(texWidth, 2)));
                texHeight = (int)Math.Pow(2, Math.Ceiling(Math.Log(texHeight, 2)));
            }

			int maxTextureSize;
			GL.GetInteger(GetPName.MaxTextureSize, out maxTextureSize);

            if (texWidth > maxTextureSize) texWidth = maxTextureSize;
            if (texHeight > maxTextureSize) texHeight = maxTextureSize;

			bool requiresSquareTexture = false; //TODO Find the proper cap to test.
            if (requiresSquareTexture)
            {
                texWidth = texHeight = Math.Max(texWidth, texHeight);
            }
            
            if (frameBuffer == null || frameBuffer.width != texWidth || frameBuffer.height != texHeight)
            {
            	SafeDispose<FrameBuffer>(ref frameBuffer);
               	frameBuffer = new FrameBuffer(texWidth, texHeight);
            	modelViewProjection = Matrix4Helper.CreateOrthographicProjection(0, texWidth, 0, texHeight, 0, 1);
            }

			int top = titleRectangle.Y;
			int left = titleRectangle.X;
			int right = titleRectangle.X + texWidth - 1;
			int bottom = titleRectangle.Y + texHeight - 1;

            frameBufferQuad[0] = new PositionTexture(left,  top,    0, 0, 1);
            frameBufferQuad[1] = new PositionTexture(left,  bottom, 0, 0, 0);
            frameBufferQuad[2] = new PositionTexture(right, top,    0, 1, 1);
            frameBufferQuad[3] = new PositionTexture(right, bottom, 0, 1, 0);
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);

            List<PositionColor> verts = new List<PositionColor>();

            Rectangle frameTitleRect = ScreenToFrame(ClientToScreen(this.titleRectangle));

            int borderSize = BorderSize > 0 ? 1 : 0;
            if (borderSize > 0)
            {
                Color edgeColor = BorderEdgeColor;

                verts.Add(new PositionColor(new Vector3(frameTitleRect.Left, frameTitleRect.Top, 0f), edgeColor));
                verts.Add(new PositionColor(new Vector3(frameTitleRect.Left, frameTitleRect.Bottom, 0f), edgeColor));
                verts.Add(new PositionColor(new Vector3(frameTitleRect.Right, frameTitleRect.Top, 0f), edgeColor));

                verts.Add(new PositionColor(new Vector3(frameTitleRect.Left, frameTitleRect.Bottom, 0f), edgeColor));
                verts.Add(new PositionColor(new Vector3(frameTitleRect.Right, frameTitleRect.Bottom, 0f), edgeColor));
                verts.Add(new PositionColor(new Vector3(frameTitleRect.Right, frameTitleRect.Top, 0f), edgeColor));
            }

            Color color = titleColor;
            verts.Add(new PositionColor(new Vector3(frameTitleRect.Left + borderSize, frameTitleRect.Top + borderSize, 0f), color));
            verts.Add(new PositionColor(new Vector3(frameTitleRect.Left + borderSize, frameTitleRect.Bottom, 0f), color));
            verts.Add(new PositionColor(new Vector3(frameTitleRect.Right - borderSize, frameTitleRect.Top + borderSize, 0f), color));

            verts.Add(new PositionColor(new Vector3(frameTitleRect.Left + borderSize, frameTitleRect.Bottom, 0f), color));
            verts.Add(new PositionColor(new Vector3(frameTitleRect.Right - borderSize, frameTitleRect.Bottom, 0f), color));
            verts.Add(new PositionColor(new Vector3(frameTitleRect.Right - borderSize, frameTitleRect.Top + borderSize, 0f), color));

            PositionColor.Draw(BeginMode.Triangles, verts.ToArray());

            if (this.titleRectangle.Width > 0)
            {
                Frame.DrawText(titleFont, Text, frameTitleRect, DrawTextFormat.Bottom | DrawTextFormat.Center, Color.Black);
            }
        }

        public void DrawText(Font font, string text, Rectangle rectangle, DrawTextFormat drawTextFormat, Color color)
        {
            if (text == null) return;

            switch (drawTextFormat)
            {
                case DrawTextFormat.WordBreak: break;
                case DrawTextFormat.SingleLine: break;
                case DrawTextFormat.ExpandTabs: break;

                default: break;
            }

            RectangleF textSize = frameMgr.textPrinter.Measure(text, font).BoundingBox;
			
			int leftPadding;
            if ((drawTextFormat & DrawTextFormat.Right) == DrawTextFormat.Right)
            {
                leftPadding = (int)(rectangle.Width - textSize.Width);
            }
            else if ((drawTextFormat & DrawTextFormat.Center) == DrawTextFormat.Center)
            {
                leftPadding = (int)(rectangle.Width - textSize.Width) / 2;
            }
            else
            {
                leftPadding = 0;
            }

            int topPadding;
            if ((drawTextFormat & DrawTextFormat.VerticalCenter) == DrawTextFormat.VerticalCenter)
            {
                topPadding = (int)(rectangle.Height - textSize.Height) / 2;
            }
            else if ((drawTextFormat & DrawTextFormat.Bottom) == DrawTextFormat.Bottom)
            {
                topPadding = (int)(rectangle.Height - textSize.Height);
            }
            else
            {
                topPadding = 0;
            }

            Vector2 position = new Vector2(rectangle.X + leftPadding, rectangle.Y + topPadding);

            ShaderProgram.UseDefault();
            GL.Disable(EnableCap.Lighting);
            GL.Enable(EnableCap.ScissorTest);
			
            frameMgr.textPrinter.Begin();
            GL.Color3(color);
            GL.Translate(position.X, position.Y, 0);
            GL.Scissor(rectangle.X, frameBuffer.height - rectangle.Bottom, rectangle.Width, rectangle.Height);
			frameMgr.textPrinter.Print(text, font, Color.Black);
			frameMgr.textPrinter.End();			
            GL.Enable(EnableCap.Lighting);
            GL.Disable(EnableCap.ScissorTest);
        }

        public void Draw(double gameTime)
        {
            PositionTexture.Draw(BeginMode.TriangleStrip, frameBufferQuad, frameBuffer.handleTexture);
                        
            OOGL.ErrorChecking.TraceErrors();
        }
    }
}
