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
    // Then come nNumVertices times ms3d_vertex_t structs (sizeof(ms3d_vertex_t) == 15)
    //
    //typedef struct
    //{
    //    byte    flags;                                      // SELECTED | SELECTED2 | HIDDEN
    //    float   vertex[3];                                  //
    //    char    boneId;                                     // -1 = no bone
    //    byte    referenceCount;
    //} ms3d_vertex_t;
    //
    // ms3d_vertex_ex_t for subVersion == 1
    //typedef struct
    //{
    //    char boneIds[3];									// index of joint or -1, if -1, then that weight is ignored, since subVersion 1
    //    byte weights[3];									// vertex weight ranging from 0 - 255, last weight is computed by 1.0 - sum(all weights), since subVersion 1
    //    // weight[0] is the weight for boneId in ms3d_vertex_t
    //    // weight[1] is the weight for boneIds[0]
    //    // weight[2] is the weight for boneIds[1]
    //    // 1.0f - weight[0] - weight[1] - weight[2] is the weight for boneIds[2]
    //} ms3d_vertex_ex_t;
    ///
    // ms3d_vertex_ex_t for subVersion == 2
    //typedef struct
    //{
    //    char boneIds[3];									// index of joint or -1, if -1, then that weight is ignored, since subVersion 1
    //    byte weights[3];									// vertex weight ranging from 0 - 100, last weight is computed by 1.0 - sum(all weights), since subVersion 1
    //    // weight[0] is the weight for boneId in ms3d_vertex_t
    //    // weight[1] is the weight for boneIds[0]
    //    // weight[2] is the weight for boneIds[1]
    //    // 1.0f - weight[0] - weight[1] - weight[2] is the weight for boneIds[2]
    //    unsigned int extra;									// vertex extra, which can be used as color or anything else, since subVersion 2
    //} ms3d_vertex_ex_t;
    public struct Vertex
    {
        public readonly Flags flags;
        public readonly Vector3 vertex;
        public readonly sbyte boneId0;
        public readonly byte referenceCount;

        // Extended Data			
        public readonly sbyte boneId1;
        public readonly sbyte boneId2;
        public readonly sbyte boneId3;

        public readonly float weight0;
        public readonly float weight1;
        public readonly float weight2;

        public Vertex(BinaryReader r)
        {
            flags = (Flags)r.ReadByte();
            vertex = new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle());
            boneId0 = r.ReadSByte();
            referenceCount = r.ReadByte();

            boneId1 = -1;
            boneId2 = -1;
            boneId3 = -1;

            weight0 = 1.0f;
            weight1 = 0.0f;
            weight2 = 0.0f;
        }

        public Vertex(BinaryReader r, Vertex v, int subVersion)
        {
            flags = v.flags;
            vertex = v.vertex;
            boneId0 = v.boneId0;
            referenceCount = v.referenceCount;

            boneId1 = r.ReadSByte();
            boneId2 = r.ReadSByte();
            boneId3 = r.ReadSByte();

            weight0 = r.ReadByte() / 255.0f;
            weight1 = r.ReadByte() / 255.0f;
            weight2 = r.ReadByte() / 255.0f;

            if (subVersion == 1) return;

            r.ReadUInt32(); // extra data subversion 2+
        }

        public float Weight3
        {
            get
            {
                return 1.0f - (weight0 + weight1 + weight2);
            }
        }

        public override string ToString()
        {
            return string.Format("Vertex flags={0},vertex={1},referenceCount={2},boneIds=({3},{4},{5},{6}),weights=({7},{8},{9},{10})",
                flags, vertex, referenceCount, boneId0, boneId1, boneId2, boneId3, weight0, weight1, weight2, Weight3);
        }
    }
}
