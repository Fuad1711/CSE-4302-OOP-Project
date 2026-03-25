#include "../../include/Entities/Vehicle.h"
#include<iostream>
#include<iomanip>
using namespace std;

Vehicle::Vehicle():licensePlate(""), vehicleId(""), 
    vehicleModel(""), type(BIKE), baseFare(0),
    perKmRate(0), vehicleColor(""){}

Vehicle::Vehicle(string vModel,string vID, string lPlate, string col,
        double fare, double rate, VehicleType vType) 
        : licensePlate(lPlate), vehicleId(vID), 
        vehicleModel(vModel), type(vType), baseFare(fare), 
        perKmRate(rate), vehicleColor(col){}

//Getter
string Vehicle::getModel() const{
    return vehicleModel;
}
string Vehicle::getVehicleId() const{
    return vehicleId;
}
string Vehicle::getLicensePlate() const{
    return licensePlate;
}
string Vehicle::getVehicleColor() const{
    return vehicleColor;
}
VehicleType Vehicle::getType() const{
    return type;
}
double Vehicle::getBaseFare() const{
    return baseFare;
}
double Vehicle::getRate() const{
    return perKmRate;
}

//Setter
void Vehicle::setModel(string m){
    vehicleModel=m;
}
void Vehicle::setVehicleId(string id){
    vehicleId=id;
}
void Vehicle::setLicensePlate(string l){
    licensePlate=l;
}
void Vehicle::setVehicleColor(string c){
    vehicleColor=c;
}
void Vehicle::setType(VehicleType v){
    type=v;
}
void Vehicle::setBaseFare(double f){
    baseFare=f;
}
void Vehicle::setPerKmRate(double r){
    perKmRate=r;
}

string Vehicle::vehicleTypeToString(VehicleType v){
    switch(v){
        case BIKE:
            return "Bike";
        case CNG:
            return "CNG";
        case CAR_AFFORDABLE:
            return "Car (Affordable)";
        case CAR_COMFORTABLE:
            return "Car (Comfortable)";
        case CAR_LUXURY:
            return "Car (Luxury)";
        default:
            return "N/A";
    }
}

void Vehicle::displayInfo() const{
    cout << left << setw(20) << "Model" << ": " << vehicleModel << endl;
    cout << left << setw(20) << "Vehicle ID" << ": " << vehicleId << endl;
    cout << left << setw(20) << "License Plate" << ": " << licensePlate << endl;
    cout << left << setw(20) << "Type" << ": " << vehicleTypeToString(type) << endl;
    cout << left << setw(20) << "Color" << ": " << vehicleColor << endl;
    
}