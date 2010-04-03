#pragma once

#include <cstring> // GCC needs this

#include "../Storage/SerializerBase.h"
#include "PartGuide.h"

const NodeType NodeTypeList[] =
{
   { PartGuide::RideNodePlatForm,  "Platform" },
   { PartGuide::RideNodeBase, "Base" },   //
   { PartGuide::RideNodeHub, "Hub" },
   { PartGuide::RideNodeStrut, "Strut" },
   { PartGuide::RideNodeArm, "Arm" },
   { PartGuide::RideNodeDeck, "Deck" },
   { PartGuide::RideNodeCar, "Car" },
   { PartGuide::RideNodeDisc, "Disc" }, 
   { PartGuide::RideNodeCarriage, "Carriage" },
   { PartGuide::RideNodeCableHinge, "CableHinge" },
   { PartGuide::RideNodeRotationHub, "RotationHub" },
   { PartGuide::RideNodeCrankHub, "CrankHub" },
   { PartGuide::RideNodeLiftArm, "LiftArm" },
   { PartGuide::RideNodeDud, "Dud" }
};

PartGuide::PartGuide ()
: trig(0.0f, 0.0f, 0.0f)   // vector angle
{
   Clear ();
}

void  PartGuide::Clear()
{
   nCount = 0;
   nSpeed = 0;
   fOffset = 0;
   fWidth = 1; // cube
   fHeight = 1;
   fLength = 1;
   fDrop = 0;
   fAngle = 0;
   iNextNode = 0;
}

void PartGuide::Load(SerializerBase& ser)
{
   ser.Add ("NodeType", NodeTypeList[mNodeType].pNodeName);
   ser.Add ("Count", nCount);
   ser.Add ("Speed", nSpeed);
   ser.Add ("Offset", fOffset);
   ser.Add ("Height", fHeight);
   ser.Add ("Width", fWidth);
   ser.Add ("Length", fLength);
   ser.Add ("Angle", fAngle);
   ser.Add ("Drop", fDrop);
}

PartGuide::TRideNodeType PartGuide::GetNodeType (const char* szNodeName)
{
   size_t iCount = sizeof(NodeTypeList)/sizeof(NodeType);
   for (size_t idx = 0; idx < iCount; ++idx)
   {
      if( strcmp(NodeTypeList[idx].pNodeName, szNodeName) == 0 )
      {
         return NodeTypeList[idx].nType;
      }
   }
   return RideNodeDud;
}
   
void PartGuide::Save(SerializerBase& ser)
{
   try
   {
      mNodeType = GetNodeType(ser.GetString ("NodeType"));   // what part to build
      short nCount = (short)ser.GetInt ("Count");
      short nSpeed = (short)ser.GetInt ("Speed");
      float fOffset = ser.GetFloat ("Offset");
      float fWidth = ser.GetFloat ("Width");
      float fHeight = ser.GetFloat ("Height");
      float fLength = ser.GetFloat ("Length");
      float fAngle = ser.GetFloat ("Angle");
      float fDrop = ser.GetFloat ("Drop"); // used for suspended items or offsets
   }
   catch (...)
   {
      // tell the user this line if borked
   }      
}
