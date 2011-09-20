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

namespace Ms3dLoader
{
    //
    // flags
    //
    //#define SELECTED        1
    //#define HIDDEN          2
    //#define SELECTED2       4
    //#define DIRTY           8

    [Flags]
    public enum Flags : byte
    {
        selected = 1,
        hidden = 2,
        selected2 = 4,
        dirty = 8
    }
}
