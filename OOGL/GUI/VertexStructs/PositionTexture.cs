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

// PositionTexture.cs created with MonoDevelop
// User: James P Michels III at 9:43 PM 5/8/2008
//

using System;
using System.Runtime.InteropServices;

using OpenTK;
using OpenTK.Graphics;

using OOGL.Shaders;

namespace OOGL.GUI.VertexStructures
{	
	[StructLayout (LayoutKind.Sequential)]
	public struct PositionTexture
	{
#pragma warning disable 0414
		float x;
		float y;
		float z;
		float s;
		float t;
#pragma warning restore 0414
		
		private const int elementSize = sizeof(float);
		private const int strideElements = 5;
		private const int stride = strideElements * elementSize;
	
		public PositionTexture(float x, float y, float z, float s, float t)
		{
			this.x = x;
			this.y = y;
			this.z = z;
			this.s = s;
			this.t = t;
		}
		
		public PositionTexture(Vector3 vertex, Vector2 texture)
		{
			this.x = vertex.X;
			this.y = vertex.Y;
			this.z = vertex.Z;
			
			this.s = texture.X;
			this.t = texture.Y;
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
		
		public Vector2 TextureCoordinate
		{
			set
			{
				this.s = value.X;
				this.t = value.Y;
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

        public static void Draw(BeginMode beginMode, PositionTexture[] vertexData, uint handleTexture)
        {
            int primativeCount;
            switch (beginMode)
            {
                case BeginMode.Triangles: primativeCount = vertexData.Length / 3; break;
                case BeginMode.TriangleStrip: primativeCount = vertexData.Length - 2; break;
                default: throw new ArgumentException();
            }
            if (primativeCount == 0) return;


            GL.ActiveTexture(TextureUnit.Texture0);
            GL.Enable(EnableCap.Texture2D);
            GL.BindTexture(TextureTarget.Texture2D, handleTexture);
            
            GL.EnableClientState(EnableCap.VertexArray);

            GL.ClientActiveTexture(TextureUnit.Texture0);
            GL.EnableClientState(EnableCap.TextureCoordArray);

            shader.Use();
            shader.SetSamplerUniform("sampler0", 0);

            unsafe
            {
                fixed (float* pData = &vertexData[0].x)
                {
                    GL.VertexPointer(3, VertexPointerType.Float, PositionTexture.stride, (IntPtr)pData);
                    GL.TexCoordPointer(2, TexCoordPointerType.Float, PositionTexture.stride, (IntPtr)(pData + 3));

                    GL.DrawArrays(beginMode, 0, vertexData.Length);
                }
            }

            GL.DisableClientState(EnableCap.VertexArray);
            GL.DisableClientState(EnableCap.TextureCoordArray);

            //GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            //GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);

            GL.Disable(EnableCap.Texture2D);
        }
	}
}
