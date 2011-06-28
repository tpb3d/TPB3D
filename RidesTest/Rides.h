#ifndef PeoopleMovement_H
#define PeeopleMovement_H
/*
Flat Rides are simlar to tracked rides in that flat rides are like a moving vehicle
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
class FlatRide
{
   
public:
FlatRide();

/*
FlatRide(string name,bool status,int placement, double load)
*/
FlatRide(string,bool,int,double);
~FlatRide();
   //functions

string DrawRide();
void DrawRideBase();
void DrawRideTower();
int placeRide();



  void GuestEnterQue();
  void loadPeeps(); //loads the guests onto the ride returns nothing yet.
  void startCycle(); //starts ride cycle
  double timeRide(); //times the duration of the ride.
  void unLoad();// stops the ride and unloads guests

  


  bool getLoad();// tells if ride is loaded. Default is ride is unloaded so it is true
  double getMinutes(); // gets how many minutes the ride will last(use input)
  double getSecond();// gets how many seconds the ride will last(user input)
  double getTotalTime();// gets and calculates the total ride time
  string getRideName(); // gets the the ride name
  bool getStatus();

   
protected:
	bool load;
	int total;
	bool capicity;
	double minutes;
	double second;
	double totalTime;
	string RideName;
	bool status;

};
    
#endif