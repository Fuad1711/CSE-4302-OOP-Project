#include "../../include/Services/Ride.h"

#include <iomanip>
#include <iostream>
using namespace std;

int Ride::nextRideId = 1000;

//1 degree of latitude ≈ 111 km on the surface.
double Ride::toKm(double rawDist) const { return rawDist * 111.0; }

Ride::Ride()
    : rideId(++nextRideId), rider(nullptr), driver(nullptr),
      pickupLocation(), dropoffLocation(), distanceKm(0.0), fare(0.0),
      status(RideStatus::REQUESTED), paymentMethod(PaymentMethod::CASH),
      paymentStatus(PaymentStatus::PENDING),
      driverRating(0), riderRating(0) {}

Ride::Ride(Rider *r, Driver *d, Geolocation pickup, Geolocation dropoff, PaymentMethod pm)
    : rideId(++nextRideId), rider(r), driver(d),
      pickupLocation(pickup), dropoffLocation(dropoff),
      status(RideStatus::ASSIGNED), paymentMethod(pm),
      paymentStatus(PaymentStatus::PENDING),
      driverRating(0), riderRating(0) {

    Geolocation tmp;
    double raw = tmp.calculateDistance(pickup, dropoff);
    distanceKm = toKm(raw);
    string vt = driver->getVehicleType();
    VehicleType vehicleType = VehicleType::CAR_AFFORDABLE;
    if (vt == "Bike")                    vehicleType = VehicleType::BIKE;
    else if (vt == "CNG")                vehicleType = VehicleType::CNG;
    else if (vt == "Car (Affordable)")   vehicleType = VehicleType::CAR_AFFORDABLE;
    else if (vt == "Car (Comfortable)")  vehicleType = VehicleType::CAR_COMFORTABLE;
    else if (vt == "Car (Luxury)")       vehicleType = VehicleType::CAR_LUXURY;

    FareCalculator calc;
    fare = calc.calculateFare(distanceKm, vehicleType);
}

//getters
int Ride::getRideId() const{ return rideId; }
Rider *Ride::getRider() const{ return rider; }
Driver *Ride::getDriver() const{ return driver; }
Geolocation Ride::getPickupLocation() const{ return pickupLocation; }
Geolocation Ride::getDropoffLocation() const{ return dropoffLocation; }
double Ride::getDistanceKm() const{ return distanceKm; }
double Ride::getFare() const{ return fare; }
RideStatus Ride::getStatus() const{ return status; }
PaymentMethod Ride::getPaymentMethod() const{ return paymentMethod; }
PaymentStatus Ride::getPaymentStatus() const{ return paymentStatus; }

string Ride::statusToString() const{
    switch (status) {
    case RideStatus::REQUESTED:  return "Requested";
    case RideStatus::ASSIGNED:   return "Assigned";
    case RideStatus::ONGOING:    return "Ongoing";
    case RideStatus::COMPLETED:  return "Completed";
    case RideStatus::CANCELLED:  return "Cancelled";
    default:                     return "Unknown";
    }
}
string Ride::paymentMethodToString() const{
    return (paymentMethod == PaymentMethod::CASH) ? "Cash" : "Digital Wallet";
}
string Ride::paymentStatusToString() const{
    switch (paymentStatus){
    case PaymentStatus::PENDING: return "Pending";
    case PaymentStatus::SUCCESS: return "Paid";
    case PaymentStatus::FAILED:  return "Failed";
    default:                     return "Unknown";
    }
}

void Ride::startRide(){
    if(status != RideStatus::ASSIGNED){
        cout << "[Ride] Cannot start: ride is " << statusToString() << endl;
        return;
    }
    status    = RideStatus::ONGOING;
    if(driver) driver->toggleAvailability();
    cout << "[Ride #" << rideId << "] Started." << endl;
}

void Ride::completeRide(){
    if(status != RideStatus::ONGOING){
        cout << "[Ride] Cannot complete: ride is " << statusToString() << endl;
        return;
    }
    status  = RideStatus::COMPLETED;
    if(rider) rider->endRide();
    if(driver) {
        driver->toggleAvailability();
        driver->setCurrentLocation(dropoffLocation);
    }
    cout << "[Ride #" << rideId << "] Completed." << endl;
    processPayment();
}

void Ride::cancelRide(const string &reason){
    if(status == RideStatus::COMPLETED){
        cout << "[Ride] Already completed, cannot cancel." << endl;
        return;
    }
    status  = RideStatus::CANCELLED;
    if(driver && !driver->getAvailability())
        driver->toggleAvailability();
    cout << "[Ride #" << rideId << "] Cancelled";
    if(!reason.empty()) cout << " — " << reason;
    cout << endl;
}

bool Ride::processPayment(){
    if(paymentStatus == PaymentStatus::SUCCESS){
        cout << "[Payment] Already processed." << endl;
        return true;
    }
    paymentStatus = PaymentStatus::SUCCESS;
    cout << "[Payment] BDT " << fixed << setprecision(2) << fare
         << " collected via " << paymentMethodToString() << ". SUCCESS." << endl;
    return true;
}

void Ride::rateDriver(int rating){
    if(status != RideStatus::COMPLETED){
        cout << "[Rating] You can only rate after the ride is completed." << endl;
        return;
    }
    if(rating < 1 || rating > 5) { cout << "[Rating] Must be 1–5." << endl; return; }
    driverRating = rating;
    if(driver){
        int count = driver->getRatingCount();
        float updated = (driver->getRating() * count + rating) / (count + 1);
        driver->setRating(updated);
        driver->setRatingCount(count + 1);
    }
    cout << "[Rating] Driver rated " << rating << "/5. Thank you!" << endl;
}

void Ride::rateRider(int rating){
    if(status != RideStatus::COMPLETED){
        cout << "[Rating] You can only rate after the ride is completed." << endl;
        return;
    }
    if(rating < 1 || rating > 5) { cout << "[Rating] Must be 1–5." << endl; return; }
    riderRating = rating;
    if (rider) {
        int count = rider->getRatingCount();
        float updated = (rider->getRating() * count + rating) / (count + 1);
        rider->setRating(updated);
        rider->setRatingCount(count + 1);
    }
    cout << "[Rating] Rider rated " << rating << "/5. Thank you!" << endl;
}
void Ride::displayRideInfo() const{
    cout << "\n  ======= Ride #" << rideId << " =======" << endl;
    cout << "  Status   : " << statusToString() << endl;
    if(rider)  cout << "  Rider    : " << rider->getFirstName()  << " " << rider->getLastName()  << endl;
    if(driver) cout << "  Driver   : " << driver->getFirstName() << " " << driver->getLastName() << endl;
    cout << fixed << setprecision(6);
    cout << "  Pickup   : " << pickupLocation.getLocationName() << " (" << pickupLocation.getLatitude()   << ", " << pickupLocation.getLongitude()   << ")" << endl;
    cout << "  Dropoff  : " << dropoffLocation.getLocationName() << " (" << dropoffLocation.getLatitude()  << ", " << dropoffLocation.getLongitude()  << ")" << endl;
    cout << fixed << setprecision(2);
    cout << "  Distance : " << distanceKm << " km" << endl;
    cout << "  Fare     : BDT " << fare << endl;
    cout << "  Payment  : " << paymentMethodToString() << " [" << paymentStatusToString() << "]" << endl;
}

void Ride::displayReceipt() const{
    cout << "\n  ============================================" << endl;
    cout << "       PATHAO RIP-OFF  |  RECEIPT            " << endl;
    cout << "  ============================================" << endl;
    cout << "  Ride ID  : #" << rideId << endl;
    if(rider)  cout << "  Rider    : " << rider->getFirstName()  << " " << rider->getLastName()  << endl;
    if(driver) cout << "  Driver   : " << driver->getFirstName() << " " << driver->getLastName() << endl;
    if(driver) cout << "  Vehicle  : " << driver->getVehicleModel()
                     << " (" << driver->getVehicleType() << ")"
                     << " - " << driver->getLicensePlate() << endl;
    cout << "  From     : " << pickupLocation.getLocationName() << " (" << fixed << setprecision(4)
         << pickupLocation.getLatitude() << ", " << pickupLocation.getLongitude() << ")" << endl;
    cout << "  To       : " << dropoffLocation.getLocationName() << " (" << dropoffLocation.getLatitude() << ", " << dropoffLocation.getLongitude() << ")" << endl;
    cout << "  Distance : " << setprecision(2) << distanceKm << " km" << endl;
    cout << "  ----" << endl;
    cout << "  TOTAL    : BDT " << fare << endl;
    cout << "  Payment  : " << paymentMethodToString() << endl;
    cout << "  Status   : " << paymentStatusToString() << endl;
    cout << "  ============================================\n" << endl;
}
