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

using OOGL.Textures;

namespace OOGL.GUI.Widgets
{
    public class Picture : BaseControl
    {
        private PositionTexture[] quad = new PositionTexture[4];

        public Picture(BaseFrameMgr frameMgr, BaseControl parent)
            : base(frameMgr, parent)
        {
        }

        private Texture texture;
        public Texture Texture
        {
            get
            {
                return texture;
            }
            set
            {
                texture = value;
                NeedUpdate();
            }
        }

        public override void DrawToFrameBuffer(double gameTime)
        {
            base.DrawToFrameBuffer(gameTime);

            Rectangle frameClientRect = ScreenToFrame(ClientToScreen(clientRectangle));

            quad[0].Position = new Vector3(frameClientRect.Left, frameClientRect.Top, 0f);
            quad[1].Position = new Vector3(frameClientRect.Left, frameClientRect.Bottom, 0f);
            quad[2].Position = new Vector3(frameClientRect.Right, frameClientRect.Top, 0f);
            quad[3].Position = new Vector3(frameClientRect.Right, frameClientRect.Bottom, 0f);

			quad[0].TextureCoordinate = new Vector2(0, 1);
			quad[1].TextureCoordinate = new Vector2(0, 0);
			quad[2].TextureCoordinate = new Vector2(1, 1);
			quad[3].TextureCoordinate = new Vector2(1, 0);

            PositionTexture.Draw(BeginMode.TriangleStrip, quad, texture.handle);
        }
    }
}
