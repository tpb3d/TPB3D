// files to include
#include "Rides.h" // ride header. Every ride needs this so its a class.
#include <vector> // used to draw the line(hopefully)
#include <iostream> //basic input and output are needed here
#include <string> // used to get name of ride
#include <iomanip> // used to manuiplate decimals so we dont load half guests
#include <cstdlib>
#include <ctime>
#include <list>

FlatRide::FlatRide()
{
}
FlatRide::FlatRide(string name1,bool cap,int queueTotal,double load1)
{
	name1 = RideName;
	cap = capicity;
	queueTotal = total;
	load1 = load;
}

string FlatRide::DrawRide()
{
	/*
	This function assumes the user has chosen the base of a ride.
	Once that is the case the bas is the first thing drawn then placement occurs.
	Then the rest of the ride is drawn.
	*/
	string name;
	name = FlatRide::getRideName();
	cout << name;
	return name;
}

int FlatRide::placeRide()
{
	int coordinates[4];
	return 0;
}
void FlatRide::DrawRideBase()
{
}
void FlatRide::DrawRideTower()
{
}
void FlatRide::loadPeeps()
{
//guests enter ride from queue.
	// guests board and queue empties

	string name;

	int count =3;

list <string> guestName(2, "");
list <wchar_t> guestGender(2, 'M');
for(list<string>::iterator test=guestName.begin(); test!=guestName.end(); test++)
{
	guestName.push_front("Test");
}



/*	int number;
	srand(time(0));
	number = (rand() % 10) +1;


	
	for(int i =0; i=number; i++)
	{
		cout << "The number of people waiting in the line is: " << number -- << endl;;
		continue;
	}
*/

// funcion loads the guests on.  We start by calling a helper function to queue them and move them.
	
}

bool FlatRide::getLoad()
{
	return false;
}

double FlatRide::getSecond()
{
	return second;
}

string FlatRide::getRideName()
{
	return RideName;
}

bool FlatRide::getStatus()
{
	return status;
}