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

namespace Ms3dLoader
{
    //
    // Then come nNumGroups times groups (the sizeof a group is dynamic, because of triangleIndices is numtriangles long)
    //
    //typedef struct
    //{
    //    byte            flags;                              // SELECTED | HIDDEN
    //    char            name[32];                           //
    //    word            numtriangles;                       //
    //    word            triangleIndices[numtriangles];      // the groups group the triangles
    //    char            materialIndex;                      // -1 = no material
    //} ms3d_group_t;
    public struct Group
    {
        public readonly Flags flags;
        public readonly string name;
        public readonly ushort numTriangles;
        public readonly ushort[] triangleIndices;
        public readonly sbyte materialIndex;

        public Group(BinaryReader r)
        {
            flags = (Flags)r.ReadByte();
            name = ASCIIEncoding.ASCII.GetString(r.ReadBytes(32)).Split((char)0)[0];
            numTriangles = r.ReadUInt16();

            triangleIndices = new ushort[numTriangles];
            for (int i = 0; i < numTriangles; i++)
            {
                triangleIndices[i] = r.ReadUInt16();
            }

            materialIndex = r.ReadSByte();
        }

        public override string ToString()
        {
            return string.Format("Group flags={0},name={1},numTriangles={2},materialIndex={3}", flags, name, numTriangles, materialIndex);
        }
    }
}
