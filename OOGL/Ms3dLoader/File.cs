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
using System.Text;
using System.Collections.Generic;
using System.Diagnostics;

using OpenTK;
using OpenTK.Graphics;

using OOGL.Shaders;

// This class is derived from MilkShape 3D 1.8.2 File Format Specification
namespace Ms3dLoader
{	
	public class File
	{
        //
        // max values
        //
        public const int maxVertices = 65534;
		public const int maxTriangles = 65534;
		public const int maxGroups = 255;
		public const int maxMaterials = 128;
		public const int maxJoints = 128;
															
		public readonly Header header;
		public readonly Vertex[] vertices;
		public readonly Triangle[] triangles; 
		public readonly Group[] groups;
		public readonly Material[] materials;	
		public readonly float animationFPS;
		public readonly float currentTime;
		public readonly int totalFrames;
		public readonly Joint[] joints;
		public readonly Comment[] groupComments;
		public readonly Comment[] materialComments;
		public readonly Comment[] jointComments;
		public readonly Comment[] modelComments;
		public readonly string fileName;
				
		public File(string fileName)
		{
			this.fileName = fileName;
		
			using(FileStream file = System.IO.File.OpenRead(fileName))
			{
				using(BinaryReader r = new BinaryReader(file))
				{
						this.header = new Header(r);
			
						ushort numVertices = r.ReadUInt16();
						this.vertices = new Vertex[numVertices];
						
						for(int i = 0; i < numVertices; i++)
						{
							vertices[i] = new Vertex(r);
						}
						
						ushort numTriangles = r.ReadUInt16();
						this.triangles = new Triangle[numTriangles];
						for (int i = 0; i < numTriangles; i++) 
						{
							triangles[i] = new Triangle(r);
						}
					
						ushort numGroups = r.ReadUInt16();
						this.groups = new Group[numGroups];
						for (int i = 0; i < numGroups; i++) 
						{
							groups[i] = new Group(r);
						}
						
						ushort numMaterials = r.ReadUInt16();
						this.materials = new Material[numMaterials];
						for (int i = 0; i < numMaterials; i++)
						{
							materials[i] = new Material(r);
						}
						
						this.animationFPS = r.ReadSingle();
						this.currentTime = r.ReadSingle();
						this.totalFrames = r.ReadInt32();
						
						ushort numJoints = r.ReadUInt16();
						this.joints = new Joint[numJoints];
						for (int i = 0; i < numJoints; i++)
						{
							joints[i] = new Joint(r);
						}	

						try
						{
							int commentSubversion = r.ReadInt32();
							if(commentSubversion != 1) throw new Exception("Unsupported comments sub version");
						}
						catch (EndOfStreamException ex)
						{
							ex.ToString();
							return;
						}
						
						uint numGroupComments = r.ReadUInt32();				
						this.groupComments = ReadComments(r, (int)numGroupComments);

						int numMaterialComments = r.ReadInt32();
						this.materialComments = ReadComments(r, numMaterialComments);

						int numJointComments = r.ReadInt32();
						this.jointComments = ReadComments(r, numJointComments);
						
						int numModelComments = r.ReadInt32();
						this.modelComments = ReadComments(r, numModelComments);

						int vertexSubVersion = r.ReadInt32();
						if (vertexSubVersion > 2) throw new Exception(string.Format("Unsupported extended vertex sub version. Found {0}. Expected 1 or 2", vertexSubVersion));
						
						for(int i = 0; i < numVertices; i++)
						{
							vertices[i] = new Vertex(r, vertices[i], vertexSubVersion);
						}

						// int jointSubVersion = r.ReadInt32();
						// if (jointSubVersion != 1) throw new Exception(string.Format("Unsupported extended joint sub version. Found {0}. Expected 1", jointSubVersion));

						// I stopped parsing early because I don't think I need the rest of the data.			
				}
			}		
		}
		
		private static Comment[] ReadComments(BinaryReader r, int count)
		{
			Comment[] comments = new Comment[count];
			for (int i = 0; i < count; i++)
			{
				comments[i] = new Comment(r);
			}	
			return comments;
		}
		
		public OOGL.Animation.Model ToModel(ShaderProgram shader, OOGL.Animation.Sample[] tracks)
		{
			OOGL.Animation.Group[] groups = new OOGL.Animation.Group[this.groups.Length];
			for(int i = 0; i < this.groups.Length; i++)
			{
				ushort[] indices;
				OOGL.Animation.VertexStruct[] vertices = GetVertices(i, out indices);
			
				groups[i] = new OOGL.Animation.Group
				(
					this.groups[i].name,
					this.materials[this.groups[i].materialIndex].GetOOGLMaterial(this.fileName),
					vertices,
					indices
				);
			}

			OOGL.Animation.Bone[] bones = new OOGL.Animation.Bone[this.joints.Length];
			AddChildBones("", null, bones);

            OOGL.Animation.Model model = new OOGL.Animation.Model(shader, groups, bones, tracks);
			
			return model;
		}
		
		public OOGL.Animation.VertexStruct[] GetVertices(int groupIndex, out ushort[] indices)
		{
			List<OOGL.Animation.VertexStruct> vertices = new List<OOGL.Animation.VertexStruct>();
		
			int numIndices = 0;
			for (int t = 0; t < this.triangles.Length; t++)
			{
				if (this.triangles[t].groupIndex == groupIndex)
				{
					for (int v = 0; v < 3; v++)
					{
						OOGL.Animation.VertexStruct vertexStruct = ToVertexStruct(t, v);						
						int index = vertices.BinarySearch(vertexStruct);
						if(index < 0) vertices.Insert(~index, vertexStruct);
					}
					numIndices += 3;
				}
			}
			
			int i = 0;
			indices = new ushort[numIndices];
			for (int t = 0; t < this.triangles.Length; t++)
			{
				if (this.triangles[t].groupIndex == groupIndex)
				{
					for (int v = 0; v < 3; v++)
					{
						indices[i] = (ushort)vertices.BinarySearch(ToVertexStruct(t, v));
						i++;
					}
				}
			}
			
			return vertices.ToArray();		
		}
		
		private OOGL.Animation.VertexStruct ToVertexStruct(int triangleIndex, int cornerIndex)
		{
			return new OOGL.Animation.VertexStruct
			(
				this.vertices[this.triangles[triangleIndex].vertexIndices[cornerIndex]].vertex,
				this.triangles[triangleIndex].normals[cornerIndex],
				this.triangles[triangleIndex].s[cornerIndex],
				1 - this.triangles[triangleIndex].t[cornerIndex],
				this.vertices[this.triangles[triangleIndex].vertexIndices[cornerIndex]].boneId0
			);
		}

		private void AddChildBones(string parentName, OOGL.Animation.Bone parentBone, OOGL.Animation.Bone[] bones)
		{
			for(int j = 0; j < this.joints.Length; j++)
			{
				if(this.joints[j].parentName == parentName)
				{						
					Matrix4 localRotationMatrix
						= Matrix4.RotateX(this.joints[j].rotation.X)
						* Matrix4.RotateY(this.joints[j].rotation.Y)
						* Matrix4.RotateZ(this.joints[j].rotation.Z);
																														
					Matrix4 localTranslationMatrix = Matrix4.CreateTranslation(this.joints[j].position);
					// TODO delete
					//Matrix4 localTranslationMatrix = Matrix4.Translation(this.joints[j].position);
					
					Dictionary<float,OOGL.Animation.KeyFrame> keyFrameDict =new Dictionary<float,OOGL.Animation.KeyFrame>();
					
					for(int r = 0; r < this.joints[j].keyFrameRotations.Length; r++)
					{
						float time = this.joints[j].keyFrameRotations[r].time;
						Vector3 rotVec = this.joints[j].keyFrameRotations[r].rotation;
									
						Quaternion rotation
							= Quaternion.FromAxisAngle(Vector3.UnitZ, rotVec.Z)
							* Quaternion.FromAxisAngle(Vector3.UnitY, rotVec.Y)
							* Quaternion.FromAxisAngle(Vector3.UnitX, rotVec.X);
																		
						keyFrameDict[time] = new OOGL.Animation.KeyFrame(time, rotation, Vector3.Zero);
					}
					
					for(int t = 0; t < this.joints[j].keyFramePositions.Length; t++)
					{	
						float time = this.joints[j].keyFramePositions[t].time;
						Vector3 translation	= this.joints[j].keyFramePositions[t].position;
						
						if(keyFrameDict.ContainsKey(time))
						{							
							keyFrameDict[time] = new OOGL.Animation.KeyFrame(time, keyFrameDict[time].rotation, translation);
						}
						else
						{
							keyFrameDict[time] = new OOGL.Animation.KeyFrame(time, Quaternion.Identity, translation);
						}						
					}
						
					List<OOGL.Animation.KeyFrame> keyFrames = new List<OOGL.Animation.KeyFrame>(keyFrameDict.Values);
					keyFrames.Sort();
					
					bones[j] = new OOGL.Animation.Bone(this.joints[j].name, parentBone, localRotationMatrix, localTranslationMatrix , keyFrames.ToArray());
					
					AddChildBones(bones[j].name, bones[j], bones);					
				}
			}
		}
	}
}
