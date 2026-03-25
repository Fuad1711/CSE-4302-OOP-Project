#include "../../include/Services/FareCalculator.h"
#include <iostream>
#include <iomanip>
using namespace std;

double FareCalculator::getBaseFareForType(VehicleType type) const {
    switch (type) {
        case VehicleType::BIKE:            return 20.0;
        case VehicleType::CNG:             return 30.0;
        case VehicleType::CAR_AFFORDABLE:  return 50.0;
        case VehicleType::CAR_COMFORTABLE: return 80.0;
        case VehicleType::CAR_LUXURY:      return 150.0;
        default:                           return 50.0;
    }
}

double FareCalculator::getPerKmRateForType(VehicleType type) const {
    switch (type) {
        case VehicleType::BIKE:            return 10.0;
        case VehicleType::CNG:             return 15.0;
        case VehicleType::CAR_AFFORDABLE:  return 18.0;
        case VehicleType::CAR_COMFORTABLE: return 25.0;
        case VehicleType::CAR_LUXURY:      return 45.0;
        default:                           return 18.0;
    }
}
double FareCalculator::calculateFare(double distanceKm, VehicleType vehicleType,
                                     bool isPeakHour, int dayOfWeek) const {
    double base     = getBaseFareForType(vehicleType);
    double perKm    = getPerKmRateForType(vehicleType);
    double fare     = base + (distanceKm * perKm);
    
    if(isPeakHour) fare *= peakHourMultiplier;
    bool isWeekday = (dayOfWeek >= 1 && dayOfWeek <= 5);
    if(isWeekday) fare *= weekdayMultiplier;

    return fare;
}
void FareCalculator::displayFareBreakdown(double distanceKm, VehicleType type, bool isPeakHour, int dayOfWeek) const {
    double fare = calculateFare(distanceKm, type, isPeakHour, dayOfWeek);
    cout << fixed << setprecision(2);
    cout << "--- Fare Breakdown ---" << endl;
    cout << "Distance        : " << distanceKm <<" km"<< endl;
    cout << "Base Fare       : BDT " << getBaseFareForType(type)           << endl;
    cout << "Rate/km         : BDT " << getPerKmRateForType(type)          << endl;
    cout << "Peak Hour       : " << (isPeakHour ? "Yes (x" + to_string(peakHourMultiplier) + ")" : "No") << endl;
    cout << "Weekday         : " << (dayOfWeek>=1&&dayOfWeek<=5 ? "Yes" : "No") << endl;
    cout << "Total Fare      : BDT " << fare                               << endl;
    cout << "Driver Gets 80% : BDT " << fare * 0.80                       << endl;
    cout << "Platform Fee 20%: BDT " << fare * 0.20                       << endl;
}