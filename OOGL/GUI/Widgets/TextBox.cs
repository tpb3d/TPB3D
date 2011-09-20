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
using System.Drawing;
using System.Collections.Generic;
using System.Text;

using OpenTK.Graphics;
using OpenTK;
using OpenTK.Input;

using OOGL.GUI.Abstract;

namespace OOGL.GUI.Widgets
{
    public class Textbox : BaseControl
    {
        private VScrollBar scrollBar;

        public Textbox(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {
        }

        public override void InitializeControls()
        {
            base.InitializeControls();

            this.scrollBar = new VScrollBar(frameMgr, this);
            this.scrollBar.BorderSize = 0;
            this.scrollBar.MinValue = 0;
            this.scrollBar.ValueChanged += new EventHandler(scrollBar_ValueChanged);
            AddChildControl(this.scrollBar);
        }

        void scrollBar_ValueChanged(object sender, EventArgs e)
        {
            NeedUpdate();
        }

        public override void OnResize()
        {
            base.OnResize();

            int width = showScrollBar ? scrollBarWidth : 0;
            scrollBar.Size = new Size(width, clientRectangle.Height);
            scrollBar.Location = new Point(clientRectangle.Width - width, 0);
        }

        public string Text
        {
            get
            {
                if (lines == null || lines.Length == 0) return "";
                return lines[0];
            }
            set
            {
                lines = new string[] { value };
                scrollBar.MaxValue = 0;
                NeedUpdate();
            }
        }

        private string[] lines = new string[] { "" };
        public string[] Lines
        {
            get
            {
                return lines;
            }
            set
            {
                bool lastLine = scrollBar.Value == lines.Length - 1;

                if (value == null)
                {
                    lines = new string[] { "" };
                }
                else
                {
                    lines = value;
                }

                scrollBar.MaxValue = lines.Length - 1;
                if (lastLine) scrollBar.Value = lines.Length - 1;
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

        private bool showScrollBar = false;
        public bool ShowScrollBar
        {
            get
            {
                return showScrollBar;
            }
            set
            {
                if (showScrollBar == value) return;
                showScrollBar = value;
                OnResize();
                NeedUpdate();
            }
        }

        private int scrollBarWidth = 15;
        public int ScrollBarWidth
        {
            get
            {
                return scrollBarWidth;
            }
            set
            {
                if (scrollBarWidth == value) return;
                scrollBarWidth = value;
                NeedUpdate();
            }
        }

        public ScrollBar ScrollBar
        {
            get
            {
                return scrollBar;
            }
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);

            string[] lines = this.lines;
            if (lines == null) return;

            int adjLength = scrollBar.Value + 1;
            if (adjLength > lines.Length) adjLength = lines.Length;

            StringBuilder text = new StringBuilder();
            for (int i = 0; i < adjLength; i++)
            {
                if (i > 0) text.AppendLine();
                text.Append(lines[i]);
            }

            Rectangle textRectangle = new Rectangle(clientRectangle.X + 1, clientRectangle.Y + 1, clientRectangle.Width - scrollBar.Width - 2, clientRectangle.Height - 2);
            Frame.DrawText(Font, text.ToString(), ScreenToFrame(ClientToScreen(textRectangle)), DrawTextFormat.Bottom | DrawTextFormat.WordBreak, Color.Black);
        }

        public override bool ConsumingKeyboard
        {
            get
            {
                return true;
            }
        }

        //public override void OnKeyDown(KeyboardDevice keyboard, Key key)
        //{
        //    string text = Text;
        //    if (key == Key.BackSpace)
        //    {
        //        if (text.Length > 0) Text = text.Substring(0, text.Length - 1);
        //    }
        //    else
        //    {
        //        bool shift = keyboard[Key.ShiftLeft] || keyboard[Key.ShiftRight];
        //        Text = text +  BaseFrameMgr.TranslateKey(key, shift);
        //    }
        //}

        public override void OnKeyDown(object sender, KeyboardKeyEventArgs e) {
            string text = Text;
            KeyboardDevice keyboard = sender as KeyboardDevice;
            if (e.Key == Key.BackSpace) {
                if (text.Length > 0) Text = text.Substring(0, text.Length - 1);
            }
            else {
                bool shift = keyboard[Key.ShiftLeft] || keyboard[Key.ShiftRight];
                Text = text + BaseFrameMgr.TranslateKey(e.Key, shift);
            }
        }
    }
}