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
//

using System;
using System.IO;

namespace OOGL
{
	public static class ResourceLocator
	{
		private static string rootPath;
		
		public static string RootPath
		{
			get
			{
				return rootPath;
			}
			set
			{
				rootPath = value;
			}
		}
	
		public static string GetFullPath(string resourcePath)
		{
			return rootPath + resourcePath;
		}
		
		public static string GetFullPathRelative(string knownFilePath, string fileName)
		{
			if (fileName.StartsWith(@"./")) fileName = fileName.Substring(2);
			if (fileName.StartsWith(@".\")) fileName = fileName.Substring(2);
			
			return Path.GetDirectoryName(knownFilePath) + Path.DirectorySeparatorChar + fileName;			
		}
	}
}
