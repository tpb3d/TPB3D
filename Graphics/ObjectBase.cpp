// GLBase.cpp: implementation of the GLBase class.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ObjectBase.h"

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// Alocation is handled here at the base level dictated by derivation
// You must derive from this base as it is pure virtual.
 
ObjectBase::ObjectBase( int count, int id )
:  mID( id )
,  mMaxPointCount( count )
,  mpPoints( 0 )
,  mPointCount( 0 )
{
   mbHighlighted = false;
   try
   {
      if( count > 0 )
         mpPoints = new sf::Vector3f[mMaxPointCount];
   }
   catch( ... )
   {
      mpPoints = 0;
      mPointCount = 0;
      mMaxPointCount = 0;
   }
}

ObjectBase::~ObjectBase()
{
   try
   {
      if( mpPoints )
         delete [] mpPoints;
   }
   catch( ... )
   {
      throw( "Failed to delete a Points Array","GLBase" ); // CGLException
   }
}

int ObjectBase::AddPoint( sf::Vector3f& point )
{
   if( mPointCount >= mMaxPointCount )
      return -1;
	mpPoints[mPointCount] = point;
   int ret = mPointCount;
   ++mPointCount;
   return ret;
}

void ObjectBase::Resize( int width, int depth )
{
   try
   {
      delete [] mpPoints;
      mPointCount = 0;
      mMaxPointCount = width*depth;
      if( mMaxPointCount > 0 )
         mpPoints = new sf::Vector3f[mMaxPointCount];
   }
   catch( ... )
   {
      mpPoints = 0;
      mPointCount = 0;
      mMaxPointCount = 0;
   }
}