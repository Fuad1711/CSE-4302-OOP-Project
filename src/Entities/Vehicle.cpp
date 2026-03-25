#include "../../include/Entities/Vehicle.h"
#include <iostream>
using namespace std;

string Vehicle::getTypeAsString() const {
    switch (vehicleType) {
        case VehicleType::BIKE:            return "Bike";
        case VehicleType::CNG:             return "CNG";
        case VehicleType::CAR_AFFORDABLE:  return "Car (Affordable)";
        case VehicleType::CAR_COMFORTABLE: return "Car (Comfortable)";
        case VehicleType::CAR_LUXURY:      return "Car (Luxury)";
        default:                           return "Unknown";
    }
}