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
    //    float           position[3];                        // local position
    //} ms3d_keyframe_pos_t;
    public struct KeyFramePosition
    {
        public readonly float time;
        public readonly Vector3 position;

        public KeyFramePosition(BinaryReader r)
        {
            time = r.ReadSingle();
            position = new Vector3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle());
        }

        public override string ToString()
        {
            return string.Format("KeyFramePosition(time={0},position={1}", time, position);
        }
    }
}
