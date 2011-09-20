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
    // Then come nNumGroupComments times group comments, which are dynamic, because the comment can be any length
    //
    //typedef struct
    //{
    //    int index;											// index of group, material or joint
    //    int commentLength;									// length of comment (terminating '\0' is not saved), "MC" has comment length of 2 (not 3)
    //    char comment[commentLength];						// comment
    //} ms3d_comment_t;
    public struct Comment
    {
        public readonly int index;
        public readonly string comment;

        public Comment(BinaryReader r)
        {
            index = r.ReadInt32();
            comment = ASCIIEncoding.ASCII.GetString(r.ReadBytes(r.ReadInt32()));
        }

        public override string ToString()
        {
            return string.Format("Comment index={0},comment={1}", index, comment);
        }
    }
}
