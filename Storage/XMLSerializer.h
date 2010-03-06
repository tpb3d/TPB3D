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
// Tick Tock!

#pragma once
#ifndef _XMLSERIALIZER_H
#define _XMLSERIALIZER_H

#include "SerializerBase.h"

class TiXmlElement;
// NO CPP

class XMLSerializer : public SerializerBase
{
protected:
   TiXmlElement* mpnParent;
public:
   XMLSerializer (TiXmlElement* pnParent);
   XMLSerializer( const char* tag );
   virtual ~XMLSerializer ();
   virtual void AddChild( const char*pName );
   TiXmlElement* AddTiXMLChild( const char*pName );
   void Add( const char* tag, int val );
   void Add( const char* tag, float val );
   void Add( const char* tag, double val );
   void Add( const char* tag, const char* str );
   const char* GetString( const char* tag );
   double GetDouble( const char* tag );
   float GetFloat( const char* tag );
   int   GetInt( const char* tag );
   SerializerBase* Spawn(const char* pName);
   SerializerBase* GetFirstChild (const char* pName);
   SerializerBase* GetNextSibling (const char* pName);
};

#endif // _XMLSERIALIZER_H
