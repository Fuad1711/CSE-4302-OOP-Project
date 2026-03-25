#ifndef RIDE_H
#define RIDE_H

#include "../Common/Geolocation.h"
#include "../Common/Types.h"
#include "../Entities/Driver.h"
#include "../Entities/Rider.h"
#include "FareCalculator.h"
#include <string>
using namespace std;

class Ride{
  private:
    static int nextRideId;
    int rideId;

    Rider *rider;
    Driver *driver;

    Geolocation pickupLocation;
    Geolocation dropoffLocation;
    double distanceKm;
    double fare;

    RideStatus status;
    PaymentMethod paymentMethod;
    PaymentStatus paymentStatus;

    int driverRating; 
    int riderRating;

    double toKm(double rawDist) const;

  public:
    Ride();
    Ride(Rider *r, Driver *d, Geolocation pickup, Geolocation dropoff,
         PaymentMethod pm = PaymentMethod::CASH);

    int getRideId() const;
    Rider *getRider() const;
    Driver *getDriver() const;
    Geolocation getPickupLocation() const;
    Geolocation getDropoffLocation() const;
    double getDistanceKm() const;
    double getFare() const;
    RideStatus getStatus() const;
    PaymentMethod getPaymentMethod() const;
    PaymentStatus getPaymentStatus() const;
    string statusToString() const;
    string paymentMethodToString() const;
    string paymentStatusToString() const;

    void startRide();
    void completeRide();
    void cancelRide(const string &reason = "");
    bool processPayment();
    void rateDriver(int rating);
    void rateRider(int rating);
    void displayRideInfo() const;
    void displayReceipt() const;
};

#endif
