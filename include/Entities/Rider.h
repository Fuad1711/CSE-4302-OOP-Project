#ifndef Rider_h
#define Rider_h

#include "User.h"
#include "../Common/Geolocation.h"
#include <iostream>
#include <string>
using namespace std;

class Rider : public User {
  private:
    Geolocation currentLocation;
    Geolocation dropoffLocation;
    float rating;
    int ratingCount;
    string preferredPaymentMethod;
    bool isRiding;

  public:
    Rider();

    Rider(string firstName, string lastName, string phoneNumber, string address,
          int day, int month, int year, string email, string uname,
          string password, float initialRating = 0.0,
          string defaultPayment = "Cash");

    // Getters
    Geolocation getCurrentLocation() const;
    Geolocation getDropoffLocation() const;
    float getRating() const;
    string getPreferredPaymentMethod() const;
    bool getRideStatus() const;

    // Setters
    void setCurrentLocation(Geolocation loc);
    void setDropoffLocation(Geolocation loc);
    void setRating(float newRating);
    void setRatingCount(int count);
    int getRatingCount() const;
    void setPreferredPaymentMethod(string method);
    
    // Core Methods
    void requestRide(Geolocation dropoff);
    void endRide();

    // Overridden methods
    void updateProfile();
    void viewProfile() override;
    void saveData();
};


#endif
