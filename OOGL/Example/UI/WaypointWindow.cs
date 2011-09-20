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
    internal class WaypointWindow : BaseFrame
    {
        public Button btnAdd;
        public Button btnDelete;
        public ListBox lstWaypoint;
		public Textbox txtStatus;

        public WaypointWindow(BaseFrameMgr frameMgr)
            : base(frameMgr, 2, "Waypoint")
        {
            Text = "Waypoints";
            Location = new Point(75, 75);
            Size = new Size(100, 50);
            BorderSize = 1;

            lstWaypoint.Items = new string[] { "ListItem0", "ListItem1", "ListItem2", "ListItem3", "ListItem4", "ListItem5", "ListItem6", "ListItem7", "ListItem8" };
        }

        public override void InitializeControls()
        {
            base.InitializeControls();

            this.btnAdd = new Button(frameMgr, this);
            this.btnAdd.Text = "Add";
            this.btnAdd.BorderSize = 1;
            this.btnAdd.Size = new Size(10, 20);
            AddChildControl(this.btnAdd);

            this.btnDelete = new Button(frameMgr, this);
            this.btnDelete.Text = "Delete";
            this.btnDelete.BorderSize = 1;
            this.btnDelete.Size = new Size(10, 20);
            AddChildControl(this.btnDelete);

            this.lstWaypoint = new ListBox(frameMgr, this);
            this.lstWaypoint.BorderSize = 0;
            AddChildControl(this.lstWaypoint);
			
			this.txtStatus = new Textbox(frameMgr, this);
			this.txtStatus.BorderSize = 1;
			AddChildControl(this.txtStatus);
        }

        public override void OnResize()
        {
            base.OnResize();

            int btnWidth = (clientRectangle.Width - 3) / 2;
            int btnHeight = btnAdd.Height;
			
			int resizeHeight = clientRectangle.Height - (btnHeight + 2);
			int waypointHeight = resizeHeight / 2;
			int statusHeight = resizeHeight - waypointHeight;

            btnAdd.Location = new Point(1, 1);
            btnAdd.Size = new Size(btnWidth, btnHeight);

            btnDelete.Location = new Point(1 + btnWidth + 1, 1);
            btnDelete.Size = new Size(btnWidth, btnHeight);

            lstWaypoint.Location = new Point(1, 1 + btnHeight + 1);
            lstWaypoint.Size = new Size(clientRectangle.Width - 2, waypointHeight);
			
			txtStatus.Location = new Point(1, 1 + btnHeight + 1 + waypointHeight + 1);
			txtStatus.Size = new Size(clientRectangle.Width - 2, statusHeight);
		}

        private DateTime nextUpdate = DateTime.Now;

        public override void Update(double gameTime)
        {
            if (DateTime.Now > nextUpdate)
            {
                nextUpdate = DateTime.Now.AddSeconds(5);
                NeedUpdate();

                lstWaypoint.ClearItems();
				
				DateTime now = DateTime.Now;
				txtStatus.Text = string.Format("Hour = {0}\nMinute = {1}\nSecond = {2}", now.Hour, now.Minute, now.Second);
            }

            base.Update(gameTime);
        }
    }
}
