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

using OOGL.GUI;
using OOGL.GUI.Abstract;
using OOGL.GUI.Widgets;

namespace Example
{
    internal class PlayerWindow : BaseFrame
    {
        private ProgressBar pgrHealth;
        private ProgressBar pgrMechHead;
        private ProgressBar pgrMechBody;
        private ProgressBar pgrMechLeftArm;
        private ProgressBar pgrMechRightArm;
        private ProgressBar pgrMechLeftLeg;
        private ProgressBar pgrMechRightLeg;

        private Label lblHealth;
        private Label lblMechHead;
        private Label lblMechBody;
        private Label lblMechLeftArm;
        private Label lblMechRightArm;
        private Label lblMechLeftLeg;
        private Label lblMechRightLeg;

        public PlayerWindow(BaseFrameMgr frameMgr)
            : base(frameMgr, 0, "Player")
        {
            Location = new Point(100, 100);
            Size = new Size(100, 100);
            Text = "Player Name";
            BorderSize = 0;
            BackgroundColor = Color.Silver;
        }

        public override void InitializeControls()
        {
            base.InitializeControls();

            InitHelper(out lblHealth, out pgrHealth, 0, "Health", 100, Color.Red, Color.LightSalmon, Color.Silver);
            InitHelper(out lblMechHead, out pgrMechHead, 1, "Mech Head", 95, Color.SteelBlue, Color.LightSteelBlue, Color.Silver);
            InitHelper(out lblMechBody, out pgrMechBody, 2, "Mech Body", 35, Color.SteelBlue, Color.LightSteelBlue, Color.Silver);
            InitHelper(out lblMechLeftArm, out pgrMechLeftArm, 3, "Mech Left Arm", 70, Color.SteelBlue, Color.LightSteelBlue, Color.Silver);
            InitHelper(out lblMechRightArm, out pgrMechRightArm, 4, "Mech Right Arm", 99, Color.SteelBlue, Color.LightSteelBlue, Color.Silver);
            InitHelper(out lblMechLeftLeg, out pgrMechLeftLeg, 5, "Mech Left Leg", 1, Color.SteelBlue, Color.LightSteelBlue, Color.Silver);
            InitHelper(out lblMechRightLeg, out pgrMechRightLeg, 6, "Mech Right Leg", 10, Color.SteelBlue, Color.LightSteelBlue, Color.Silver);
        }

        public override void OnResize()
        {
            base.OnResize();

            int rows = 7;
            ResizeHelper(lblHealth, pgrHealth, 0, rows);
            ResizeHelper(lblMechHead, pgrMechHead, 1, rows);
            ResizeHelper(lblMechBody, pgrMechBody, 2, rows);
            ResizeHelper(lblMechLeftArm, pgrMechLeftArm, 3, rows);
            ResizeHelper(lblMechRightArm, pgrMechRightArm, 4, rows);
            ResizeHelper(lblMechLeftLeg, pgrMechLeftLeg, 5, rows);
            ResizeHelper(lblMechRightLeg, pgrMechRightLeg, 6, rows);
        }

        private void InitHelper(out Label label, out ProgressBar bar, int row, string text, int value, Color barColor, Color barBack, Color textBack)
        {
            int borderSize = 0;
            //int spacer = 2;
            //int textWidth = 100;
            //int barLeftEdge = (2 * spacer) + textWidth;

            label = new Label(frameMgr, this);
            label.Text = text;
            label.BorderSize = 0;
            label.DrawTextFormat = DrawTextFormat.Right | DrawTextFormat.VerticalCenter;
            label.BackgroundColor = textBack;
            AddChildControl(label);

            bar = new ProgressBar(frameMgr, this);
            bar.BorderSize = borderSize;
            bar.BackgroundColor = barBack;
            bar.BarColor = barColor;
            bar.Value = value;
            AddChildControl(bar);

            ResizeHelper(label, bar, row, 7);
        }

        private void ResizeHelper(Label label, ProgressBar bar, int row, int rows)
        {
            int clientWidth = clientRectangle.Width;
            int clientHeight = clientRectangle.Height;

            int spacer = 2;
            int spacer2 = spacer * 2;
            int textWidth = 100;
            int barLeftEdge = spacer2 + textWidth;

            int rowHeight = (clientHeight - (spacer * (rows + 1))) / rows;
            if (rowHeight < 5) rowHeight = 5;

            int barWidth = (clientWidth - spacer) - barLeftEdge;
            if (barWidth < 5) barWidth = 5;

            label.Location = new Point(spacer, spacer + (row * (rowHeight + spacer)));
            label.Size = new Size(textWidth, rowHeight);

            bar.Location = new Point(barLeftEdge, spacer + (row * (rowHeight + spacer)));
            bar.Size = new Size(barWidth, rowHeight);
        }

        public override void Update(double gameTime)
        {
            pgrHealth.Value = (int)Game.Instance.ActualFps;

            base.Update(gameTime);
        }
    }
}
