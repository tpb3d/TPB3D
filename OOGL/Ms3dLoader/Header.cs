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
    // First comes the header (sizeof(ms3d_header_t) == 14)
    //
    //typedef struct
    //{
    //    char    id[10];                                     // always "MS3D000000"
    //    int     version;                                    // 4
    //} ms3d_header_t;
    public struct Header
    {
        public readonly string id;
        public readonly int version;

        public Header(BinaryReader r)
        {
            id = ASCIIEncoding.ASCII.GetString(r.ReadBytes(10));
            version = r.ReadInt32();
        }

        public override string ToString()
        {
            return string.Format("Header id={0},version={1}", id, version);
        }
    }
}
