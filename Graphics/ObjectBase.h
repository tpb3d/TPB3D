//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Base object class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../Types/Vector3.h"

class CMainFrame;

struct TextureUV
{
   float U;
   float V;
public:
   TextureUV() {};
   TextureUV( float u, float v ) { U = u; V = v; };
};


// Alocation is handled here at the base level dictated by derivation
// You must derive from this base as it is pure virtual, but ctor/dtor must be called.
class SerializerBase;

class ObjectBase
{
protected:
   Vector3f* mpPoints;
   short mPointCount;
   short mMaxPointCount;
   unsigned char mRGBA[4];
   int mID;
   bool mbHighlighted;

public:
	ObjectBase( int PointCount, int ID );
	virtual ~ObjectBase();

   // methods
   virtual void Draw() = 0; // base can't draw
   virtual void DrawSelectionTarget() = 0; // base can't draw
   virtual ObjectBase* Clone( ) = 0;
   virtual void Save(SerializerBase& ser) {};
   virtual void Load(SerializerBase& ser) {};

   int AddPoint( const Vector3f& point );
   void Resize( int width, int depth );

   // properties
   int  GetID() { return mID; };
   Vector3f* GetPoints() { return mpPoints; };
   void HighLight( bool bVal ) {mbHighlighted = bVal; };
};
