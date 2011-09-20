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
using OOGL.GUI.VertexStructures;

namespace OOGL.GUI.Widgets
{
    public class VScrollBar : ScrollBar
    {
        public VScrollBar(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {

        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            Rectangle screenRectClient = ClientToScreen(clientRectangle);

            if (screenRectClient.Height < buttonSize * 3 || Width == 0)
            {
                screenRectDecreaseValueButton = new Rectangle();
                screenRectIncreaseValueButton = new Rectangle();
                screenRectScrollRange = new Rectangle();
                screenRectValueButton = new Rectangle();
                return;
            }

            base.DrawToFrameBuffer(gameTime);

            screenRectDecreaseValueButton = new Rectangle(screenRectClient.Left, screenRectClient.Top, screenRectClient.Width, buttonSize);
            screenRectIncreaseValueButton = new Rectangle(screenRectClient.Left, screenRectClient.Bottom - buttonSize, screenRectClient.Width, buttonSize);
            screenRectScrollRange = new Rectangle(screenRectClient.Left, screenRectClient.Top + buttonSize, screenRectClient.Width, screenRectClient.Height - (2 * buttonSize));

            double pageSize = (screenRectScrollRange.Height - buttonSize) / (double)(1 + maxValue - minValue);
            if (pageSize < 0) pageSize = 0;

            screenRectValueButton = new Rectangle(screenRectScrollRange.Left, screenRectScrollRange.Top + (int)((value - minValue) * pageSize), screenRectScrollRange.Width, (int)(buttonSize + pageSize));

            List<PositionColor> verts = new List<PositionColor>();

            int size = clientRectangle.Width;

            float brightSkew = 0.90f;
            float darkSkew = -0.50f;

            Rectangle frameRectDecreaseValueButton = ScreenToFrame(screenRectDecreaseValueButton);
            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Left, frameRectDecreaseValueButton.Top, 0f), Gradient(Color.Gray, 255)));
            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Left, frameRectDecreaseValueButton.Bottom, 0f), Gradient(Color.Gray, 127)));
            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Right, frameRectDecreaseValueButton.Top, 0f), Gradient(Color.Gray, 127)));

            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Left, frameRectDecreaseValueButton.Bottom, 0f), Gradient(Color.Gray, 127)));
            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Right, frameRectDecreaseValueButton.Bottom, 0f), Gradient(Color.Gray, 0)));
            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Right, frameRectDecreaseValueButton.Top, 0f), Gradient(Color.Gray, 127)));

            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Left + 2, frameRectDecreaseValueButton.Bottom - 2, 0f), Gradient(Color.LightGray, 127)));
            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Right - 2, frameRectDecreaseValueButton.Bottom - 2, 0f), Gradient(Color.LightGray, 100)));
            verts.Add(new PositionColor(new Vector3(frameRectDecreaseValueButton.Left + (size / 2), frameRectDecreaseValueButton.Top + 2, 0f), Gradient(Color.LightGray, 127)));

            Rectangle frameRectIncreaseValueButton = ScreenToFrame(screenRectIncreaseValueButton);
            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Left, frameRectIncreaseValueButton.Top, 0f), Gradient(Color.Gray, 255)));
            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Left, frameRectIncreaseValueButton.Bottom, 0f), Gradient(Color.Gray, 127)));
            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Right, frameRectIncreaseValueButton.Top, 0f), Gradient(Color.Gray, 127)));

            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Left, frameRectIncreaseValueButton.Bottom, 0f), Gradient(Color.Gray, 127)));
            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Right, frameRectIncreaseValueButton.Bottom, 0f), Gradient(Color.Gray, 0)));
            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Right, frameRectIncreaseValueButton.Top, 0f), Gradient(Color.Gray, 127)));

            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Left + 2, frameRectIncreaseValueButton.Top + 2, 0f), Gradient(Color.LightGray, 255)));
            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Left + (size / 2), frameRectIncreaseValueButton.Bottom - 2, 0f), Gradient(Color.LightGray, 100)));
            verts.Add(new PositionColor(new Vector3(frameRectIncreaseValueButton.Right - 2, frameRectIncreaseValueButton.Top + 2, 0f), Gradient(Color.LightGray, 127)));

            Rectangle frameRectValueButton = ScreenToFrame(screenRectValueButton);
            verts.Add(new PositionColor(new Vector3(frameRectValueButton.Left, frameRectValueButton.Top, 0f), Gradient(Color.Gray, brightSkew)));
            verts.Add(new PositionColor(new Vector3(frameRectValueButton.Left, frameRectValueButton.Bottom, 0f), Gradient(Color.Gray, brightSkew)));
            verts.Add(new PositionColor(new Vector3(frameRectValueButton.Right, frameRectValueButton.Top, 0f), Gradient(Color.Gray, darkSkew)));

            verts.Add(new PositionColor(new Vector3(frameRectValueButton.Left, frameRectValueButton.Bottom, 0f), Gradient(Color.Gray, brightSkew)));
            verts.Add(new PositionColor(new Vector3(frameRectValueButton.Right, frameRectValueButton.Bottom, 0f), Gradient(Color.Gray, darkSkew)));
            verts.Add(new PositionColor(new Vector3(frameRectValueButton.Right, frameRectValueButton.Top, 0f), Gradient(Color.Gray, darkSkew)));

            PositionColor.Draw(BeginMode.Triangles, verts.ToArray());
        }

        public override void OnMouseMove(object sender, MouseMoveEventArgs e)
        {
            if (!dragging) return;

            double normalized = (e.Y - screenRectScrollRange.Y) / (double)(screenRectScrollRange.Height);
            if (normalized < 0) normalized = 0;
            if (normalized > 1) normalized = 1;

            Value = (int)Math.Round(minValue + (normalized * (maxValue - minValue)));

            base.OnMouseMove(sender, e);
        }

        public override void OnMouseUp(object sender, MouseButtonEventArgs e)
        {
            dragging = false;

            base.OnMouseUp(sender, e);
        }
    }
}
