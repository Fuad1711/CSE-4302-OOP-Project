#ifndef GEOLOCATION_H
#define GEOLOCATION_H

#include <math.h>
#include <string>

using namespace std;

class Geolocation {
private:
    double latitude;
    double longitude;
    string locationName;

public:
    Geolocation() : latitude(0.0), longitude(0.0), locationName("") {}
    Geolocation(double lat, double lon, string name="Fuadpara") 
        : latitude(lat), longitude(lon), locationName(name) {}

    double getLatitude() const {
        return latitude;
    }
    double getLongitude() const {
        return longitude;
    }
    string getLocationName() const {
        return locationName;
    }

    void setLatitude(double lat) {
        latitude = lat;
    }
    void setLongitude(double lon) {
        longitude = lon;
    }
    void setLocationName(string name) {
        locationName = name;
    }

    double calculateDistance(const Geolocation& other) const {
        double x = latitude - other.latitude;
        double y = longitude - other.longitude;
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    static double calculateDistance(const Geolocation& loc1, const Geolocation& loc2) {
        double x = loc1.latitude - loc2.latitude;
        double y = loc1.longitude - loc2.longitude;
        return sqrt(pow(x, 2) + pow(y, 2));
    }
};

#endif