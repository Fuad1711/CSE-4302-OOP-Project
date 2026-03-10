#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include <string>

using namespace std;

class Driver : public User {
  private:
    string licenseNumber;
    string vehicleType;
    string vehicleModel;
    string licensePlate;
    float rating;
    bool isAvailable;

  public:
    Driver();

    Driver(string firstName, string lastName, string phoneNumber,
           string address, int day, int month, int year, string email,
           string uname, string password, string licenseNum, string vType,
           string vModel, string lPlate, float initialRating = 0.0);

    string getLicenseNumber() const;
    string getVehicleType() const;
    string getVehicleModel() const;
    string getLicensePlate() const;
    float getRating() const;
    bool getAvailability() const;

    void setLicenseNumber(string lNum);
    void setVehicleType(string vType);
    void setVehicleModel(string vModel);
    void setLicensePlate(string lPlate);
    void setRating(float newRating);

    void toggleAvailability(); // Toggle between available/unavailable

    // Overridden methods from User class
    void updateProfile();
    void viewProfile();
    void saveData();
};

#endif // DRIVER_H
