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

using OOGL.GUI.Abstract;
using OOGL.GUI.VertexStructures;

namespace OOGL.GUI.Widgets
{
    public class Button : BaseControl
    {
        public Button(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);

            Rectangle frameClientRect = ScreenToFrame(ClientToScreen(clientRectangle));

            List<PositionColor> verts = new List<PositionColor>();

            Color color = BackgroundColor;

            float topSkew;
            float bottomSkew;
            if (isPressed)
            {
                topSkew = 0.0f;
                bottomSkew = -.75f;
            }
            else
            {
                topSkew = 0.5f;
                bottomSkew = -0.5f;
            }

            verts.Add(new PositionColor(new Vector3(frameClientRect.Left, frameClientRect.Top, 0f), Gradient(color, topSkew)));
            verts.Add(new PositionColor(new Vector3(frameClientRect.Left, frameClientRect.Bottom, 0f), Gradient(color, bottomSkew)));
            verts.Add(new PositionColor(new Vector3(frameClientRect.Right, frameClientRect.Top, 0f), Gradient(color, topSkew)));

            verts.Add(new PositionColor(new Vector3(frameClientRect.Left, frameClientRect.Bottom, 0f), Gradient(color, bottomSkew)));
            verts.Add(new PositionColor(new Vector3(frameClientRect.Right, frameClientRect.Bottom, 0f), Gradient(color, bottomSkew)));
            verts.Add(new PositionColor(new Vector3(frameClientRect.Right, frameClientRect.Top, 0f), Gradient(color, topSkew)));

            PositionColor.Draw(BeginMode.Triangles, verts.ToArray());
            Frame.DrawText(Font, text, ScreenToFrame(ClientToScreen(clientRectangle)), drawTextFormat, textColor);
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

        private bool isPressed;
        public bool IsPressed
        {
            get
            {
                return isPressed;
            }
            set
            {
                isPressed = value;
                NeedUpdate();
            }
        }

        public EventHandler<EventArgs> Pressed;
        private void OnPressed()
        {
            EventHandler<EventArgs> items = Pressed;
            if (items != null) items(this, null);
        }

        public Font Font
        {
            get
            {
                return frameMgr.SansSerifFont;
            }
        }

        private Color textColor = Color.Black;
        public Color TextColor
        {
            get
            {
                return textColor;
            }
            set
            {
                textColor = value;
                NeedUpdate();
            }
        }

        private DrawTextFormat drawTextFormat = DrawTextFormat.VerticalCenter | DrawTextFormat.Center;
        public DrawTextFormat DrawTextFormat
        {
            get
            {
                return drawTextFormat;
            }
            set
            {
                drawTextFormat = value;
                NeedUpdate();
            }
        }

        public override bool OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (base.OnMouseDown(sender, e))
            {
                IsPressed = true;
                OnPressed();
                return true;
            }

            return false;
        }

        public override void OnMouseUp(object sender, MouseButtonEventArgs e)
        {
            IsPressed = false;
        }

        public override void OnLostFocus()
        {
            IsPressed = false;
        }
    }
}
