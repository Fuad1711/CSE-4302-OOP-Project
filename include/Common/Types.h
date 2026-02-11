#ifndef TYPES_H
#define TYPES_H

#include <string>

enum class VehicleType { BIKE, CNG, CAR_AFFORDABLE, CAR_COMFORTABLE, CAR_LUXURY };
enum class RideStatus { REQUESTED, ASSIGNED, ONGOING, COMPLETED, CANCELLED };

struct GeoLocation {
    double latitude;
    double longitude;
};

#endif