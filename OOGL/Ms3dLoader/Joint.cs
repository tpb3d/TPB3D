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
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

using OpenTK;

namespace Ms3dLoader
{
    //
    // Then come nNumJoints joints (the size of joints are dynamic, because each joint has a differnt count of keys
    //
    //typedef struct
    //{
    //    byte            flags;                              // SELECTED | DIRTY
    //    char            name[32];                           //
    //    char            parentName[32];                     //
    //    float           rotation[3];                        // local reference matrix
    //    float           position[3];

    //    word            numKeyFramesRot;                    //
    //    word            numKeyFramesTrans;                  //

    //    ms3d_keyframe_rot_t keyFramesRot[numKeyFramesRot];      // local animation matrices
    //    ms3d_keyframe_pos_t keyFramesTrans[numKeyFramesTrans];  // local animation matrices
    //} ms3d_joint_t;
    public struct Joint
    {
        public readonly Flags flags;
        public readonly string name;
        public readonly string parentName;
        public readonly Vector3 rotation;
        public readonly Vector3 position;

        public readonly KeyFrameRotation[] keyFrameRotations;
        public readonly KeyFramePosition[] keyFramePositions;

        public Joint(BinaryReader r)
        {
            flags = (Flags)r.ReadByte();
            name = ASCIIEncoding.ASCII.GetString(r.ReadBytes(32)).Split((char)0)[0];
            parentName = ASCIIEncoding.ASCII.GetString(r.ReadBytes(32)).Split((char)0)[0];
            rotation = new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle());
            position = new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle());

            ushort numKeyFrameRotations = r.ReadUInt16();
            ushort numKeyFramePositions = r.ReadUInt16();

            keyFrameRotations = new KeyFrameRotation[numKeyFrameRotations];
            for (int i = 0; i < numKeyFrameRotations; i++)
            {
                keyFrameRotations[i] = new KeyFrameRotation(r);
            }

            keyFramePositions = new KeyFramePosition[numKeyFramePositions];
            for (int i = 0; i < numKeyFramePositions; i++)
            {
                keyFramePositions[i] = new KeyFramePosition(r);
            }
        }

        public override string ToString()
        {
            StringBuilder text = new StringBuilder();

            text.AppendLine(string.Format("Joint flags={0},name={1},parentName={2},rotation={3},position={4},numKeyFrameRotations={5},numKeyFramePositions={6}", flags, name, parentName, rotation, position, keyFrameRotations.Length, keyFramePositions.Length));
            for (int i = 0; i < keyFrameRotations.Length; i++)
            {
                text.AppendLine(keyFrameRotations[i].ToString());
            }

            for (int i = 0; i < keyFramePositions.Length; i++)
            {
                text.AppendLine(keyFramePositions[i].ToString());
            }

            return text.ToString();
        }
    }
}
