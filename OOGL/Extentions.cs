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

using OpenTK.Graphics;

namespace OOGL
{
	public static class Extentions
	{
		private static string[] extensions;
		
		public static bool IsAvailable(string extention)
		{
			if(Extentions.extensions == null)
			{
        		string[] extensions = GL.GetString(StringName.Extensions).Split(' ');
        		Array.Sort<string>(extensions);
        		Extentions.extensions = extensions;
			}
			
			return Array.BinarySearch<string>(Extentions.extensions, extention) >= 0;
		}
	
		public const string ArbTextureNonPowerOfTwo = "GL_ARB_texture_non_power_of_two";
	}
}
