//    Copyright 2008 James P Michels III
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published by
//    the Free Software Foundation.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

using System;

using OpenTK;

using OOGL.Textures;

namespace OOGL.Animation
{
	/// <summary>
	/// Material used in model rendering
	/// <remarks>Thread safety - This class must be only be used from the main thread.</remarks>
	/// </summary>
	public class Material
	{
		public readonly Texture texture;		

		public readonly Vector4 ambient;
		public readonly Vector4 diffuse;
		public readonly Vector4 specular;
		public readonly Vector4 emissive;
		public readonly float shininess;
		public readonly float transparency;
		
		public Material(Texture texture, Vector4 ambient, Vector4 diffuse, Vector4 specular, Vector4 emissive, float shininess, float transparency)
		{
			this.texture = texture;
			this.ambient = ambient;
			this.diffuse = diffuse;
			this.specular = specular;
			this.emissive = emissive;
			this.shininess = shininess;
			this.transparency = transparency;
		}
	}
}
