#pragma once
#include "../Graphics/VPoint.h"
#include "../Types/Vector3.h"

// forward decls
class Park;
class Ride;
class RideNode;
class ObjectBase;

struct PartGuide
{
   enum TFlatRideNodeType
   {
      RideNodePlatForm,   // The Base that sits on the ground or
      RideNodeBase,    // Deck or Central base as in a carousel
      RideNodeHub,
      RideNodeStrut,
      RideNodeArm,
      RideNodeDeck,
      RideNodeCar,
      RideNodeDisc,        // spinner - no power
      RideNodeCarriage,    // rolling or orbiting -  no power
      RideNodeCableHinge,  // swinging - no power
      RideNodeRotationHub, // rotates - powered
      RideNodeLiftArm,     // lifiting hinge - powered
      RideNodeDud
   };
   TFlatRideNodeType mNodeType;   // what part to build
   STrig trig;
   short nCount;
   short nSpeed;
   float fOffset;
   float fWidth;
   float fHeight;
   float fLength;
   float fAngle;
   float fDrop; // used for suspended items or offsets
//   float fTwistAngle;
//   float fBendAngle;
   PartGuide ()
      : trig(0,0,0,1.0)
   {
      Clear ();
   }
   int   TakeANumber()
   {
      return iNextNode++;  // take currrent then bump
   }
   void  Clear()
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
protected:
   int   iNextNode;
};

class FlatRideBuilder
{
public:
   FlatRideBuilder(void);
   ~FlatRideBuilder(void);
   
   // Game Manager Interaction
   static Ride* CreateRide(int iPattern, Park& pPark);

   // UI Interaction
   void MakeSection( PartGuide& guide, Ride& ride );
   bool SetParameter( int node, int parameter, int id, float value );
   // some rides need supports and legs.
   ObjectBase* Support( Vector3f pt, PartGuide& guide, float MountAngle, float Load, float fBaseHeight );

   static RideNode* AddRideNodePlatForm (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeBase (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeHub (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeStrut (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeArm (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeDeck (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeCar (RideNode* pParent, ObjectNode* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeDisc (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeCarriage (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeCableHinge (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeRotationHub (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeLiftArm (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
};


/* Ride list quick reference as of 2-24-2010
Alakazaam - Star_Ranger4 (Nailed)
Austin "Fly Plane" Star_Ranger4 (Nailed)
Aviator - Star_Ranger4 (Nailed)
Balloon Race - Meph (Nailed)
Barnstormer - Star_Ranger4 (Nailed)
Bounty Swingship - Star_Ranger4 (Nailed)
Bulgy The Whale (Kid ride) - Star_Ranger4 (Nailed)
Bumpercar Tube - Doughnuts (Nailed)
Bumpercar Modern - Doughnuts (Nailed)
Bumper Car - retro (AutoSkooter) - aelk2004 (Nailed)
Bumpercar Retro 1932 (Dodg'em) - aelk2004 (Nailed)
Bumpercar Retro 1957 (Dodg'em) - aelk2004 (Nailed)
Carousel Double Decker - Gadget (Nailed)
Carousel Grand - Gadget (Nailed)
Carousel Regular - Gadget (Nailed)
Carousel Small - Gadget (Nailed)
Chance Giant Wheel - WCBoudreaux (Nailed)
Chance Rotor - Star_Ranger4 (Nailed)
Chance Skydiver - Star_Ranger4 (Nailed)
Chaotic - Surfingoz (Nailed)
Chance Tumbler - Star_Ranger4 (Nailed)
Chance Turbo/Radar - Star_Ranger4 (Nailed)
Coney Island Parachute Jump ( 1939 ) - GermanTaco (Nailed)
Cobra - Star_Ranger4/Mikey98 (Nailed)
Crazy Bus - Star_Ranger4 (Nailed)
Crazy Dance - by X-treme Coaster/Star_Ranger4 (Nailed)
Crazy Fire Brigade - Star_Ranger4 (Nailed)
Crazy Plane - Star_Ranger4 (Nailed)
Crazy Sub - Star_Ranger4 (Nailed)
Disk - O - Star_Ranger4 (Nailed)
Eli Ferris wheel - WCBoudreaux (Nailed)
Enterprise - Star_Ranger4 (Nailed)
Eyerly Octopus - WCBoudreaux (Nailed)
Eyerly Dual Bucket Octopus - Star_Ranger4 (Nailed)
Eyerly Fly-O-Plane - Star_Ranger4 (Nailed)
Eyerly Loop-O-Plane (Hammer) - Star_Ranger4 (Nailed)
Eyerly Monster - Star_Ranger4 (Nailed)
Eyerly Rock-O-Plane - Star_Ranger4 (Nailed)
Eyerly Roll-O-Plane - Star_Ranger4 (Nailed)
Eyerly Sidewinder - Star_Ranger4 (Nailed)
Eyerly Spider - Dual Pod - Star_Ranger4 (Nailed)
Eyerly Spider - Single Pod - Star_Ranger4 (Nailed)
Fabbri Booster - Star_Ranger4 (Nailed)
FlyAway - Star_Ranger4 (Nailed)
Flying Circus - Gadget (Nailed)
Flying Elephants - Surfingoz (Nailed)
Flying Scooters - Star_Ranger4 (Nailed)
Gravitron - Surfingoz (Nailed)
High Ride (aka. Sky Hook, Sky Ride) - Star_Ranger4 (Nailed)
High Roller/Crazy Train - Star_Ranger4 (Nailed)
Huss Boost - Star_Ranger4 (Nailed)
Huss Claw - Star_Ranger4 (Nailed)
Huss Condor - Star_Ranger4 (Nailed)
Huss Frisbee - Star_Ranger4 (Nailed)
Huss Giant Frisbee - Star_Ranger4 (Nailed)
Huss Jump 1 - Star_Ranger4 (Nailed)
Huss Skylab - Star_Ranger4 (Nailed)
Huss Takeoff - Star_Ranger4 (Nailed)
Intamin AG Flight Trainer - Star_Ranger4 (Nailed)
Intamin Double Wheel - Star_Ranger4 (Nailed)
Intamin Drop Tower - SR3D (Nailed)
Intamin Parachute Drop - in Cages stand-up/(Double Skycabin) Combo Ride - GermanTaco (Nailed)
Intamin Triple Wheel - Star_Ranger4 (Nailed)
Kamikazee - WCBoudreaux (Nailed)
Keefe Wheel - Star_Ranger4 (Nailed)
Kiddie Ride Construction Set 01 - Star_Ranger4 (Nailed)
Mega Disk - O - Star_Ranger4 (Nailed)
Moby Dick - Mephiles (Nailed)
Mondial Splashover - Surfingoz (Nailed)
Paratrooper Ride - Star_Ranger4 (Nailed)
Pharoah's Fury - Star_Ranger4 (Nailed)
Polyp - Star_Ranger4 (Nailed)
Qui-Diver - Star_Ranger4 (Nailed)
Rainbow - WCBoudreaux (Nailed)
Rocket Astro Jets - Surfingoz (Nailed)
Robinson Planetary Wheel Ferris Wheel Double Arm (Space Ride) - Star_Ranger4 (Nailed)
Roundup - GermanTaco (Nailed)
Scrambler/Twist - Star_Ranger4 (Nailed)
Sea Dragon Swing Ship - Star_Ranger4 (Nailed)
Seattle Wheel - Star_Ranger4 (Nailed)
Shepherd Galaxy Wheel(1960) - Star_Ranger4 (Nailed)
Shepherd Roll-O-Liner(1940) - Star_Ranger4 (Nailed)
Shepherd Roll-O-Plane - Star_Ranger4 (Nailed)
Shuttle Swing ship - Star_Ranger4 (Nailed)
Sky Coaster - JungleGuy (Nailed)
SkyQuad - Star_Ranger4 (Nailed)
Skyswatter - Star_Ranger4 (Nailed)
Skywheel (Chance Version) - Star_Ranger4 (Nailed)
Spillman Doublewhirl - Star_Ranger4 (Nailed)
Spinning Cups - Star_Ranger4 (Nailed)
Stantzel Strat-O-Liner Star_Ranger4 (Nailed)
Starflyer - Star_Ranger4 (Nailed)
Super Looper - Star_Ranger4 (Nailed)
Tagada - Star_Ranger4 (Nailed)
Tannenbaum Christmas Tree Ride - Surfingoz (Nailed)
Thunder Bolt/Flying Bobs/Alpine Bobs - WCBoudreaux (Nailed)
Tilted Whirler/G5 - Star_Ranger4 (Nailed)
Tivoli Orbitor - DJfriktion/Star_Ranger4 (Nailed)
Top Scan - Star_Ranger4 (Nailed)
Top Spin - Surfingoz (Nailed)
Tornado - Star_Ranger4 (Nailed)
Trabant - WCBoudreaux (Nailed)
Traver Circle Swing - Star_Ranger4 (Nailed)
Tri-Diver - Star_Ranger4 (Nailed)
UFO Aircar - Doughnuts (Nailed)
Velare Spacewheels - Star_Ranger4 (Nailed)
Waltzer/Super Waltzer - Star_Ranger4 (Nailed)
Watkins Rampage - Star_Ranger4 (Nailed)
Wave Swinger - Surfingoz (Nailed)
Wipeout - WCBoudreaux (Nailed)
Yo-Yo - Mikey98/Star_Ranger4 (Nailed)
Zamperla Nitro - Star_Ranger4 (Nailed)
Zipper - Surfingoz (Nailed)
*/