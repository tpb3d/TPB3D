#include "Rides.h"
#include "Irrlicht.h"
#include "DriverChoice.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;
using namespace irr;

using namespace core;
using namespace video;
using namespace gui;
using namespace io;
using namespace scene;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

int main()
{
	double minute =1;
	double second =3;
	double time =1.3;
	bool isopen = false;
	bool test = false;


	FlatRide*ride;
	ride = new FlatRide("test",isopen,minute,time);
	ride->DrawRideBase();

/*	video::E_DRIVER_TYPE driverChoice = driverChoiceConsole();
	if(driverChoice == video::EDT_COUNT)
	{
		return 1;
	}
	IrrlichtDevice* device = createDevice(driverChoice,core::dimension2d<u32>(1020,1024));
	device->setWindowCaption(L"Theme Park Builder 3D Ride Test");
	device->setResizable(true);
	*/
	return 0;
}