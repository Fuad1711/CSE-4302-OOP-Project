#ifndef FARE_CALCULATOR_H
#define FARE_CALCULATOR_H

#include "../Common/Types.h"
#include <string>

class FareCalculator {
private:
    double peakHourMultiplier = 1.5;
    double weekdayMultiplier = 1.2;

public:
    double getBaseFareForType(VehicleType type) const;
    double getPerKmRateForType(VehicleType type) const;
    
    double calculateFare(double distanceKm, VehicleType vehicleType,
                         bool isPeakHour = false, int dayOfWeek = 1) const;
    
    void displayFareBreakdown(double distanceKm, VehicleType type, 
                              bool isPeakHour = false, int dayOfWeek = 1) const;
};

#endif