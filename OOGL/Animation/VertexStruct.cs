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
using System.Runtime.InteropServices;

using OpenTK;
using OpenTK.Graphics;

using OOGL.Shaders;

namespace OOGL.Animation
{
	/// <summary>
	/// A custom vertex structure used by the vertex buffer class for rendering.
	/// <remarks>Thread safety - This structure is provides no thread safety guarantees.</remarks>
	/// </summary>	
	[StructLayout (LayoutKind.Sequential)]
	public struct VertexStruct : IComparable<VertexStruct>
	{
		public float x;
		public float y;
		public float z;
		public float nX;
		public float nY;
		public float nZ;
		public int	boneIndex;
		public float s;
		public float t;
		
		public const int elementSize = sizeof(float);
		public const int strideElements = 9;
		public const int stride = strideElements * elementSize;
		
		public VertexStruct(float x, float y, float z, float nX, float nY, float nZ,  float s, float t, int boneIndex)
		{
			this.x = x;
			this.y = y;
			this.z = z;
			this.nX = nX;
			this.nY = nY;
			this.nZ = nZ;
			this.s = s;
			this.t = t;
			this.boneIndex = boneIndex;
		}
				
		public VertexStruct(Vector3 vertex, Vector3 normal,  float s, float t, int boneIndex)
		{
			this.x = vertex.X;
			this.y = vertex.Y;
			this.z = vertex.Z;
			this.nX = normal.X;
			this.nY = normal.Y;
			this.nZ = normal.Z;
			this.s = s;
			this.t = t;
			this.boneIndex = boneIndex;
		}

		public Vector3 Position
		{
			get
			{
				return new Vector3(x, y, z);
			}
			set
			{
				this.x = value.X;
				this.y = value.Y;
				this.z = value.Z;
			}
		}
		
		public Vector3 Normal
		{
			get
			{
				return new Vector3(nX, nY, nZ);
			}
			set
			{
				this.nX = value.X;
				this.nY = value.Y;
				this.nZ = value.Z;
			}
		}
		
		public Vector2 TextureCoordinate
		{
			get
			{
				return new Vector2(s, t);
			}
			set
			{
				this.s = value.X;
				this.t = value.Y;
			}
		}
		
		public int BoneIndex
		{
			get
			{
				return boneIndex;
			}
			set
			{
				boneIndex = value;
			}
		}
				
		public int CompareTo(VertexStruct other)
		{
			if(x > other.x) return 1;
			if(x < other.x) return -1;
			if(y > other.y) return 1;
			if(y < other.y) return -1;
			if(z > other.z) return 1;
			if(z < other.z) return -1;

			if(s > other.s) return 1;
			if(s < other.s) return -1;
			if(t > other.t) return 1;
			if(t < other.t) return -1;

			if(boneIndex > other.boneIndex) return 1;
			if(boneIndex < other.boneIndex) return -1;

			if(nX > other.nX) return 1;
			if(nX < other.nX) return -1;
			if(nY > other.nY) return 1;
			if(nY < other.nY) return -1;
			if(nZ > other.nZ) return 1;
			if(nZ < other.nZ) return -1;
			
			return 0;
		}
	}
}
