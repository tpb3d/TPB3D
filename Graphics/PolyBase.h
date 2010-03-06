//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  PolygonBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Extreme Park Developer.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#pragma once
//#include <GL/gl.h>
// BaseClass of all the polygons

class CPolyBase
{
   int            m_Index;
   unsigned char  m_RGBA[4];
   GLfloat        m_RootPoint[4];
public:
   CPolyBase( int Index );
   ~CPolyBase(void);

public:
   virtual void Render() = 0; // base can't draw

   int AddVertex( GLfloat* f3 );
};
