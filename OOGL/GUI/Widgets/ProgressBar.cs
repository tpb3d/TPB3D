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
    public class ProgressBar : BaseControl
    {
        public ProgressBar(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {
        }

        public override void InitializeControls()
        {
            base.InitializeControls();
        }

        private Color barColor = Color.Red;
        public Color BarColor
        {
            get
            {
                return barColor;
            }
            set
            {
                barColor = value;
                NeedUpdate();
            }
        }

        private int minValue = 0;
        public int MinValue
        {
            get
            {
                return minValue;
            }
            set
            {
                minValue = value;
                NeedUpdate();
            }
        }

        private int maxValue = 100;
        public int MaxValue
        {
            get
            {
                return maxValue;
            }
            set
            {
                maxValue = value;
                NeedUpdate();
            }
        }

        private int value = 0;
        public int Value
        {
            get
            {
                return value;
            }
            set
            {
                this.value = value;
                NeedUpdate();
            }
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);

            double perc = (double)(value - minValue) / (double)(maxValue - minValue);
            int mid = (int)(perc * clientRectangle.Width);

            Rectangle frameClientRect = ScreenToFrame(ClientToScreen(clientRectangle));
            PositionColor[] barQuad = new PositionColor[4];

            barQuad[0].Position = new Vector3(frameClientRect.Left, frameClientRect.Top, 0);
            barQuad[1].Position = new Vector3(frameClientRect.Left, frameClientRect.Bottom, 0);
            barQuad[2].Position = new Vector3(frameClientRect.Left + mid, frameClientRect.Top, 0);
            barQuad[3].Position = new Vector3(frameClientRect.Left + mid, frameClientRect.Bottom, 0);

            barQuad[0].Color = Gradient(barColor, 0.90f);
            barQuad[1].Color = Gradient(barColor, 0.00f);
            barQuad[2].Color = Gradient(barColor, 0.90f);
            barQuad[3].Color = Gradient(barColor, 0.00f);

            PositionColor.Draw(BeginMode.TriangleStrip, barQuad);
        }
    }
}
