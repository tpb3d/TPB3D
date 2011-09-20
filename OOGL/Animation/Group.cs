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

using OpenTK.Graphics;

namespace OOGL.Animation
{
	/// <summary>
	/// The Group class hold material information for similiar vertexes.
	/// <remarks>Thread safety - This class must be only be used from the main thread.</remarks>
	/// </summary>
	public class Group
	{		
		public readonly string name;
		public readonly Material material;
		public readonly VertexStruct[] vertices;
		public readonly ushort[] indices;
	
		public readonly VertexBuffer vertexBuffer;
		
		public Group(string name, Material material, VertexStruct[] vertices, ushort[] indices)
		{
			this.name = name;
			this.material = material;
			this.vertices = vertices;
			this.indices = indices;
			
			this.vertexBuffer = new VertexBuffer(vertices, indices);
		}
		
		public void LoadMaterials()
		{
			GL.BindTexture(TextureTarget.Texture2D, material.texture.handle);
			GL.Material(MaterialFace.FrontAndBack, MaterialParameter.Ambient, material.ambient);
			GL.Material(MaterialFace.FrontAndBack, MaterialParameter.Diffuse, material.diffuse);
			GL.Material(MaterialFace.FrontAndBack, MaterialParameter.Emission, material.emissive);
			GL.Material(MaterialFace.FrontAndBack, MaterialParameter.Specular, material.specular);
			GL.Material(MaterialFace.FrontAndBack, MaterialParameter.Shininess, material.shininess);			
			
			// TODO Fix
//			GL.Materialv(MaterialFace.FrontAndBack, MaterialParameter.Specular, new float[] {1.0f, 1.0f, 1.0f, 1.0f});
//			GL.Material(MaterialFace.FrontAndBack, MaterialParameter.Shininess, 32.0f);
		}
	}
}
