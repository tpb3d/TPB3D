#pragma once
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"
#include "../Types/Vector3.h"

struct Guide;

class ParabolicCorkSupport :
   public ObjectNode
{
protected:
   long  mFootingColor;
   long  mStructureColor;

public:
   enum CorkSupportFormat
   {
      CSF_Standard,
      CSF_Modified      // More advanced trussing
   };
protected:   // Persisted
   CorkSupportFormat mFormat;
   Vector3f mLocation;
   Gfx::Texture* mpTexture;
   float mfHeight;
   float mfWidth;
   float mfYAngle;   // Angle looking at the ground

public:
   ParabolicCorkSupport(Gfx::Texture* pTex, Vector3f& loc);
   ~ParabolicCorkSupport(void);

   void Clear();
   void Create(int Count);
   void SetupGuide(Guide& guide);
   void Preset( CorkSupportFormat format, float mfYAngle, float mfHeight, float mfWidth);
   void AddSection( ObjectBase* pGLBase );
   void Draw();
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);

   void Render (Vector3f& RollCenter, float HighPoint); // HighPoint is 1 foot about the track spine at the apex.
};
