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
using System.IO;
using System.Diagnostics;

using OpenTK;
using OpenTK.Graphics;

namespace OOGL.Shaders
{
	public abstract class AbstractShader : IDisposable
	{
		public readonly string file; 
		public readonly int handle;
		
		public AbstractShader(string file)
		{
			this.file = file;

			string sourceCode;
			using(StreamReader reader = File.OpenText(this.file))
			{
				sourceCode = reader.ReadToEnd();
			}

			this.handle= GL.CreateShader(this.ShaderType);
								
			GL.ShaderSource(this.handle, sourceCode);
			GL.CompileShader(this.handle);
									
			int[] results = new int[1];
			GL.GetShader(this.handle, ShaderParameter.CompileStatus, results); 
			
			if(results[0] == 0)
			{
				GL.GetShader(this.handle, ShaderParameter.InfoLogLength, results);
				
				string info;				
				GL.GetShaderInfoLog(this.handle, out info);

				throw new Exception(string.Format("Shader error: {0}", info));
			}
		}
		
		public void Dispose()
		{
			if (this.handle != 0)
			{
				GL.DeleteShader(this.handle);
			}
		}
		
		protected abstract ShaderType ShaderType
		{
			get;
		}		
	}
}
