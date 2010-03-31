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
#include <string>
#include "../xml/tinyxml/tinyxml.h"
#include "../Types/String.h"
#include "XMLSerializer.h"

using namespace std;

XMLSerializer::XMLSerializer (TiXmlElement* pnParent)
:   mpnParent (pnParent)
{
}

XMLSerializer::XMLSerializer( const char* tag )
{
   TiXmlElement* pnSpace = new TiXmlElement(tag);
   mpnParent->LinkEndChild(pnSpace);
}

XMLSerializer::~XMLSerializer ()
{
}

void XMLSerializer::Add( const char* tag, int val )
{
   TiXmlElement* pnElement = new TiXmlElement(tag);
   TiXmlText* pnVal = new TiXmlText(ToString(val).c_str());
   pnElement->LinkEndChild(pnVal);
   mpnParent->LinkEndChild(pnElement);
}

void XMLSerializer::Add( const char* tag, double val )
{
   TiXmlElement* pnElement = new TiXmlElement(tag);
   TiXmlText* pnVal = new TiXmlText(ToString(val).c_str());
   pnElement->LinkEndChild(pnVal);
   mpnParent->LinkEndChild(pnElement);
}

void XMLSerializer::Add( const char* tag, float val )
{
   TiXmlElement* pnElement = new TiXmlElement(tag);
   TiXmlText* pnVal = new TiXmlText(ToString(val).c_str());
   pnElement->LinkEndChild(pnVal);
   mpnParent->LinkEndChild(pnElement);
}

void XMLSerializer::Add( const char* tag, const char* str )
{
   TiXmlElement* pnElement = new TiXmlElement(tag);
   TiXmlText* pnText = new TiXmlText(str);
   pnElement->LinkEndChild(pnText);
   mpnParent->LinkEndChild(pnElement);
}

void XMLSerializer::AddChild( const char* tag )
{
   TiXmlElement* pnSpace = new TiXmlElement(tag);
   mpnParent->LinkEndChild(pnSpace);
}

TiXmlElement* XMLSerializer::AddTiXMLChild( const char* tag )
{
   TiXmlElement* pnSpace = new TiXmlElement(tag);
   mpnParent->LinkEndChild(pnSpace);
   return pnSpace;
}

SerializerBase* XMLSerializer::Spawn(const char* pName)
{
   TiXmlElement* pnSpace = AddTiXMLChild(pName);
   XMLSerializer* pSer = new XMLSerializer(pnSpace);
   return pSer;
}

SerializerBase* XMLSerializer::GetFirstChild(const char* pName)
{
   XMLSerializer* pNewSer = NULL;
   TiXmlElement* pnSib = mpnParent->FirstChildElement(pName);
   if (pnSib != NULL)
   {
      pNewSer = new XMLSerializer(pnSib);
   }
   return pNewSer;
}

SerializerBase* XMLSerializer::GetNextSibling(const char* pName)
{
   XMLSerializer* pNewSer = NULL;
   TiXmlElement* pnSib = mpnParent->NextSiblingElement(pName);
   if (pnSib != NULL)
   {
      pNewSer = new XMLSerializer(pnSib);
   }
   return pNewSer;
}

const char* XMLSerializer::GetString( const char* tag )
{
   TiXmlNode* pnName = mpnParent->FirstChild(tag);
   const char* psz = "";
   TiXmlNode* pnStr = pnName->FirstChild();
   if( pnStr )
   {
      psz = pnStr->Value();
   }
   return psz;
}

double XMLSerializer::GetDouble( const char* tag )
{
   TiXmlNode* pnName = mpnParent->FirstChild(tag);
   return FromString<double>(pnName->FirstChild()->Value());
}

float XMLSerializer::GetFloat( const char* tag )
{
   TiXmlNode* pnName = mpnParent->FirstChild(tag);
   return FromString<float>(pnName->FirstChild()->Value());
}

int XMLSerializer::GetInt( const char* tag )
{
   TiXmlNode* pnName = mpnParent->FirstChild(tag);
   return FromString<int>(pnName->FirstChild()->Value());
}

