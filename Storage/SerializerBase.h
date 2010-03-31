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
// Tick Tock!

#pragma once
#ifndef _SERIALIZERBASE_H
#define _SERIALIZERBASE_H

// NO CPP

class SerializerBase // abstract
{
public:
   SerializerBase () {};
   virtual ~SerializerBase () {};
   virtual void AddChild( const char*pName ) = 0;
   virtual void Add( const char* tag, int val ) = 0;
   virtual void Add( const char* tag, float val ) = 0;
   virtual void Add( const char* tag, double val ) = 0;
   virtual void Add( const char* tag, const char* tr ) = 0;
   virtual float GetFloat( const char* tag ) = 0;
   virtual double GetDouble( const char* tag ) = 0;
   virtual int GetInt( const char* tag ) = 0;
   virtual const char* GetString( const char* tag ) = 0;
   virtual SerializerBase* Spawn(const char* pName) = 0;
   virtual SerializerBase* GetFirstChild (const char* pName) = 0;
   virtual SerializerBase* GetNextSibling (const char* pName) = 0;
};

#endif // _SERIALIZERBASE_H
