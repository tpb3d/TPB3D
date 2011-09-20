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

using OpenTK;

namespace OOGL.Animation
{
	/// <summary>
	/// Bones used in skeletal animation
	/// <remarks>Thread safety - This class is thread safe.</remarks>
	/// </summary>
	public class Bone
	{	
		public readonly string name;
		public readonly Bone parent;
		public readonly Matrix4 localRotationMatrix;
		public readonly Matrix4 localTranslationMatrix;
		public readonly Matrix4 localTransformationMatrix;
		public readonly Matrix4 globalTransformationMatrix;
		
		public readonly KeyFrame[] keyFrames;
		
		public Bone(string name, Bone parent, Matrix4 localRotationMatrix, Matrix4 localTranslationMatrix, KeyFrame[] keyFrames)
		{
			this.name = name;
			this.parent = parent;
			
			this.localRotationMatrix = localRotationMatrix;
			this.localTranslationMatrix = localTranslationMatrix;
			this.localTransformationMatrix = localRotationMatrix * localTranslationMatrix;

			this.globalTransformationMatrix = this.GetGlobalTransformationMatrix();
			
			this.keyFrames = keyFrames;			
		}
		
		public Matrix4 GetAnimationMatrix(float time)
		{
			Matrix4 matrix = this.localTransformationMatrix;
			for (int i = 1; i < keyFrames.Length; i++)
			{
				if (keyFrames[i - 1].time < time && keyFrames[i].time >= time)
				{
					matrix = KeyFrame.Interpolate(this, ref keyFrames[i - 1], ref keyFrames[i], time);
					break;
				}
			}
			
			if (parent == null)
			{
				return matrix;
			}
			else
			{
				return matrix * parent.GetAnimationMatrix(time);
			}
		}
		
		private Matrix4 GetGlobalTransformationMatrix()
		{
			if (parent == null)
			{
				return this.localTransformationMatrix;
			}
			else
			{
				return this.localTransformationMatrix * parent.GetGlobalTransformationMatrix();
			}
		}
	}
}
