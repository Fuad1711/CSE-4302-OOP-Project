#include "../../include/Entities/Driver.h"

// Helper: converts a string like "Car" to VehicleType enum
static VehicleType stringToVehicleType(const string &vType) {
    if (vType == "Bike")
        return VehicleType::BIKE;
    if (vType == "CNG")
        return VehicleType::CNG;
    if (vType == "Car")
        return VehicleType::CAR_AFFORDABLE;
    if (vType == "Car (Affordable)")
        return VehicleType::CAR_AFFORDABLE;
    if (vType == "Car Comfortable")
        return VehicleType::CAR_COMFORTABLE;
    if (vType == "Car (Comfortable)")
        return VehicleType::CAR_COMFORTABLE;
    if (vType == "Car Luxury")
        return VehicleType::CAR_LUXURY;
    if (vType == "Car (Luxury)")
        return VehicleType::CAR_LUXURY;
    return VehicleType::CAR_AFFORDABLE;
}

// Default Constructor
Driver::Driver()
    : User(), licenseNumber(""), vehicle(), rating(0.0), ratingCount(0),
      isAvailable(false) {
}

// Parameterized Constructor
Driver::Driver(string firstName, string lastName, string phoneNumber,
               string address, int day, int month, int year, string email,
               string uname, string password, string licenseNum, string vType,
               string vModel, string lPlate, float initialRating)
    : User(firstName, lastName, phoneNumber, address, day, month, year, email,
           uname, password),
      licenseNumber(licenseNum),
      vehicle(vModel, "", lPlate, "", 0.0, 0.0, stringToVehicleType(vType)),
      rating(initialRating), ratingCount(0), isAvailable(true) {
}

// Getters — delegate vehicle stuff to the Vehicle object
string Driver::getLicenseNumber() const {
    return licenseNumber;
}
string Driver::getVehicleType() const {
    return vehicle.vehicleTypeToString(vehicle.getType());
}
string Driver::getVehicleModel() const {
    return vehicle.getModel();
}
string Driver::getLicensePlate() const {
    return vehicle.getLicensePlate();
}
float Driver::getRating() const {
    return rating;
}
bool Driver::getAvailability() const {
    return isAvailable;
}

// Setters
void Driver::setLicenseNumber(string lNum) {
    licenseNumber = lNum;
}
void Driver::setVehicleType(string vType) {
    vehicle.setType(stringToVehicleType(vType));
}
void Driver::setVehicleModel(string vModel) {
    vehicle.setModel(vModel);
}
void Driver::setLicensePlate(string lPlate) {
    vehicle.setLicensePlate(lPlate);
}
void Driver::setRating(float newRating) {
    rating = newRating;
}
void Driver::setRatingCount(int count) {
    ratingCount = count;
}
int Driver::getRatingCount() const {
    return ratingCount;
}

// Core Methods
void Driver::toggleAvailability() {
    isAvailable = !isAvailable;
    cout << "Driver availability toggled to: "
         << (isAvailable ? "Available" : "Unavailable") << endl;
}

// Overridden Methods
void Driver::updateProfile() {
    viewProfile();
    int choice;

    cout << "Update Driver Profile" << endl;
    cout << "1. Update Basic Info (Inherited)" << endl;
    cout << "2. Update Vehicle Info" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        User::updateProfile();
    } else if (choice == 2) {
        cout << "Enter new Vehicle Type (e.g. Car, Bike): ";
        string vType;
        cin >> vType;
        vehicle.setType(stringToVehicleType(vType));

        cout << "Enter new Vehicle Model: ";
        string vModel;
        cin >> vModel;
        vehicle.setModel(vModel); // BUG FIX: was setVehicleModel(vType)

        cout << "Enter new License Plate: ";
        string lPlate;
        cin >> lPlate;
        vehicle.setLicensePlate(
            lPlate); // BUG FIX: was setLicenseNumber(lPlate)
        cout << "Vehicle information updated successfully!" << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
}

void Driver::viewProfile() {
    cout << "\nDriver Profile: " << endl;
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Date of birth: " << day << "\\" << month << "\\" << year << endl;
    cout << "Address: " << homeAddress << endl;
    cout << "Email: " << email << endl;
    cout << "User Name:" << userName << endl;
    cout << "License Number: " << licenseNumber << endl;
    cout << "Vehicle: " << vehicle.getModel() << " ("
         << vehicle.vehicleTypeToString(vehicle.getType()) << ") - "
         << vehicle.getLicensePlate() << endl;
    cout << "Rating: " << rating << " Stars" << endl;
    cout << "Status: " << (isAvailable ? "Available" : "Currently Unavailable")
         << endl;
    return;
}

void Driver::saveData() {
    try {
        ofstream outFile("data/driver_credentials.csv", ios::app);
        if (!outFile.is_open()) {
            throw runtime_error("Could not open data/driver_credentials.csv");
        }
        outFile << firstName << "," << lastName << "," << phoneNumber << ","
                << homeAddress << "," << email << "," << userName << ","
                << password << "," << day << "," << month << "," << year << ","
                << licenseNumber << ","
                << vehicle.vehicleTypeToString(vehicle.getType()) << ","
                << vehicle.getModel() << "," << vehicle.getLicensePlate() << ","
                << rating << "," << isAvailable << "\n";
        outFile.close();
        cout << "Driver data saved successfully" << endl;
    } catch (const exception &e) {
        cerr << "File Error: " << e.what() << endl;
    }
}
