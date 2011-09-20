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

using OpenTK.Graphics;
using OpenTK;
using OpenTK.Input;

namespace OOGL.GUI.Abstract
{
    public abstract class BaseControl
    {
        protected Color darkEdgeColor = Color.DarkBlue;
        protected Color lightEdgeColor = Color.LightBlue;

        public BaseControl(BaseFrameMgr frameMgr, BaseControl parent)
        {
            this.frameMgr = frameMgr;
            this.parent = parent;

            InitializeControls();

            BorderColor = Color.SteelBlue;
            BackgroundColor = Color.LightBlue;
            BorderSize = 4;
        }

        protected void SafeDispose<T>(ref T iDisposable) where T : class, IDisposable
        {
            if (iDisposable == null) return;
            try
            {
                iDisposable.Dispose();
            }
            catch
            {
            }
            finally
            {
                iDisposable = null;
            }
        }


        protected BaseFrameMgr frameMgr;
        public BaseFrameMgr FrameMgr
        {
            get
            {
                return frameMgr;
            }
        }

        protected BaseControl parent;
        public BaseControl Parent
        {
            get
            {
                return parent;
            }
        }
        
        public virtual BaseFrame Frame
        {
        	get
	        {
	        	return parent.Frame;
	        }
        }
        
        public virtual void NeedUpdate()
        {
            if (parent != null) parent.NeedUpdate();
        }

        public virtual void InitializeControls()
        {
        }

        public Rectangle ClientToScreen(Rectangle childRectangle)
        {
            if (parent == null) return childRectangle;
            childRectangle.Offset(parent.clientRectangle.X, parent.clientRectangle.Y);
            return parent.ClientToScreen(childRectangle);
        }

        public Rectangle ControlToScreen(Rectangle childRectangle)
        {
            if (parent == null) return childRectangle;
            childRectangle.Offset(parent.controlRectangle.X, parent.controlRectangle.Y);
            return parent.ControlToScreen(childRectangle);
        }

        public virtual Rectangle ScreenToFrame(Rectangle childRectangle)
        {
            return parent.ScreenToFrame(childRectangle);
        }

        protected Rectangle controlRectangle = new Rectangle(0, 0, 10, 10);
        public Rectangle ControlRectangle
        {
            get
            {
                return controlRectangle;
            }
            set
            {
                if (value.Height < 1) return;
                if (value.Width < 1) return;
                this.controlRectangle = value;
                NeedUpdate();
                OnMove();
                OnResize();
            }
        }

        protected Rectangle clientRectangle = new Rectangle();
        public Rectangle ClientRectangle
        {
            get
            {
                return clientRectangle;
            }
        }

        public Point Location
        {
            get
            {
                return new Point(controlRectangle.X, controlRectangle.Y);
            }
            set
            {
                controlRectangle.X = value.X;
                controlRectangle.Y = value.Y;
                NeedUpdate();
                OnMove();
            }
        }

        public virtual Size Size
        {
            get
            {
                return new Size(controlRectangle.Width, controlRectangle.Height);
            }
            set
            {
                if (value.Height < 1) return;
                if (value.Width < 1) return;
                controlRectangle.Width = value.Width;
                controlRectangle.Height = value.Height;
                NeedUpdate();
                OnResize();
            }
        }

        private int borderSize = 5;
        public int BorderSize
        {
            get
            {
                return borderSize;
            }
            set
            {
                if (value < 0) return;
                if (value > 20) return;
                borderSize = value;
                NeedUpdate();
                OnResize();
            }
        }

        public virtual void OnMove()
        {
            clientRectangle = ComputeClientRectangle();
            NeedUpdate();

            BaseControl[] childControls = ChildControls;
            for (int i = 0; i < childControls.Length; i++) childControls[i].OnMove();
        }

        public virtual void OnResize()
        {
            clientRectangle = ComputeClientRectangle();
            NeedUpdate();

            BaseControl[] childControls = ChildControls;
            for (int i = 0; i < childControls.Length; i++) childControls[i].OnResize();
        }

        /// <summary>
        /// Indicates whether the control wants keyboard events.
        /// </summary>
        public virtual bool ConsumingKeyboard
        {
            get
            {
                return false;
            }
        }

        public virtual void OnKeyDown(object sender, KeyboardKeyEventArgs e)
		{
		}

        public virtual void OnKeyUp(object sender, KeyboardKeyEventArgs e)
		{
		}

        private Rectangle ComputeClientRectangle()
        {
            int maxBorderWidth = (controlRectangle.Width - 1) / 2;
            int maxBorderHeight = (controlRectangle.Height - 1) / 2;
            int adjustedBorderSize = Math.Min(borderSize, Math.Min(maxBorderHeight, maxBorderWidth));

            return new Rectangle(controlRectangle.X + adjustedBorderSize, controlRectangle.Y + adjustedBorderSize, controlRectangle.Width - (adjustedBorderSize * 2), controlRectangle.Height - (adjustedBorderSize * 2));
        }

        public virtual bool OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            BaseControl[] childControls = ChildControls;
            for (int i = 0; i < childControls.Length; i++)
            {
                if (childControls[i].OnMouseDown(sender, e)) return true;
            }

            Rectangle screenRectClient = ControlToScreen(controlRectangle);
            if (screenRectClient.Contains(e.X, e.Y))
            {
                frameMgr.FocusedControl = this;
                return true;
            }

            return false;
        }

        public virtual void OnMouseMove(object sender, MouseMoveEventArgs e)
        {
        }

        public virtual void OnMouseUp(object sender, MouseButtonEventArgs e)
        {
        }

        public virtual void OnLostFocus()
        {
        }

        public virtual void OnGotFocus()
        {
        }

        public int X
        {
            get
            {
                return controlRectangle.X;
            }
        }

        public int Y
        {
            get
            {
                return controlRectangle.Y;
            }
        }

        public int Height
        {
            get
            {
                return controlRectangle.Height;
            }
        }

        public int Width
        {
            get
            {
                return controlRectangle.Width;
            }
        }

        private Color borderColor = Color.Blue;
        public Color BorderColor
        {
            get
            {
                return borderColor;
            }
            set
            {
                borderColor = value;
                NeedUpdate();
            }
        }

        private Color borderEdgeColor = Color.LightGray;
        public Color BorderEdgeColor
        {
            get
            {
                return borderEdgeColor;
            }
            set
            {
                borderEdgeColor = value;
                NeedUpdate();
            }
        }
	
        private Color backGroundColor = Color.Silver;
        public Color BackgroundColor
        {
            get
            {
                return backGroundColor;
            }
            set
            {
                backGroundColor = value;
                NeedUpdate();
            }
        }

        public static Color Gradient(Color color, float brightness)
        {
            if (brightness > 1) brightness = 1;
            if (brightness < -1) brightness = -1;

            float p = Math.Abs(brightness);
            float q = 1 - p;

            int skew = (brightness >= 0) ? (int)(255 * p) : 0;

            byte red = (byte)((color.R * q) + skew);
            byte green = (byte)((color.G * q) + skew);
            byte blue = (byte)((color.B * q) + skew);

            return Color.FromArgb(color.A, red, green, blue);
        }

        public static Color Gradient(Color color, int shift)
        {
            return Color.FromArgb(color.A, (color.R + shift) / 2, (color.G + shift) / 2, (color.B + shift) / 2);
        }

        public virtual void DrawToFrameBuffer(double gameTime)
        {
            if (controlRectangle.Width < 5 || controlRectangle.Height < 5) return;

            Rectangle frameControlRect = ScreenToFrame(ClientToScreen(controlRectangle));
            List<PositionColor> verts = new List<PositionColor>();

            int borderOffset = 1;

            Color edgeColor = borderEdgeColor;

            verts.Add(new PositionColor(new Vector3(frameControlRect.Left, frameControlRect.Top, 0f), edgeColor));
            verts.Add(new PositionColor(new Vector3(frameControlRect.Left, frameControlRect.Bottom - 1, 0f), edgeColor));
            verts.Add(new PositionColor(new Vector3(frameControlRect.Right, frameControlRect.Top, 0f), edgeColor));

            verts.Add(new PositionColor(new Vector3(frameControlRect.Left, frameControlRect.Bottom, 0f), edgeColor));
            verts.Add(new PositionColor(new Vector3(frameControlRect.Right, frameControlRect.Bottom, 0f), edgeColor));
            verts.Add(new PositionColor(new Vector3(frameControlRect.Right, frameControlRect.Top, 0f), edgeColor));

            if (borderSize > 1)
            {
                verts.Add(new PositionColor(new Vector3(frameControlRect.Left + borderOffset, frameControlRect.Top + borderOffset, 0f), borderColor));
                verts.Add(new PositionColor(new Vector3(frameControlRect.Left + borderOffset, frameControlRect.Bottom - borderOffset, 0f), borderColor));
                verts.Add(new PositionColor(new Vector3(frameControlRect.Right - borderOffset, frameControlRect.Top + borderOffset, 0f), borderColor));

                verts.Add(new PositionColor(new Vector3(frameControlRect.Left + borderOffset, frameControlRect.Bottom - borderOffset, 0f), borderColor));
                verts.Add(new PositionColor(new Vector3(frameControlRect.Right - borderOffset, frameControlRect.Bottom - borderOffset, 0f), borderColor));
                verts.Add(new PositionColor(new Vector3(frameControlRect.Right - borderOffset, frameControlRect.Top + borderOffset, 0f), borderColor));
            }

            if (backGroundColor != Color.Transparent)
            {
                Rectangle frameClientRect = ScreenToFrame(ClientToScreen(clientRectangle));

                float brightSkew = 0.25f;
                float middleSkew = 0.00f;
                float darkSkew = -0.25f;

                verts.Add(new PositionColor(new Vector3(frameClientRect.Left, frameClientRect.Top, 0f), Gradient(backGroundColor, brightSkew)));
                verts.Add(new PositionColor(new Vector3(frameClientRect.Left, frameClientRect.Bottom, 0f), Gradient(backGroundColor, middleSkew)));
                verts.Add(new PositionColor(new Vector3(frameClientRect.Right, frameClientRect.Top, 0f), Gradient(backGroundColor, middleSkew)));

                verts.Add(new PositionColor(new Vector3(frameClientRect.Left, frameClientRect.Bottom, 0f), Gradient(backGroundColor, middleSkew)));
                verts.Add(new PositionColor(new Vector3(frameClientRect.Right, frameClientRect.Bottom, 0f), Gradient(backGroundColor, darkSkew)));
                verts.Add(new PositionColor(new Vector3(frameClientRect.Right, frameClientRect.Top, 0f), Gradient(backGroundColor, middleSkew)));
            }

            PositionColor.Draw(BeginMode.Triangles, verts.ToArray());

            BaseControl[] childControls = ChildControls;
            for (int i = 0; i < childControls.Length; i++) childControls[i].DrawToFrameBuffer(gameTime);
        }

        protected BaseControl[] childControls = new BaseControl[0];
        public BaseControl[] ChildControls
        {
            get
            {
                return childControls;
            }
        }

        public void AddChildControl(BaseControl child)
        {
            List<BaseControl> list = new List<BaseControl>(childControls);
            list.Add(child);
            childControls = list.ToArray();
        }
    }
}
