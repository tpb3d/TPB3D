/*   This file is part of Theme Park Developer 3D The Game.
 *
 *   Theme Park Developer 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Developer 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _IMAGEMANAGER_H
#define _IMAGEMANAGER_H

#include <map>
#include <string>

#ifndef PI
#define PI 3.141579
#endif

namespace Gfx
{
   class Texture;

   class ImageManager
   {
   private:
      std::string mpath_prefix;
      //std::map<std::string, sf::Image *> mimages;
      std::map<std::string, Texture*> mImages;
      static ImageManager * mInstance;
      ImageManager ();

   public:
      static ImageManager * GetInstance ();
      static ImageManager* i() { return GetInstance(); };
//      sf::Image * GetImg (const std::string & name);
      Texture* GetTexture( const std::string& name, int channels);
//      int preload_image (const std::string& name);
      void set_path (const std::string & prefix);
   };
//   sf::Image* GetImage(const std::string& Key);
}
#endif // _IMAGEMANAGER_H
