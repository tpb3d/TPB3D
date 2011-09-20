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
	/// Keyframe is used in skeletal animation
	/// <remarks>Thread safety - This struct is thread safe when treated as readonly</remarks>
	/// </summary>
	public struct KeyFrame : IComparable<KeyFrame>
	{
		public readonly float time;
		public readonly Quaternion rotation;
		public readonly Vector3 translation;
		
		public KeyFrame(float time, Quaternion rotation, Vector3 translation)
		{
			this.time = time;
			this.rotation = rotation;
			this.translation = translation;
		}
		
		public int CompareTo(KeyFrame other)
		{
			return time.CompareTo(other.time);
		}
		
		public static Matrix4 Interpolate(Bone bone, ref KeyFrame first, ref KeyFrame second, float time)
		{
			Matrix4 rotationMatrix;
			Matrix4 translationMatrix;
			
			if (time <= first.time)
			{
				if (first.rotation.Xyz.Length == 0) 
				{
					rotationMatrix = Matrix4.Identity;
				}
				else
				{
					rotationMatrix = Matrix4.Rotate(first.rotation);
				}
				
				translationMatrix = Matrix4.CreateTranslation(first.translation);
			}
			else if (time >= second.time)
			{
				if (second.rotation.Xyz.Length == 0) 
				{
					rotationMatrix = Matrix4.Identity;
				}
				else
				{
					rotationMatrix = Matrix4.Rotate(second.rotation);
				}
				translationMatrix = Matrix4.CreateTranslation(second.translation);
				// TODO delete 
				// translationMatrix = Matrix4.Translation(second.translation);
			}
			else
			{
				float blend = (time - first.time) / (second.time - first.time);
				Quaternion q = Quaternion.Slerp(first.rotation, second.rotation, blend);
				
				if (q.Xyz.Length == 0)
				{
					rotationMatrix = Matrix4.Identity;
				}
				else
				{
					rotationMatrix = Matrix4.Rotate(q);
				}
				translationMatrix = Matrix4.CreateTranslation(Vector3.Lerp(first.translation, second.translation, blend));
				// TODO delete
				//translationMatrix = Matrix4.Translation(Vector3.Lerp(first.translation, second.translation, blend));
			}
			
			return rotationMatrix * bone.localRotationMatrix * translationMatrix * bone.localTranslationMatrix;
		}
	}
}
