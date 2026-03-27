#include "../../include/Services/DriverMatchingService.h"
#include <iostream>
using namespace std;

Driver* DriverMatchingService::findAvailableDriver(vector<Driver*>& drivers,const Geolocation& riderLocation) {
    double minDist=INT_MAX;
    Driver* bestDriver=nullptr;
    for (auto d: drivers) {
        if (!d->getAvailability()) continue;
        double dist=riderLocation.calculateDistance(d->getCurrentLocation());
        if(dist<minDist){
            minDist=dist;
            bestDriver=d;
        }
    }
    return bestDriver;
}
