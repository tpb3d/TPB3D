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

using OOGL;
using OOGL.Textures;
using OOGL.GUI.Abstract;
using OOGL.GUI.Widgets;

using OpenTK.Graphics;

namespace Example
{
	public class DemoWindow : BaseFrame
	{	
		private ProgressBar progressBar;
		private Button button;
		private Picture picture;
		private VScrollBar vScrollBar;
		
		public DemoWindow(BaseFrameMgr frameMgr) : base (frameMgr, 0, "DemoWindow")
		{
			this.Location = new Point(10 ,10);
			this.Size = new Size(400, 400);				
		}
		
		public override void InitializeControls ()
		{
			base.InitializeControls();
			
			Texture texture = TextureManager.Instance.Find(ResourceLocator.GetFullPath("Planets/Earth/earth.dds"), TextureMagFilter.Nearest, TextureMinFilter.Nearest, TextureWrapMode.Clamp, TextureWrapMode.Clamp);
			
			this.progressBar = new ProgressBar(this.frameMgr, this);
			this.progressBar.Location = new Point(10, 10);
			this.progressBar.Size = new Size(200, 20);
			this.progressBar.Value = 75;
			this.progressBar.BorderSize = 1;
			AddChildControl(this.progressBar);
			
			this.button = new Button(this.frameMgr, this);
			this.button.Location = new Point(10, 40);
			this.button.Size = new Size(100,25);
			this.button.BorderSize = 1;
			AddChildControl(this.button);
						
			this.picture = new Picture(this.frameMgr, this);
			this.picture.Location = new Point(10, 70);
			this.picture.Size = new Size(200, 200);
			this.picture.BorderSize = 1;
			this.picture.Texture = texture;			
			AddChildControl(this.picture);
			
			this.vScrollBar = new VScrollBar(this.frameMgr, this);
			this.vScrollBar.Location = new Point(220, 10);
			this.vScrollBar.Size = new Size(40, 260);
			AddChildControl(this.vScrollBar);			
		}
	}
}
