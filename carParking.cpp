#include<iostream>
#include"25i3113_Lab07_1.h"
using namespace std;

void ParkingSlot::parkVehicle()
{
	isParked = true;
}
void ParkingSlot::removeVehicle()
{
	isParked = false;
}
void ParkingSlot::addParkingHours(double hours)
{
	parkingHours += hours;
}

double ParkingSlot::getParkingHours() const
{
	return parkingHours;
}

void ParkingSlot::display() const
{
	cout<<"PARKING INFORMATION\n----------------"
		<<"\nvehicleID: " << vehicleID 
		<<"\nownerName: "<<ownerName
		<<"\nisParked: "<< isParked
		<<"\nparkingHours: "<<parkingHours; 
}
ParkingSlot::ParkingSlot()
{
    vehicleID = 0;
    ownerName = "Unknown";
    isParked = false;
    parkingHours = 0;
}

ParkingSlot::ParkingSlot(int id, string name)
{
    vehicleID = id;
    ownerName = name;
    isParked = false;
    parkingHours = 0;
}

ParkingSlot::ParkingSlot(int id, string name, bool parked, double hours)
{
    vehicleID = id;
    ownerName = name;
    isParked = parked;
    parkingHours = hours;
}

ParkingSlot::~ParkingSlot()
{
	cout << "Parking record removed for " << ownerName <<endl;
}