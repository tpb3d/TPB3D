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

namespace OOGL
{
	public static class Matrix4Helper
	{
		public static Matrix4 CreateOrthographicProjection(float left, float right, float top, float bottom, float near, float far)
		{
			float invRL = 1 / (right - left);
			float invTB = 1 / (top - bottom);
			float invFN = 1 / (far - near);
			
			float m11 = 2 * invRL;
			float m22 = 2 * invTB;
			float m33 = -2 * invFN;
			
			float m41 = - (right + left) * invRL;
			float m42 = - (top + bottom) * invTB;
			float m43 = - (far + near) * invFN;
		
			return new Matrix4
			(
				new Vector4(m11,   0,   0,   0),
				new Vector4(  0, m22,   0,   0),
				new Vector4(  0,   0, m33,   0),
				new Vector4(m41, m42, m43,   1)			
			);	
		}
		
		public static void ToOpenGL(Matrix4[] source, ref float[] destination)
		{
			if (destination == null || destination.Length != source.Length * 16)
			{
				destination = new float[source.Length * 16];
			}
			for(int i = 0; i < source.Length; i++)
			{
				int j = i * 16;
				
				destination[j + 00] = source[i].Column0.X;
				destination[j + 01] = source[i].Column1.X;
				destination[j + 02] = source[i].Column2.X;
				destination[j + 03] = source[i].Column3.X;
				destination[j + 04] = source[i].Column0.Y;
				destination[j + 05] = source[i].Column1.Y;
				destination[j + 06] = source[i].Column2.Y;
				destination[j + 07] = source[i].Column3.Y;
				destination[j + 08] = source[i].Column0.Z;
				destination[j + 09] = source[i].Column1.Z;
				destination[j + 10] = source[i].Column2.Z;
				destination[j + 11] = source[i].Column3.Z;
				destination[j + 12] = source[i].Column0.W;
				destination[j + 13] = source[i].Column1.W;
				destination[j + 14] = source[i].Column2.W;
				destination[j + 15] = source[i].Column3.W;
			}
		}
		
		public static void ToOpenGL(Matrix4 source, ref float[] destination)
		{
			if (destination == null || destination.Length != 16)
			{
				destination = new float[16];
			}
				
			destination[0] = source.Column0.X;
			destination[1] = source.Column1.X;
			destination[2] = source.Column2.X;
			destination[3] = source.Column3.X;
			destination[4] = source.Column0.Y;
			destination[5] = source.Column1.Y;
			destination[6] = source.Column2.Y;
			destination[7] = source.Column3.Y;
			destination[8] = source.Column0.Z;
			destination[9] = source.Column1.Z;
			destination[10] = source.Column2.Z;
			destination[11] = source.Column3.Z;
			destination[12] = source.Column0.W;
			destination[13] = source.Column1.W;
			destination[14] = source.Column2.W;
			destination[15] = source.Column3.W;
		}
		
		private static float[] matrixBuffer = new float[16];
		public static float[] ToOpenGL(Matrix4 source)
		{
			ToOpenGL(source, ref matrixBuffer);
			return matrixBuffer;
		}
	}
}
