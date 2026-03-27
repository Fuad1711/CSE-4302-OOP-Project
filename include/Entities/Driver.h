#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include "Vehicle.h"
#include "../Common/Geolocation.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Driver : public User {
private:
string licenseNumber;
Vehicle vehicle;          // Aggregation: Driver HAS-A Vehicle
float rating;
int ratingCount;
bool isAvailable;
Geolocation currentLocation;

public:
    Driver();

    Driver(string firstName, string lastName, string phoneNumber,
           string address, int day, int month, int year, string email,
           string uname, string password, 
           string licenseNum, string vType, string vModel, 
           string lPlate, float initialRating = 0.0, Geolocation currLoc=Geolocation());

    string getLicenseNumber() const;
    string getVehicleType() const;
    string getVehicleModel() const;
    string getLicensePlate() const;
    Geolocation getCurrentLocation() const;
    float getRating() const;
    bool getAvailability() const;

    void setLicenseNumber(string lNum);
    void setVehicleType(string vType);
    void setVehicleModel(string vModel);
    void setLicensePlate(string lPlate);
    void setRating(float newRating);
    void setRatingCount(int count);
    void setCurrentLocation(Geolocation l);
    int getRatingCount() const;

    void toggleAvailability(); // Toggle between available/unavailable

    // Overridden methods from User class
    void updateProfile();
    void updateFile();
    void viewProfile();
    void saveData();
};

#endif // DRIVER_H
