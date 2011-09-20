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
using OpenTK;

using OOGL.Shaders;

namespace OOGL.Animation
{
	/// <summary>
	/// A 3d model capable of skeletal animation
	/// <remarks>Thread safety - This class must be only be used from the main thread.</remarks>
	/// </summary>
	public class Model
	{	
		public readonly ShaderProgram shader;
		public readonly Group[] groups;
		public readonly Bone[] bones;
		
		public readonly Matrix4[] vertexTransformations;
		
		private const string vertexTransformationsUniformName = "vertexTransformations";
		private const string lightPos0UniformName = "lightPos0";
		private const string sampler0UniformName = "sampler0";
		private const string boneAttributeName = "boneAttribute";
		private const int maxBones = 40;
		
		private readonly int boneAttribIndex;

        public readonly Sample[] samples;

		public Model(ShaderProgram shader, Group[] groups, Bone[] bones, Sample[] samples)
		{
			this.shader = shader;
			this.groups = groups;
			this.bones = bones;
            this.samples = samples;
			
			this.vertexTransformations = new Matrix4[maxBones];
			for (int i = 0; i < maxBones ; i++ ) 
			{
				this.vertexTransformations[i] = Matrix4.Identity;
			}
			
			Console.WriteLine(string.Format("Model created with {0} bones and {1} groups.", bones.Length, groups.Length));
			
			shader.Use();
			shader.SetSamplerUniform(sampler0UniformName, 0);
			this.boneAttribIndex = shader.FindAttribIndex(boneAttributeName);
		}
				
		private float[] vertexTransformationsBuffer;
		public void UpdateBoneTransformations(Track[] tracks)
		{
			for (int i = 0; i < this.vertexTransformations.Length && i < this.bones.Length; i++ ) 
			{
                Matrix4 blended = new Matrix4();
                float sumWeights = 0;
                if (tracks != null)
                {
                    for (int j = 0; j < tracks.Length; j++)
                    {
                        Matrix4 trackMatrix = this.bones[i].GetAnimationMatrix(tracks[j].Time);
                        float trackWeight = tracks[j].Weight;

                        blended.Row0 += trackMatrix.Row0 * trackWeight;
                        blended.Row1 += trackMatrix.Row1 * trackWeight;
                        blended.Row2 += trackMatrix.Row2 * trackWeight;
                        blended.Row3 += trackMatrix.Row3 * trackWeight;
                        sumWeights += trackWeight;
                    }

                    blended.Row0 /= sumWeights;
                    blended.Row1 /= sumWeights;
                    blended.Row2 /= sumWeights;
                    blended.Row3 /= sumWeights;
                }

				this.vertexTransformations[i] = Matrix4.Invert(this.bones[i].globalTransformationMatrix) * blended;
			}			
			
			Matrix4Helper.ToOpenGL(vertexTransformations, ref vertexTransformationsBuffer);
			shader.SetMatrix4(vertexTransformationsUniformName, vertexTransformationsBuffer);			
		}
		
		public void Draw(Controller controller, float elapsedTime, Matrix4 modelViewMatrix)
		{
			shader.Use();

			if(controller != null)
			{
            	controller.Update(elapsedTime);

				UpdateBoneTransformations(controller.Tracks);
			}
			
			GL.MatrixMode(MatrixMode.Modelview);
			GL.LoadMatrix(Matrix4Helper.ToOpenGL(modelViewMatrix));
						
			GL.ActiveTexture(TextureUnit.Texture0);
			foreach(Group group in groups)
			{
				group.LoadMaterials();
				group.vertexBuffer.Draw(this.boneAttribIndex);
			}
		}

        public int FindSampleIndex(string name)
        {
            if (samples == null) return -1;
            for (int i = 0; i < samples.Length; i++)
            {
                if (samples[i].name == name) return i;
            }
            return -1;
        }
    }
}
