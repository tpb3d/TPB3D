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
    // Then come nNumJoints joints (the size of joints are dynamic, because each joint has a differnt count of keys
    //
    //typedef struct // 16 bytes
    //{
    //    float           time;                               // time in seconds
    //    float           rotation[3];                        // x, y, z angles
    //} ms3d_keyframe_rot_t;
    public struct KeyFrameRotation
    {
        public readonly float time;
        public readonly Vector3 rotation;

        public KeyFrameRotation(BinaryReader r)
        {
            time = r.ReadSingle();
            rotation = new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle());
        }

        public override string ToString()
        {
            return string.Format("KeyFrameRotation(time={0},rotation={1}", time, rotation);
        }
    }
}
