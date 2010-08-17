/*   This file is part of Theme Park Builder 3D The Game.
 *
 *   Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

#include "Texture.h"
#include "Image.h"

using namespace Gfx;

namespace Gfx {
   Gfx::ImageManager * ImageManager::mInstance = NULL;

   ImageManager::ImageManager ()
   :   mpath_prefix ("data/")
   {
   }

   ImageManager *
   ImageManager::GetInstance ()
   {
      if (mInstance == NULL)
      {
         mInstance = new ImageManager ();
      }
      return mInstance;
   }

   void
   ImageManager::set_path (const std::string & prefix)
   {
      mpath_prefix = prefix;
   }

   Texture*
   ImageManager::GetTexture (const std::string & name, int channels, bool bInvert) // we have to tell it how many channels until we change the loader
   {
      if (mImages[name] == NULL)
      {
         Texture* pTexture = new Texture (name);
         std::cout << "Loading file " << mpath_prefix + name << std::endl;
         pTexture->Load (mpath_prefix + name);
         mImages[name] = pTexture;
         return pTexture;
      }
//      std::cout << "Using preloaded file " << name << std::endl;
      return mImages[name];
   }
}
