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

namespace OOGL.GUI.Widgets
{
    public class Label : BaseControl
    {
        public Label(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);
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
    }
}
