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
using System.Text;
using System.IO;

using OpenTK;

namespace Ms3dLoader
{
    //
    // Then come nNumTriangles times ms3d_triangle_t structs (sizeof(ms3d_triangle_t) == 70)
    //
    //typedef struct
    //{
    //    word    flags;                                      // SELECTED | SELECTED2 | HIDDEN
    //    word    vertexIndices[3];                           //
    //    float   vertexNormals[3][3];                        //
    //    float   s[3];                                       //
    //    float   t[3];                                       //
    //    byte    smoothingGroup;                             // 1 - 32
    //    byte    groupIndex;                                 //
    //} ms3d_triangle_t;
    public struct Triangle
    {
        public readonly Flags flags;
        public readonly ushort[] vertexIndices;
        public readonly Vector3[] normals;

        public readonly float[] s;
        public readonly float[] t;

        public readonly byte smoothingGroup;
        public readonly byte groupIndex;

        public Triangle(BinaryReader r)
        {
            flags = (Flags)r.ReadUInt16();
            vertexIndices = new ushort[] { r.ReadUInt16(), r.ReadUInt16(), r.ReadUInt16() };
            normals = new Vector3[]
				{
					new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle()),
					new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle()),
					new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle())
				};

            s = new float[] { r.ReadSingle(), r.ReadSingle(), r.ReadSingle() };
            t = new float[] { r.ReadSingle(), r.ReadSingle(), r.ReadSingle() };

            smoothingGroup = r.ReadByte();
            groupIndex = r.ReadByte();
        }

        public override string ToString()
        {
            return string.Format("Triangle flags={0},indices=({1},{2},{3}),normals=({4},{5},{6}),s=({7},{8},{9}),t=({10},{11},{12}),smoothingGroup={13},groupIndex={14}",
                flags, vertexIndices[0], vertexIndices[1], vertexIndices[2], normals[0], normals[1], normals[2], s[0], s[1], s[2], t[0], t[1], t[2], smoothingGroup, groupIndex);
        }
    }

}
