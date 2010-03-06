#pragma once
#include "ObjectBase.h"
#include "ObjectNode.h"

// this is just the tracks not the supports, devices or station
class ObjectBase;
class CVPoint;
class CMainFrame;
struct CamPath;

class CTrack : public ObjectNode
{
   float m_dHeight; // = 5;
   int   m_PartsCount;
   ObjectBase* m_BaseParts[168]; // temp hardcode
//   CamPath* m_pPoints[168];


public:
   CTrack(void);
   ~CTrack(void);

   void AddSection( ObjectBase* pGLBase );
   void Draw();
//   CamPath** GetPath( ) { return m_pPoints; };
};
