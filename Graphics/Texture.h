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

#pragma once
#ifndef _TEXTURE_H
#define _TEXTURE_H

// Is there a way to avoid this include?
#include <cstring>
#include "SFML/Graphics.hpp"


using namespace std;

namespace Gfx
{
   class ImageManager;

   class Texture : public sf::Image
   {
      friend class ImageManager;

      std::string mName;
      //unsigned int mID;
      unsigned int mChannels;

   protected:
      // CTOR
      Texture (const string& psName);
      ~Texture () {};

   public:
      // properties
      //unsigned int GetID() { return mID; }
      inline bool SupportsAlpha() { return mChannels==4; }

      // methods
      bool Load (const string& psName);
   };
}

#endif //_TEXTURE_H
