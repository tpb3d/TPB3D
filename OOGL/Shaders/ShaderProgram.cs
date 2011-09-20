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
using System.Collections.Generic;
using System.Diagnostics;

using OpenTK.Graphics;
using OpenTK;

namespace OOGL.Shaders
{
	public class ShaderProgram : IDisposable
	{		
		private readonly int handle; 
		private readonly VertexShader vertexShader;
		private readonly FragmentShader fragmentShader;
		
		public ShaderProgram(string vertexShaderFile, string fragmentShaderFile)
		{
			Trace.WriteLine(string.Format("Loading vertex shader {0}", vertexShaderFile));
			this.vertexShader = new VertexShader(vertexShaderFile);

			Trace.WriteLine(string.Format("Loading fragment shader {0}", fragmentShaderFile));
			this.fragmentShader = new FragmentShader(fragmentShaderFile);
			
			this.handle = GL.CreateProgram();
			
			GL.AttachShader(this.handle, this.vertexShader.handle);
			GL.AttachShader(this.handle, this.fragmentShader.handle);
			GL.LinkProgram(this.handle);
						
			int[] results = new int[1];
			GL.GetProgram(this.handle, ProgramParameter.LinkStatus, results);
			
			if (results[0] == 0 )
			{
				GL.GetProgram(this.handle, ProgramParameter.InfoLogLength, results);
				
				System.Text.StringBuilder infoLog = new System.Text.StringBuilder(results[0]);
				int length;
				GL.GetProgramInfoLog(this.handle, results[0], out length, infoLog);
				
				throw new Exception(string.Format("Shader program link failed: {0}", infoLog));
			}
			
			GL.ValidateProgram(this.handle);
			GL.GetProgram(this.handle, ProgramParameter.ValidateStatus, results);
			if (results[0] == 0 )
			{
				GL.GetProgram(this.handle, ProgramParameter.InfoLogLength, results);
				
				System.Text.StringBuilder infoLog = new System.Text.StringBuilder(results[0]);
				int length;
				GL.GetProgramInfoLog(this.handle, results[0], out length, infoLog);

				throw new Exception(string.Format("Shader program validate failed: {0}", infoLog));
			}
		}
		
		public void Use()
		{
			GL.UseProgram(this.handle);
			// TODO check for errors
		}
		
		public static void UseDefault()
		{
			GL.UseProgram(0);
		}
		
		public void Dispose()
		{
			GL.DetachShader(this.handle, this.vertexShader.handle);
			this.vertexShader.Dispose();
			
			GL.DetachShader(this.handle, this.fragmentShader.handle);
			this.fragmentShader.Dispose();
						
			GL.DeleteProgram(this.handle);
		}
		
		private Dictionary<string, int> uniformLocations = new Dictionary<string,int>();
		private int FindUniformLocation(string name)
		{
			int location;
			if(uniformLocations.TryGetValue(name, out location)) return location;
			
			location = GL.GetUniformLocation(this.handle, name);
			if( location == -1)
			{
				throw new Exception(string.Format("Unable to find uniform variable {0}", name));
			}
			
			uniformLocations[name] = location;
			
			return location;
		}
		
		private Dictionary<string, int> attribIndecies = new Dictionary<string,int>();
		public int FindAttribIndex(string name)
		{
			int index;
			if(attribIndecies.TryGetValue(name, out index)) return index;
			
			index = GL.GetAttribLocation(this.handle, name);
			
			attribIndecies[name] = index;
			
			return index;
		}
		
		public void SetSamplerUniform(string name, int sampler)
		{
			GL.Uniform1(FindUniformLocation(name), sampler);
		}
		
		public void SetSamplerUniform(string name, uint sampler)
		{
			GL.Uniform1(FindUniformLocation(name), sampler);
		}

		[Obsolete]
		public void SetMatrix(string name, Matrix4 value)
		{
			float[] matrix = new float[]
            {
            	value.Column0.X, value.Column1.X, value.Column2.X, value.Column3.X,
            	value.Column0.Y, value.Column1.Y, value.Column2.Y, value.Column3.Y,
            	value.Column0.Z, value.Column1.Z, value.Column2.Z, value.Column3.Z,
            	value.Column0.W, value.Column1.W, value.Column2.W, value.Column3.W,
            };

			GL.UniformMatrix4(FindUniformLocation(name), 1, false, matrix); 
		}
		
		public void SetMatrix4(string name, float[] values)
		{
			int count = values.Length / 16;
			if(count <= 0) return;
			
			GL.UniformMatrix4(FindUniformLocation(name), count, false, values);
		}

		public void SetMatrix3(string name, float[] values)
		{
			int count = values.Length / 9;
			if(count <= 0) return;
			
			GL.UniformMatrix3(FindUniformLocation(name), count, false, values);
		}

		public void SetVector3(string name, Vector3 value)
		{
			GL.Uniform3(FindUniformLocation(name), value.X, value.Y, value.Z);
		}

        public void SetFloat(string name, float value)
        {
            GL.Uniform1(FindUniformLocation(name), value);
        }
	}
}
