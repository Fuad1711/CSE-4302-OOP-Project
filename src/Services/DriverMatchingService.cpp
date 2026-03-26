#include "../../include/Services/DriverMatchingService.h"
#include <iostream>
using namespace std;

Driver* DriverMatchingService::findAvailableDriver(vector<Driver*>& drivers) {
    for (int i = 0; i < (int)drivers.size(); i++) {
        if (drivers[i]->getAvailability()) {
            return drivers[i];
        }
    }
    return nullptr;
}
