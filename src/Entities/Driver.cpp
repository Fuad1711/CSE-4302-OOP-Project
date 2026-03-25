#include "../../include/Entities/Driver.h"

Driver::Driver()
    : User(), licenseNumber(""), vehicleType(""), vehicleModel(""),
      licensePlate(""), rating(0.0), ratingCount(0), isAvailable(false) {
}

Driver::Driver(string firstName, string lastName, string phoneNumber,
               string address, int day, int month, int year, string email,
               string uname, string password,

               string licenseNum, string vType, string vModel, string lPlate,
               float initialRating)
    : User(firstName, lastName, phoneNumber, address, day, month, year, email,
           uname, password),
      licenseNumber(licenseNum), vehicleType(vType), vehicleModel(vModel),
      licensePlate(lPlate), rating(initialRating), ratingCount(0), isAvailable(true) {
} // true by default

string Driver::getLicenseNumber() const {
    return licenseNumber;
}
string Driver::getVehicleType() const {
    return vehicleType;
}
string Driver::getVehicleModel() const {
    return vehicleModel;
}
string Driver::getLicensePlate() const {
    return licensePlate;
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
    vehicleType = vType;
}
void Driver::setVehicleModel(string vModel) {
    vehicleModel = vModel;
}
void Driver::setLicensePlate(string lPlate) {
    licensePlate = lPlate;
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
        setVehicleType(vType);

        cout << "Enter new Vehicle Model: ";
        string vModel;
        cin >> vModel;
        setVehicleModel(vType);
        
        cout << "Enter new License Plate: ";
        string lPlate;
        cin >> lPlate;
        setLicenseNumber(lPlate);
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
    cout << "Vehicle: " << vehicleModel << " (" << vehicleType << ") - "
         << licensePlate << endl;
    cout << "Rating: " << rating << " Stars" << endl;
    cout << "Status: " << (isAvailable ? "Available" : "Currently Unavailable")
         << endl;
    return;
}

void Driver::saveData() {
    try{
        ofstream outFile("data/driver_credentials.csv", ios::app);
        if (!outFile.is_open()) {
            throw runtime_error("Could not open data/driver_credentials.csv");
        }
        outFile << firstName << "," << lastName << "," << phoneNumber << ","
                << homeAddress << "," << email << "," << userName << ","
                << password << "," << day << "," << month << "," << year << ","
                << licenseNumber << "," << vehicleType << "," << vehicleModel
                << "," << licensePlate << "," << rating << "," << isAvailable
                << "\n";
        outFile.close();
        cout << "Driver data saved successfully" << endl;
    }
    catch(const exception& e) {
        cerr << "File Error: " << e.what() << endl;
    }
}

