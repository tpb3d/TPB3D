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

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Input;
using OpenTK.Platform;

using OOGL;
using OOGL.Shaders;
using OOGL.GUI.VertexStructures;

namespace OOGL.GUI.Abstract
{
    public class BaseFrameMgr : IDisposable
    {
        protected BaseFrame[] windows = new BaseFrame[0];

        public readonly ITextPrinter textPrinter = new TextPrinter();

        public BaseFrameMgr(GameWindow gameWindow, ShaderProgram positionColorShader, ShaderProgram positionTextureShader)
        {
        	this.gameWindow = gameWindow;
            this.gameWindow.Resize += new EventHandler<EventArgs>(GameWindow_Resize);

            PositionColor.Shader = positionColorShader;
            PositionTexture.Shader = positionTextureShader;
        }

		public void Dispose()
		{
            for (int i = 0; i < windows.Length; i++)
            {
                try
                {
                    windows[i].Dispose();
                }
                catch
                {
                }
            }
		}

		private void GameWindow_Resize(object sender, EventArgs args)
		{
            foreach (BaseFrame frame in windows)
            {
                frame.NeedUpdate();
            }
		}

        public void OnKeyDown(object sender, KeyboardKeyEventArgs e)
		{
			if (focusedControl != null) focusedControl.OnKeyDown(sender, e);
		}

        public void OnKeyUp(object sender, KeyboardKeyEventArgs e)
		{
		}

		public bool OnMouseDown(object sender, MouseButtonEventArgs e)
		{
            if (focusedControl != null && focusedControl.OnMouseDown(sender, e)) return true;

            for (int i = 0; i < windows.Length; i++)
            {
                if (windows[i].OnMouseDown(sender, e))
                {
                    SetTopMostWindow(windows[i]);
                    return true;
                }
            }

            focusedControl = null;
            return false;
		}

		public bool OnMouseUp(object sender, MouseButtonEventArgs e)
		{
            if (focusedControl == null) return false;
            focusedControl.OnMouseUp(this, e);
            return true;
		}

        public bool OnMouseMove(object sender, MouseMoveEventArgs e)
        {
            if (focusedControl == null) return false;
            focusedControl.OnMouseMove(sender, e);
            return true;
        }
        
        public void Update(double gameTime)
        {
            try
            {
                for (int i = 0; i < windows.Length; i++) windows[i].Update(gameTime);   
            }
            catch (Exception ex)
            {
            	Console.WriteLine(ex.ToString());
            }
        }

        public void Draw(double gameTime)
        {
            try
            {
				GL.Enable(EnableCap.Blend);
				GL.BlendFunc(BlendingFactorSrc.SrcAlpha, BlendingFactorDest.OneMinusSrcAlpha);

				GL.MatrixMode(MatrixMode.Projection);
				GL.LoadMatrix(OOGL.Matrix4Helper.ToOpenGL(Matrix4Helper.CreateOrthographicProjection(0, gameWindow.Width, 0, gameWindow.Height, 0, 1)));

				GL.MatrixMode(MatrixMode.Modelview);
				GL.LoadMatrix(OOGL.Matrix4Helper.ToOpenGL(Matrix4.Identity));

                for (int i = windows.Length - 1; i >= 0; i--) windows[i].Draw(gameTime);

				GL.Disable(EnableCap.Blend);
            }
            catch (Exception ex)
            {
				Trace.WriteLine(ex.ToString());
            }
        }

        protected readonly GameWindow gameWindow;
        public GameWindow GameWindow
        {
            get
            {
                return gameWindow;
            }
        }

        private BaseControl focusedControl = null;
        public BaseControl FocusedControl
        {
            get
            {
                return focusedControl;
            }
            set
            {
                BaseControl oldFocusedControl = focusedControl;
                focusedControl = value;
                if (Object.ReferenceEquals(oldFocusedControl, focusedControl) == false)
                {
                    if (oldFocusedControl != null) oldFocusedControl.OnLostFocus();
                    if (focusedControl != null) focusedControl.OnGotFocus();
                }
            }
        }

        protected Font sansSerifFont = new Font(FontFamily.GenericSansSerif, 10.0f);
        public Font SansSerifFont
        {
            get
            {
                return sansSerifFont;
            }
        }

        protected Font robotechFont = new Font(FontFamily.GenericSerif, 14.0f);
        public Font TitleBarFont
        {
            get
            {
                return robotechFont;
            }
        }

        protected Size maxWindowSize = new Size(1920, 1200); // TODO Fix
        public Size MaxWindowSize
        {
            get
            {
                return maxWindowSize;
            }
        }
        
        public void SetTopMostWindow(BaseFrame window)
        {
            List<BaseFrame> windows = new List<BaseFrame>(this.windows);
            if (windows.Remove(window)) windows.Insert(0, window);
            this.windows = windows.ToArray();
        }

        /// <summary>
        /// Indicates whether the control with focus wants keyboard events.
        /// </summary>
        public virtual bool ConsumingKeyboard
        {
            get
            {
                if (focusedControl != null) return focusedControl.ConsumingKeyboard;
                return false;
            }
        }

        public void AddWindow(BaseFrame window)
        {
            List<BaseFrame> windows = new List<BaseFrame>(this.windows);
            windows.Add(window);
            this.windows = windows.ToArray();

            if (focusedControl == null) focusedControl = window;
        }

        public void RemoveWindow(BaseFrame window)
        {
            List<BaseFrame> windows = new List<BaseFrame>(this.windows);
            windows.Remove(window);
            this.windows = windows.ToArray();

            if (focusedControl != window) return;
            if (this.windows.Length == 0) focusedControl = null;
            focusedControl = this.windows[0];
        }
        
        public static string TranslateKey(Key key, bool shift)
        {
        
            switch (key)
            {
                case Key.A: return (shift) ? "A" : "a";
                case Key.B: return (shift) ? "B" : "b";
                case Key.C: return (shift) ? "C" : "c";
                case Key.D: return (shift) ? "D" : "d";
                case Key.E: return (shift) ? "E" : "e";
                case Key.F: return (shift) ? "F" : "f";
                case Key.G: return (shift) ? "G" : "g";
                case Key.H: return (shift) ? "H" : "h";
                case Key.I: return (shift) ? "I" : "i";
                case Key.J: return (shift) ? "J" : "j";
                case Key.K: return (shift) ? "K" : "k";
                case Key.L: return (shift) ? "L" : "l";
                case Key.M: return (shift) ? "M" : "m";
                case Key.N: return (shift) ? "N" : "n";
                case Key.O: return (shift) ? "O" : "o";
                case Key.P: return (shift) ? "P" : "p";
                case Key.Q: return (shift) ? "Q" : "q";
                case Key.R: return (shift) ? "R" : "r";
                case Key.S: return (shift) ? "S" : "s";
                case Key.T: return (shift) ? "T" : "t";
                case Key.U: return (shift) ? "U" : "u";
                case Key.V: return (shift) ? "V" : "v";
                case Key.W: return (shift) ? "W" : "w";
                case Key.X: return (shift) ? "X" : "x";
                case Key.Y: return (shift) ? "Y" : "y";
                case Key.Z: return (shift) ? "Z" : "z";

                case Key.Tilde: return (shift) ? "~" : "`";
                case Key.Number1: return (shift) ? "!" : "1";
                case Key.Number2: return (shift) ? "@" : "2";
                case Key.Number3: return (shift) ? "#" : "3";
                case Key.Number4: return (shift) ? "$" : "4";
                case Key.Number5: return (shift) ? "%" : "5";
                case Key.Number6: return (shift) ? "^" : "6";
                case Key.Number7: return (shift) ? "&" : "7";
                case Key.Number8: return (shift) ? "*" : "8";
                case Key.Number9: return (shift) ? "(" : "9";
                case Key.Number0: return (shift) ? ")" : "0";
                case Key.Minus: return (shift) ? "_" : "-";
                case Key.Plus: return (shift) ? "+" : "=";
                case Key.BracketLeft: return (shift) ? "{" : "[";
                case Key.BracketRight: return (shift) ? "}" : "]";
                case Key.BackSlash: return (shift) ? "|" : "\\";
                case Key.Semicolon: return (shift) ? ":" : ";";
                case Key.Quote: return (shift) ? "\"" : "'";
                case Key.Comma: return (shift) ? "<" : ",";
                case Key.Period: return (shift) ? ">" : ".";
                case Key.Slash: return (shift) ? "?" : "/";
                case Key.Space: return " ";

                default: return "";
            }
        }

        public static bool IsModifier(Key key)
        {
            return
                key == Key.AltLeft || key == Key.AltRight ||
                key == Key.ControlLeft || key == Key.ControlRight ||
                key == Key.ShiftLeft || key == Key.ShiftRight;
        }

        public void LoadWorkspace()
        {
            try
            {
                string workspacePath = System.Environment.CurrentDirectory;

                for (int i = 0; i < windows.Length; i++)
                {
                    windows[i].LoadSettings(workspacePath);
                }
            }
            catch
            {
            }
        }

        public void SaveWorkspace()
        {
            try
            {
                string workspacePath = System.Environment.CurrentDirectory;

                for (int i = 0; i < windows.Length; i++)
                {
                    windows[i].SaveSettings(workspacePath);
                }
            }
            catch
            {
            }
        }
    }
}
