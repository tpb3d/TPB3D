#pragma once
//  Wood coaster support trestle and bracing
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  TrackSection class
//
//  Generated track sections specified by a pattern and parameters
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"
#include "../Types/Vector3.h"

struct Guide;
class MeshNode;

class WoodTrestle : public ObjectNode
{
   int   mPartsCount;
   int   mMaxParts;
   long  mWoodColor;
   long  mFootintColor;
   long  mHandrailColor;
   Gfx::Texture* mpTexture;
//   ObjectBase** mpBaseParts; // temp hardcode
public:
   static const char* codes;
   enum TrestleFormat
   {
      TF_Standard,
      TF_Pyramid,
      TF_PyramidZ, // Z braced with adjacent pyramid, generator responsible for alignment
      TF_Catherdral, // Straigh butressed side supports.
      TF_HybridSteel // Galvanized steel structure
   };
// Persisted
protected:
   TrestleFormat mFormat;
   Vector3f mLocation;
   float mfHeight;
   float mfWidth;
   float mfBentAngle;   // this is the cross board that supports the track

public:
   WoodTrestle (Gfx::Texture* pTex, Vector3f& loc);
   ~WoodTrestle(void);
   void Clear();
   void Create(int Count);
   void SetupGuide(Guide& guide);
   void Preset( TrestleFormat format, float mfYAngle, float mfHeight, float mfWidth, float mfBentAngle);
   void AddSection( ObjectBase* pGLBase );
   void Draw();
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);

   void Render (Vector3f& HRLeft, Vector3f& HRRight);
   void WoodPost(float x, float y, float z, float w, float h, float angle);
   void WoodBeam(float x, float y, float z, float w, float l, float d, float angle);
   void WoodBrace(float x, float y, float z, float w, float l, float d, float h, float angle);
   void WoodBracePost(float x, float y, float z, float w, float l, float d, float angle);
   void WoodBent(float x, float y, float z, float w, float l, float d, float angle, float tilt);
   void ConcreteFooting (float x, float y, float z, float width, float depth);
   void WondHandrails (Vector3f& HRLeftA, Vector3f& HRRightA, Vector3f& HRLeftB, Vector3f& HRRightB);
};

