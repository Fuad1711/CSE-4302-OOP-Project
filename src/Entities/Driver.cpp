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
      isAvailable(false), currentLocation(0,0){}

// Parameterized Constructor
Driver::Driver(string firstName, string lastName, string phoneNumber,
               string address, int day, int month, int year, string email,
               string uname, string password,
               string licenseNum, string vType, string vModel,
               string lPlate, float initialRating, Geolocation currLoc)
    : User(firstName, lastName, phoneNumber, address, day, month, year, email,
        uname, password), licenseNumber(licenseNum),
        vehicle(vModel, "", lPlate, "", 0.0, 0.0, stringToVehicleType(vType)),
        rating(initialRating), ratingCount(0), isAvailable(true),currentLocation(currLoc) {}

// Getters — delegate vehicle stuff to the Vehicle object
string Driver::getLicenseNumber() const {
    return licenseNumber;
}
string Driver::getVehicleType() const {
    return vehicleTypeToString(vehicle.getType());
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
Geolocation Driver::getCurrentLocation() const {
    return currentLocation;
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
        vehicle.setModel(vModel); 

        cout << "Enter new License Plate: ";
        string lPlate;
        cin >> lPlate;
        vehicle.setLicensePlate(lPlate); 
        cout << "Vehicle information updated successfully!" << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
    updateFile();
}

void Driver::updateFile() {
    ifstream inFile("data/driver_credentials.csv");
    vector<string> fileData;
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string f[16];
            for(int i=0;i<15;i++){
                getline(ss,f[i],',');
            }
            getline(ss,f[15]);
            if (f[5] == oldUserName) {
                string updated = firstName + "," + lastName + "," + phoneNumber + "," + 
                homeAddress + "," + email + "," + userName + "," + password + "," +
                to_string(day) + "," + to_string(month) + "," + to_string(year) + "," + 
                licenseNumber + "," + vehicleTypeToString(vehicle.getType()) + "," + 
                vehicle.getModel() + "," + vehicle.getLicensePlate() + "," +
                to_string(rating) + "," + to_string(isAvailable ? 1 : 0);
                fileData.push_back(updated);
            } else {
                fileData.push_back(line);
            }
        }
        inFile.close();
    }

    ofstream outFile("data/driver_credentials.csv");
    if (outFile.is_open()) {
        for (auto &line : fileData) {
            outFile << line << endl;
        }
        outFile.close();
    }
    oldUserName = userName;
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
         << vehicleTypeToString(vehicle.getType()) << ") - "
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
                << vehicleTypeToString(vehicle.getType()) << ","
                << vehicle.getModel() << "," << vehicle.getLicensePlate() << ","
                << rating << "," << isAvailable << "\n";
        outFile.close();
        cout << "Driver data saved successfully" << endl;
    } catch (const exception &e) {
        cerr << "File Error: " << e.what() << endl;
    }
}
