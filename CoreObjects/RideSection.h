//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideSection class
//
//  Generated Ride sections specified by a pattern and parameters
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"

// this is just the Ridesections not the supports, devices or station
// A secion represents an assembly which is made up of one or more detailed parts.

class ObjectBase;
struct Guide;

class RideSection : public ObjectNode
{
   int   mPartsCount;
   int   mMaxParts;
   ObjectBase** mpBaseParts; // temp hardcode
public:
   static const char* codes;
   enum SectionFormat
   {
      SF_Straight,
      SF_Pitched,
      SF_Curved,
      SF_Compound
   };
// Persisted
protected:
   SectionFormat mSectionFormat;
   float mfDegPitch;
   float mfDistance;
   float mfDegRotation;
   float mfRadius;
   float mfPitchRadius;
   float mfRoll;
   int mRepetitions;
   int mRepCount; // temporary value used by render system for interation
   //int TextureID; use model info
   int Debug;
   int gearID;
   float gearRatio;

public:
   RideSection(void);
   ~RideSection(void);

   void Clear();
   void Create(int Count);
   void SetupGuide(Guide& guide);
   void Preset( float fDefPitch, float fDistance, float fDegRotation, float fRadius, float fPitchRadius, float fRoll);
   void AddSection( ObjectBase* pGLBase );
   void Draw();
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
