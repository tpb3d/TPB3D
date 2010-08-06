#pragma once
#include "../Types/Vector3.h"
#include "BuilderBase.h"

// forward decls
class Park;
class Ride;
class RideNode;
class ObjectBase;
class ObjectNode;
class RideController;
struct PartGuide;

/* Example of template patterns
   enum PatternNo
   {
      Static = 0, // just sits there
      Spinner,    // Kids simple spin around a hub
      Planetary,  // scrambler cars stationary on spining arms
      Orbital,    // planetary and the cars spin free
      Wobble,     // rotating and wobbling tub (Tagada)
      Disk,       // Rotating with lift arm (enterprise)
      Disco,      // rotating disc on track
      Carousel,   // rotating deck with seats/animals on reciprocal poles
      Centrifugue,  // spinning barrel (rotor).
      Flying,     // spinning hub with arms and suspended cars (Biplanes).
      Spider,     // 2 to n legs
      Articulated // Pivital arm (Robot, Flying Circus, 
   };
*/
class FlatRideBuilder : public BuilderBase
{
public:
   enum TempNums
   {
      Biplanes,
      Carousel,
      BasketRide,
      Scrambler,
      Spider,
      Polyp,
      Octopus,
      Enterprise
   };
public:
   FlatRideBuilder(void);
   ~FlatRideBuilder(void);

   // Game Manager Interaction
   static Ride* CreateRide(int iPattern, Park& pPark);

   // events
   void OnHit (int hit);
   void OnMove (const Vector3f& vec);

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
   static RideNode* AddRideNodeRotationJoint (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeRotationHub (RideController* pRCU, RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeLiftArm (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide);
   static RideNode* AddRideNodeSpinCar (RideNode* pParent, ObjectNode* pGraphicObject, PartGuide& guide);
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
