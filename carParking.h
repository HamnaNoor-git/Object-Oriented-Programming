#pragma once
#include <string>
using namespace std;
class ParkingSlot
{

	int vehicleID;
	string ownerName;
	bool isParked;
	double parkingHours;

public:
	void parkVehicle();
	void removeVehicle();
	void addParkingHours(double hours);
	double getParkingHours() const;
	void display() const;
	ParkingSlot();
	ParkingSlot(int vehicleID, string ownerName);
	ParkingSlot(int vehicleID, string ownerName, bool isParked, double parkingHours);
	~ParkingSlot();
};