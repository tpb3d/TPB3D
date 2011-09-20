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
    public class ListBox : BaseControl
    {
        private Rectangle[] screenRectItems = new Rectangle[0];

        public ListBox(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);

            int size = clientRectangle.Height;
            if (size < 5) return;

            RectangleF fontSize = frameMgr.textPrinter.Measure("0", Font).BoundingBox;
			Rectangle screenRectClient = ClientToScreen(clientRectangle);

            object[] items = Items;
            if (items.Length == 0) return;
            
            Rectangle[] itemRects = new Rectangle[items.Length];
            for (int i = 0; i < items.Length; i++)
            {
                itemRects[i] = new Rectangle(screenRectClient.X, screenRectClient.Y + ((int)fontSize.Height * i), screenRectClient.Width, (int)fontSize.Height);
            }
            screenRectItems = itemRects;

            List<PositionColor> verts = new List<PositionColor>();

            for (int i = 0; i < items.Length; i++)
            {
                if (screenRectItems[i].Bottom <= screenRectClient.Bottom)
                {
                    Rectangle frameRectDropListItem = ScreenToFrame(screenRectItems[i]);
                    Color color = (i == selectedIndex) ? Color.SteelBlue : Color.Gray;

                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Left, frameRectDropListItem.Top, 0f), color));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Left, frameRectDropListItem.Bottom, 0f), color));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Right, frameRectDropListItem.Top, 0f), color));

                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Left, frameRectDropListItem.Bottom, 0f), color));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Right, frameRectDropListItem.Bottom, 0f), color));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Right, frameRectDropListItem.Top, 0f), color));
                }
            }

            PositionColor.Draw(BeginMode.Triangles, verts.ToArray());

            for (int i = 0; i < items.Length; i++)
            {
                if (screenRectItems[i].Bottom <= screenRectClient.Bottom)
                {
                    Rectangle frameRectDropListItem = ScreenToFrame(screenRectItems[i]);
                    Frame.DrawText(Font, items[i].ToString(), frameRectDropListItem, DrawTextFormat.Left | DrawTextFormat.Bottom, Color.Black);
                }
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

        public override bool OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle[] rects = screenRectItems;
            for (int i = 0; i < rects.Length; i++)
            {
                if (rects[i].Contains(e.X, e.Y))
                {
                    SelectedIndex = i;
                    break;
                }
            }

            return base.OnMouseDown(sender, e);
        }

        private List<object> items = new List<object>();
        public object[] Items
        {
            get
            {
                lock (items)
                {
                    return items.ToArray();
                }
            }
            set
            {
                lock (items)
                {
                    items = new List<object>(value);
                    items.TrimExcess();
                    selectedIndex = -1;
                }
                NeedUpdate();
            }
        }

        public void AddItem(object item)
        {
            lock (items)
            {
                items.Add(item);
                items.TrimExcess();
            }
            NeedUpdate();
        }

        public void ClearItems()
        {
            lock (items)
            {
                items.Clear();
                selectedIndex = -1;
            }
            NeedUpdate();
        }

        private int selectedIndex = -1;
        public int SelectedIndex
        {
            get
            {
                return selectedIndex;
            }
            set
            {
                lock (items)
                {
                    if (value < 0 || value >= items.Count) throw new ArgumentOutOfRangeException();
                    selectedIndex = value;
                    NeedUpdate();
                    OnSelectedIndexChanged();
                }
            }
        }

        public object SelectedItem
        {
            get
            {
                lock (items)
                {
                    if (selectedIndex == -1) return null;
                    return items[selectedIndex];
                }
            }
            set
            {
                lock (items)
                {
                    for (int i = 0; i < items.Count; i++)
                    {
                        if (items[i] == value)
                        {
                            selectedIndex = i;
                            NeedUpdate();
                            OnSelectedIndexChanged();
                            return;
                        }
                    }
                }
                throw new ArgumentOutOfRangeException();
            }
        }

        public event EventHandler SelectedIndexChanged;
        private void OnSelectedIndexChanged()
        {
            EventHandler items = SelectedIndexChanged;
            if (items == null) return;
            items(this, null);
        }

    }
}
