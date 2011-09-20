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
    public class ComboBox : BaseControl
    {
        private Rectangle screenRectText = new Rectangle();
        private Rectangle screenRectButton = new Rectangle();
        private Rectangle[] screenRectDropListItems = new Rectangle[0];

        public ComboBox(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {
        }

        private string text = "";
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

        private bool showDropList = false;
        public bool ShowDropList
        {
            get
            {
                return showDropList;
            }
            set
            {
                if (showDropList == value) return;
                showDropList = value;
                NeedUpdate();
            }
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);

            int size = clientRectangle.Height;
            if (size < 5) return;

			RectangleF fontSize = frameMgr.textPrinter.Measure("0", Font).BoundingBox;
			
            Rectangle screenRectClient = ClientToScreen(clientRectangle);
            screenRectText = new Rectangle(screenRectClient.X, screenRectClient.Y, clientRectangle.Width - size, clientRectangle.Height);
            screenRectButton = new Rectangle(screenRectClient.Right - size, screenRectClient.Y, size, size);

            object[] items = Items;
            Rectangle[] itemRects = new Rectangle[items.Length];
            for (int i = 0; i < items.Length; i++)
            {
                itemRects[i] = new Rectangle(screenRectClient.X, screenRectClient.Bottom + ((int)fontSize.Height * i) + 1, screenRectClient.Width, (int)fontSize.Height);
            }
            screenRectDropListItems = itemRects;

            Rectangle frameRectText = ScreenToFrame(screenRectText);
            Rectangle frameRectButton = ScreenToFrame(screenRectButton);

            List<PositionColor> verts = new List<PositionColor>();

            verts.Add(new PositionColor(new Vector3(frameRectButton.Left, frameRectButton.Top, 0f), Gradient(Color.Gray, 255)));
            verts.Add(new PositionColor(new Vector3(frameRectButton.Left, frameRectButton.Bottom, 0f), Gradient(Color.Gray, 127)));
            verts.Add(new PositionColor(new Vector3(frameRectButton.Right, frameRectButton.Top, 0f), Gradient(Color.Gray, 127)));

            verts.Add(new PositionColor(new Vector3(frameRectButton.Left, frameRectButton.Bottom, 0f), Gradient(Color.Gray, 127)));
            verts.Add(new PositionColor(new Vector3(frameRectButton.Right, frameRectButton.Bottom, 0f), Gradient(Color.Gray, 0)));
            verts.Add(new PositionColor(new Vector3(frameRectButton.Right, frameRectButton.Top, 0f), Gradient(Color.Gray, 127)));

            verts.Add(new PositionColor(new Vector3(frameRectButton.Left + 2, frameRectButton.Top + 2, 0f), Gradient(Color.LightGray, 255)));
            verts.Add(new PositionColor(new Vector3(frameRectButton.Left + (size / 2), frameRectButton.Bottom - 2, 0f), Gradient(Color.LightGray, 100)));
            verts.Add(new PositionColor(new Vector3(frameRectButton.Right - 2, frameRectButton.Top + 2, 0f), Gradient(Color.LightGray, 127)));

            if (showDropList)
            {
                for (int i = 0; i < items.Length; i++)
                {
                    Rectangle frameRectDropListItem = ScreenToFrame(screenRectDropListItems[i]);

                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Left, frameRectDropListItem.Top, 0f), Color.Gray));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Left, frameRectDropListItem.Bottom, 0f), Color.Gray));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Right, frameRectDropListItem.Top, 0f), Color.Gray));

                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Left, frameRectDropListItem.Bottom, 0f), Color.Gray));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Right, frameRectDropListItem.Bottom, 0f), Color.Gray));
                    verts.Add(new PositionColor(new Vector3(frameRectDropListItem.Right, frameRectDropListItem.Top, 0f), Color.Gray));
                }
            }

            PositionColor.Draw(BeginMode.Triangles, verts.ToArray());
            
            Frame.DrawText(Font, Text, frameRectText, DrawTextFormat.Bottom | DrawTextFormat.WordBreak, Color.Black);
            if (showDropList)
            {
                for (int i = 0; i < items.Length; i++)
                {
                    Rectangle frameRectDropListItem = ScreenToFrame(screenRectDropListItems[i]);
                    Frame.DrawText(Font, items[i].ToString(), frameRectDropListItem, DrawTextFormat.Left | DrawTextFormat.Bottom, Color.Black);
                }
            }
        }

        public override bool OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (screenRectButton.Contains(e.X, e.Y))
            {
                ShowDropList = !ShowDropList;
            }
            else if (ShowDropList)
            {
                Rectangle[] rects = screenRectDropListItems;
                for (int i = 0; i < rects.Length; i++)
                {
                    if (rects[i].Contains(e.X, e.Y))
                    {
                        SelectedIndex = i;
                        break;
                    }
                }
            }

            return base.OnMouseDown(sender, e);
        }

        public override void OnLostFocus()
        {
            ShowDropList = false;

            base.OnLostFocus();
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
                    Text = items[value].ToString();
                    ShowDropList = false;
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
                            Text = items[i].ToString();
                            ShowDropList = false;
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
