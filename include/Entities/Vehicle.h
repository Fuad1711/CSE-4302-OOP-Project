#ifndef VEHICLE_H
#define VEHICLE_H

#include "../Common/Types.h"
#include <string>

class Vehicle {
private:
    VehicleType vehicleType;
    std::string model;
    std::string licensePlate;

public:
    Vehicle(VehicleType type, std::string mod, std::string plate)
        : vehicleType(type), model(mod), licensePlate(plate) {}

    VehicleType getType() const { return vehicleType; }
    std::string getModel() const { return model; }
    std::string getLicensePlate() const { return licensePlate; }
    
    std::string getTypeAsString() const;
};

#endif // VEHICLE_H
