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

using OOGL;
using OOGL.Textures;
using OOGL.GUI;
using OOGL.GUI.Abstract;
using OOGL.GUI.Widgets;

namespace Example
{
    internal class RadarWindow : BaseFrame
    {
        private CheckBox shortRange;
        private CheckBox mediumRange;
        private CheckBox longRange;
        private Picture radar;
        private ComboBox comboBox;

        public RadarWindow(BaseFrameMgr frameMgr)
            : base(frameMgr, 1, "Radar")
        {
            BackgroundColor = Color.PaleGoldenrod;
            BorderColor = Color.PaleGoldenrod;
            TitleColor = Color.PaleGoldenrod;
            Location = new Point(200, 200);
            Size = new Size(100, 100);
            Text = "Radar";
        }

        public override void InitializeControls()
        {
            base.InitializeControls();

			Texture texture = TextureManager.Instance.Find(ResourceLocator.GetFullPath("Textures/Radar.dds"), TextureMagFilter.Nearest, TextureMinFilter.Nearest, TextureWrapMode.Clamp, TextureWrapMode.Clamp); 

            this.radar = new Picture(frameMgr, this);
            this.radar.BorderSize = 2;
            this.radar.Texture = texture;
            AddChildControl(this.radar);

            int checkBoxWidth = 60;

            this.shortRange = new CheckBox(frameMgr, this);
            this.shortRange.ControlRectangle = new Rectangle(0 * (checkBoxWidth + 1), 1, checkBoxWidth, 20);
            this.shortRange.Text = "Short";
            this.shortRange.BorderSize = 1;
            this.shortRange.Value = true;
            this.shortRange.ValueChanged += new EventHandler(shortRange_ValueChanged);
            AddChildControl(this.shortRange);

            this.mediumRange = new CheckBox(frameMgr, this);
            this.mediumRange.ControlRectangle = new Rectangle(1 * (checkBoxWidth + 1), 1, checkBoxWidth, 20);
            this.mediumRange.Text = "Medium";
            this.mediumRange.BorderSize = 1;
            this.mediumRange.ValueChanged += new EventHandler(mediumRange_ValueChanged);
            AddChildControl(this.mediumRange);

            this.longRange = new CheckBox(frameMgr, this);
            this.longRange.ControlRectangle = new Rectangle(2 * (checkBoxWidth + 1), 1, checkBoxWidth, 20);
            this.longRange.Text = "Long";
            this.longRange.BorderSize = 1;
            this.longRange.ValueChanged += new EventHandler(longRange_ValueChanged);
            AddChildControl(this.longRange);

            this.comboBox = new ComboBox(frameMgr, this);
            this.comboBox.ControlRectangle = new Rectangle(3 * (checkBoxWidth + 1), 1, checkBoxWidth * 2, 20);
            this.comboBox.Text = "ComboBox";
            this.comboBox.BorderSize = 1;
            this.comboBox.Items = new string[] { "Test1", "Test2", "Test3" };
            this.comboBox.SelectedIndexChanged += new EventHandler(comboBox_SelectedIndexChanged);
            AddChildControl(this.comboBox);

        }

        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int selectedIndex = comboBox.SelectedIndex;
            if (selectedIndex == 0)
            {
                Game.Instance.SetPolygonMode(PolygonMode.Fill);
            }
            else if (selectedIndex == 1)
            {
                Game.Instance.SetPolygonMode(PolygonMode.Line);
            }
            else
            {
                Game.Instance.SetPolygonMode(PolygonMode.Point);
            }

        }

        private void longRange_ValueChanged(object sender, EventArgs e)
        {
            if (longRange.Value)
            {
                shortRange.Value = false;
                mediumRange.Value = false;
            }
            Game.Instance.SetPolygonMode(PolygonMode.Point);
        }

        private void mediumRange_ValueChanged(object sender, EventArgs e)
        {
            if (mediumRange.Value)
            {
                shortRange.Value = false;
                longRange.Value = false;
            }
            Game.Instance.SetPolygonMode(PolygonMode.Line);
        }

        private void shortRange_ValueChanged(object sender, EventArgs e)
        {
            if (shortRange.Value)
            {
                mediumRange.Value = false;
                longRange.Value = false;
            }
            Game.Instance.SetPolygonMode(PolygonMode.Fill);
        }

        public override void OnResize()
        {
            base.OnResize();

            //Rectangle screenClientRect = ClientToScreen(clientRectangle);
            this.radar.ControlRectangle = new Rectangle(5, shortRange.Height + 6, clientRectangle.Width - 10, clientRectangle.Height - (shortRange.Height + 11));
        }
    }
}
