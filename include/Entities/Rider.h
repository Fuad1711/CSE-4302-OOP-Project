#ifndef Rider_h
#define Rider_h

#include "User.h"
#include "../Common/Geolocation.h"
#include <iostream>
#include <string>
using namespace std;

class Rider : public User {
  private:
    GeoLocation currentLocation;
    GeoLocation dropoffLocation;
    float rating;
    string preferredPaymentMethod;
    bool isRiding;

  public:
    Rider();

    Rider(string firstName, string lastName, string phoneNumber, string address,
          int day, int month, int year, string email, string uname,
          string password, float initialRating = 0.0,
          string defaultPayment = "Cash");

    // Getters
    GeoLocation getCurrentLocation() const;
    GeoLocation getDropoffLocation() const;
    float getRating() const;
    string getPreferredPaymentMethod() const;
    bool getRideStatus() const;

    // Setters
    void setCurrentLocation(GeoLocation loc);
    void setDropoffLocation(GeoLocation loc);
    void setRating(float newRating);
    void setPreferredPaymentMethod(string method);
    
    // Core Methods
    void requestRide(GeoLocation dropoff);
    void endRide();

    // Overridden methods
    void updateProfile();
    void viewProfile() override;
    void saveData();
};


#endif
