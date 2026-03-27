#ifndef DRIVER_MATCHING_SERVICE_H
#define DRIVER_MATCHING_SERVICE_H

#include "../Entities/Driver.h"
#include <vector>
using namespace std;

class DriverMatchingService {
public:
    // Returns the first available driver, or nullptr if none found
    Driver* findAvailableDriver(vector<Driver*>& drivers,const Geolocation& riderLocation);
};

#endif
