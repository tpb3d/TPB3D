//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride Forming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../CoreObjects/RideBase.h"
#include "../CoreObjects/Ride.h"
#include "../Graphics/VPoint.h"
#include "../Graphics/Image.h"
#include "../Graphics/MeshNode.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/TexturedMesh.h"
#include "../Graphics/ObjectFactory.h"
#include "RideFormer.h"

#include "../CoreObjects/Park.h" // access to the park for the car path (will change)

/* Legend
CA - Catapult
RA - Randome Movement
RO - Roundabout
SW - Swing
TR - Tracked Flatride
VT - Vertical
WH - Wheel
CA - Center Axle
SA - Spoke arms
LA - Lift Arm

Aviator - RO, CA, SA, cars on wirs
Alakazaam - RO, CA, SA, cars on struts
Austin Fly Plane - WH - Single wheel, rocket cars roll on gravity
Ballon Race - RO, CA, SA, SW, ballon cars direct attached, basket swings out.
Barnstormer - RO, CA, SA, planes on wires
Breakdance - RO
Bulgy Whale - RO, CA, CA, whale cars on the splines
BumberCars - Free Range in a box
Carousels - RO, 2xDisks top and bottom, reciprocating poles with saddle seats, or benches. 1,2 or 3 rows.
Chance Tumbler, Radar- WH, Double Wheel
Chance Skydiver - Wh Large wheel (need more details)
Chance Tumbler - WH+WH - Axel with 2 wheels, mounted to a large rotating frame on a second axel.
Chaotic - RO, WH - Wheel on tilt-lift platform .
Cobra - RO, CA, tilted cross bar that rotates on CA supporting two spining cariages with multiple cars. on each.
Crazy Bus - SW - Large Platform with rows os seats mounted on a swing arm that revolves 360 deg, seating remains level.
Crazy Dance - Ro - three spinning sets of arms with 3 or more cars on a rotating platform.
Diablo - RO, LA - rotating carriage mounted on a tilt arm lifts the carriage into the air while spinning it.
Disk-O - TR - rotating disc of seats rides on a horseshoe shuttle track with optional hump in track.
DiveBomber - RO
Donner Cicle Swing - RO
Eli Ferris Wheel - WH
Enyterprise - RO, WH, SA - Wheel on tilt-lift platform. Cars are end mounted to spokes so that they swing out.
Everly Fly-O-plane - RO, CA, SA, SW, planes swing out on stiff arms.
Everly Loop-O-plane - Support pilon, CA, SA, SW, four planes revolve on dual armes in opposite directions.
Everly Monster - RO, CA, SA - mutiple arms, spinning carraiges and muliple cars per carriage.
Everly Octopus - CA, RO, LA, stiff arms life via an off of a rotating crank the operator can control.
Everly Rock-O-plane - WH - flipping cars
Everly Rock-O-plane - SW
Everly Sidewinder - SW
Everly Spider - CA, RO, LA, stiff arms life via an off of a rotating crank the operator can control, single car.
Everly Spider - CA, RO, LA, stiff arms life via an off of a rotating crank the operator can control, double car.
Fabbri Booster - SW - two pairs of outward facing seats gravity locked.
Flying Circus - SW, ?
Flying Elephants - RO, SA, simple cars.
Flying Scooters - RO, CA, SA, dual seats on wires with a large rudder to control swing out.
Giant Wonder Wheel - WH, TR - standard wheel cars and cars mounted on tracks.
Graviton - RO - simple revolving structure.
High Ride - Tower with cables that lift cages
High Roller/Crazy Train - TR - train on loop track that flips as the train goes around
Hymalaya - RO - cars mounted on the edges of a rotating undulating platform.
Huss Boost - RO - ?
Huss Jump1
Huss Jump2
Huss Skylab
Huss Takeoff
Intamin Sky Jom/Cabin combo
Keefe ferris wheel WH, SA - Three wheels mounted on a three spokes same axis
Intamin Double Wheel WH, SA - Two wheels mounted on a rotating arm same axis
Intamin Drop Tower VT - Seats mounted on carriage facing out. Carriage wraps the round, or four face tower.
Intamin AG Flight Trainer - Seats mounted on carriage facing to the side. Carriage wraps the round tower.
Intamin Triple Wheel - WH, TA, SA - three carriages on end of three spokes.
Kamikazee - Support pilon, CA, SA, SW, two planes revolve on dual armes in opposite directions, counter weight on opposite end of arms.
Klaus Satelitte Jets - ?
Mega Disk-O - Massive Disk-O
Moby Dick - Whale crazy bus
Mondial Splashover - PI, SW, FO wide rows of seats on a carriage that flips wile revolving on 2 syncronized arms.
Moonraker - RO, TA, another spinning tilting disc.
Music Express - see Hymalaya
Parachute Jump - CP, SP, parachutes on cables
Paratrooper - see ballon race
Pendulum Ride - variations on A frame with pendulum swining a carriage of varying seat configurations.
Planetary Wheel - see cobra but arm is bent 80 so that one carriage is up when the other is up on it's side.
Polyp Ride - see everly monster with 4 arms
Rainbow - large version of crazy buss with huge arm and counterweight.
Rocket Astro Jets -  RO, SA, jets on end os spokes center mounted.
Rotor - see graveton with dropping floor.
Roundup, Gravity - RO, TA, walled wheel you lean against wall as ride spins it tilts up.
Scrambler - CA, SA, three carraiges with three seats that spin on the ends of the spoks.
Seattle Wheel - WH big wheel.
Shepard Galaxy - four wheels on one large wheel.
Shepard Roll-O-Liner - Campers moundet on ends so they roll as the wheel revolves.
Shepard Roll-O-Plane - see Everly.
Skycoaster - two pylons with a csble loop between that the rider flies through the air.
Skyswatter - PT - Platform with rows of seats on both ends. rides to the top then flipps over several times then returns flat.
Skywheel - see chance.
Space Wheels - WH dual wheels
Spillman Doublewhirl - RO, SA, WH, wheels on ends of spokes
Spining Cups - RO - cups that spin and revolve
Stantzel Strat-O-liner - RO, CP, SP - two planes on opposing arms swint out
Starflyer - RO, CP - flying chairs
Super Looper - TR, - Large traked loop with train inside the loop.
Swing Ships - PN - Pendulum with large ship or vessel.
Tagada - sprinningm wobbling disc
Tannenbaum - CA, SA - fixed cars end of spokes
Techno Jump - CA, SA - arms list seats on hydraulics independantly
Thunderbolt, Alpine/Flying Bobs - CA, SA spokes with cars on end roll on undulating trsck.
Tiling Wirlers - RO, CA - platform with spinning carriages have large quarter round seats with weight off center
Tivoli Orbitor - see mixer
Tivoli Scorpian - see mixer
Top Scan - see diablo but we
TOp Spin - see mondial
Tornado - ?
Trabant - see moonraker
Traver Circle Swing - CT, SA,  flying swings
Waltzer/Super - see music express
Watkins Rampage - double wheels
Wave Swinger - see Carousel
Whip- rolling cars mounted on arms attached to center chain that circles two pylons.
Wipeout - see orbitor and hymalaya
YoYo - CP, RO, SA, flying swings
Zipper = ferris wheel cars on large double guide

*/
RideFormer::RideFormer( Gfx::Texture* pTexture, Park& park)
:  mPark(park)
{
   mpTexture = pTexture;
}

RideFormer::~RideFormer(void)
{
}

//Ride* RideFormer::CreateRide()
//{
//   return new Ride( );
//}


void RideFormer::MakeSection( RideGuide& guide, Ride& Ride )
{
   int id = 400;
   int iTubeSections = 6;
}

