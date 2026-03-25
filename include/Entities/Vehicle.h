#ifndef VEHICLE_H
#define VEHICLE_H

#include "../Common/Types.h"
#include<string>
using namespace std;

class Vehicle{
private:
    string vehicleModel;
    string vehicleId;
    string licensePlate;
    string vehicleColor;
    VehicleType type;
    double baseFare;
    double perKmRate;

public:
    Vehicle();

    Vehicle(string vModel,string vId, string lPlate, string col,
        double fare, double rate, VehicleType vType);

    //Getter
    string getModel() const;
    string getVehicleId() const;
    string getLicensePlate() const;
    string getVehicleColor() const;
    VehicleType getType() const;
    double getBaseFare() const;
    double getRate() const;
    
    //Setter
    void setModel(string m);
    void setVehicleId(string id);
    void setLicensePlate(string l);
    void setVehicleColor(string c);
    void setType(VehicleType v);
    void setBaseFare(double f);
    void setPerKmRate(double r);

    string vehicleTypeToString(VehicleType v);
    void displayInfo() const;
};

#endif 
