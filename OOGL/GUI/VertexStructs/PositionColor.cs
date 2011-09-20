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

// PositionColor.cs created with MonoDevelop
// User: James P Michels III at 9:57 PM 5/8/2008
//

using System;
using System.Drawing;
using System.Runtime.InteropServices;

using OpenTK;
using OpenTK.Graphics;

using OOGL.Shaders;

namespace OOGL.GUI
{
	[StructLayout (LayoutKind.Sequential)]
	public struct PositionColor
	{
#pragma warning disable 0414
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;
#pragma warning restore 0414
		
		private const int elementSize = sizeof(float);
		private const int strideElements = 6;
		private const int stride = strideElements * elementSize;
	
		public PositionColor(float x, float y, float z, Color c)
		{
			this.x = x;
			this.y = y;
			this.z = z;

			this.r = c.R / 255.0f;
			this.g = c.G / 255.0f;
			this.b = c.B / 255.0f;
		}
		
		public PositionColor(Vector3 vertex, Color c)
		{
			this.x = vertex.X;
			this.y = vertex.Y;
			this.z = vertex.Z;
			
			this.r = c.R / 255.0f;
			this.g = c.G / 255.0f;
			this.b = c.B / 255.0f;
		}
		
		public Vector3 Position
		{
			set
			{
				this.x = value.X;
				this.y = value.Y;
				this.z = value.Z;
			}
		}

		public Color Color
		{
			set
			{
				this.r = value.R / 255.0f;
				this.g = value.G / 255.0f;
				this.b = value.B / 255.0f;
			}
		}

        private static ShaderProgram shader;
        public static ShaderProgram Shader
        {
            get
            {
                return shader;
            }
            set
            {
                shader = value;
            }
        }

        public static void Draw(BeginMode beginMode, PositionColor[] vertexData)
        {
            int primativeCount;
            switch (beginMode)
            {
                case BeginMode.Triangles: primativeCount = vertexData.Length / 3; break;
                case BeginMode.TriangleStrip: primativeCount = vertexData.Length - 2; break;
                default: throw new ArgumentException();
            }
            if (primativeCount == 0) return;

            GL.EnableClientState(EnableCap.VertexArray);
            GL.EnableClientState(EnableCap.ColorArray);

            shader.Use();

            unsafe
            {
                fixed (float* pData = &vertexData[0].x)
                {
                    GL.VertexPointer(3, VertexPointerType.Float, PositionColor.stride, (IntPtr)pData);
                    GL.ColorPointer(3, ColorPointerType.Float, PositionColor.stride, (IntPtr)(pData + 3));

                    GL.DrawArrays(beginMode, 0, vertexData.Length);
                }
            }

            GL.DisableClientState(EnableCap.VertexArray);
            GL.DisableClientState(EnableCap.ColorArray);

            //GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            //GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
        }
	}
}
