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
using System.Collections.Generic;

using OpenTK.Graphics;

using TextureLoaders;

namespace OOGL.Textures
{
	public class TextureManager
	{		
		private readonly Dictionary<string,Texture> textures = new Dictionary<string,Texture>();
	
		public TextureManager()
		{
		}
		
		private static TextureManager instance;
		public static TextureManager Instance
		{
			get
			{
				if(instance==null)
				{
					instance = new TextureManager();
				}
				return instance;
			}
		}
		
		public Texture Find(string file, TextureMagFilter magFilter, TextureMinFilter minFilter, TextureWrapMode wrapModeS, TextureWrapMode wrapModeT)
		{
			try
			{
				string key = string.Format("{0}:{1}:{2}:{3}:{4}", file, magFilter, minFilter, wrapModeS, wrapModeT);
			
				Texture texture;
				if(textures.TryGetValue(key, out texture))return texture;

				TextureLoaderParameters.MagnificationFilter = magFilter;
				TextureLoaderParameters.MinificationFilter = minFilter;
				TextureLoaderParameters.WrapModeS = wrapModeS;
				TextureLoaderParameters.WrapModeT = wrapModeT;
				
				uint handle;
				TextureTarget dimension;
				ImageDDS.LoadFromDisk(file, out handle, out dimension);
				
				texture = new Texture(handle);
				
				textures[key]=texture;
				
				return texture;
			}
			catch
			{
				Console.WriteLine(string.Format("TextureManager: Failed to load texture {0}", file));
				return new Texture(0); // TODO remove
			}
		}
	}
}
