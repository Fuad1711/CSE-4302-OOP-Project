#ifndef GEOLOCATION_H
#define GEOLOCATION_H
#include<math.h>

class GeoLocation{
private:
    double latitude;
    double longitude;
    string locationName;
public:
    GeoLocation() : latitude(0.0), longitude(0.0) {}
    GeoLocation(double lat, double lon) : latitude(lat), longitude(lon) {}

    double  getLatitude() const{
        return latitude;
    }
    double getlongtitude() const{
        return longitude;
    }
    string getLocationName() const{
        return locationName;
    }
    void setLatitude(double lat){
        latitude = lat;
    }
    void setlongtitude(double lon){
        longitude = lon;
    }
    void setLocationName(string name){
        locationName=name;
    }
    double calculateDistance(const GeoLocation& location1, const GeoLocation& location2){
        double x = location1.latitude - location2.latitude;
        double y = location1.longitude - location2.longitude;
        return sqrt(pow(x, 2) + pow(y, 2));
    }
};

#endif