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
	/// This class wraps the OpenGL Vertex Buffer Object
	/// <remarks>Thread safety - This class must be only be used from the main thread.</remarks>
	/// </summary>
	public class VertexBuffer : IDisposable
	{
		private int vertexHandle;
		private int indexHandle;
		private int numVerts;
		private int numIndices;
		
		private BufferUsageHint bufferUsage = BufferUsageHint.StaticDraw;
		
		private	const int vertexOffset = 0;
		private	const int normalOffset = 3 * VertexStruct.elementSize;
		private	const int vertexAttribOffset = 6 * VertexStruct.elementSize;
		private	const int texCoord0Offset = 7 * VertexStruct.elementSize;

		public VertexBuffer(VertexStruct[] vertices, ushort[] indices)
		{
			if(vertices == null) throw new ArgumentException("Vertices may not be null");
						
			this.numVerts = vertices.Length;
			this.numIndices = indices.Length;
			
			int[] handles = new int[2];
			GL.GenBuffers(2, handles);
			this.vertexHandle = handles[0];
			this.indexHandle = handles[1];

			GL.BindBuffer(BufferTarget.ArrayBuffer, this.vertexHandle);            
			GL.BindBuffer(BufferTarget.ElementArrayBuffer, this.indexHandle);

			int size = numVerts * VertexStruct.strideElements * VertexStruct.elementSize;									
			unsafe
			{
				fixed (float* pVertices = &vertices[0].x)
				{
					GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)size, (IntPtr)pVertices, bufferUsage);
				}
				fixed (ushort* pIndices = &indices[0])
				{
					GL.BufferData(BufferTarget.ElementArrayBuffer, (IntPtr)(numIndices * 2), (IntPtr)pIndices, bufferUsage);
				}
			}						

			GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
			GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
		}
		
		public void Draw(int boneAttribIndex)
		{						
			GL.BindBuffer(BufferTarget.ArrayBuffer, vertexHandle);
			GL.BindBuffer(BufferTarget.ElementArrayBuffer, indexHandle);

			GL.ClientActiveTexture(TextureUnit.Texture0);

			GL.EnableClientState(EnableCap.VertexArray);
			GL.EnableClientState(EnableCap.NormalArray);
			GL.EnableClientState(EnableCap.TextureCoordArray);
			GL.EnableVertexAttribArray(boneAttribIndex);			
			
			GL.VertexPointer(3, VertexPointerType.Float, VertexStruct.stride, (IntPtr)vertexOffset);
			GL.NormalPointer(NormalPointerType.Float, VertexStruct.stride, (IntPtr)normalOffset);
			GL.TexCoordPointer(2, TexCoordPointerType.Float, VertexStruct.stride, (IntPtr)texCoord0Offset);
			GL.VertexAttribPointer(boneAttribIndex, 1, VertexAttribPointerType.Int, false, VertexStruct.stride, (IntPtr)vertexAttribOffset);

			GL.DrawElements(BeginMode.Triangles, numIndices, DrawElementsType.UnsignedShort, IntPtr.Zero); 
			
			GL.DisableClientState(EnableCap.VertexArray);
			GL.DisableClientState(EnableCap.NormalArray);
			GL.DisableClientState(EnableCap.TextureCoordArray);
			GL.DisableVertexAttribArray(boneAttribIndex);
			
			GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
			GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
		}
		
				
		public void Dispose()
		{
			int[] bufferHandles = new int[] { vertexHandle, indexHandle };
			GL.DeleteBuffers(2, bufferHandles);
		}
	}
}
