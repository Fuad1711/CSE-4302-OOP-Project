#include "../../include/Entities/Rider.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructors
Rider::Rider()
    : User(), currentLocation(0.0, 0.0), dropoffLocation(0.0, 0.0), rating(0.0),
      ratingCount(0), preferredPaymentMethod("Cash"), isRiding(false) {
}

Rider::Rider(string firstName, string lastName, string phoneNumber,
             string address, int day, int month, int year, string email,
             string uname, string password, float initialRating,
             string defaultPayment)
    : User(firstName, lastName, phoneNumber, address, day, month, year, email,
           uname, password),
      currentLocation(0.0, 0.0), dropoffLocation(0.0, 0.0),
      rating(initialRating), ratingCount(0),
      preferredPaymentMethod(defaultPayment), isRiding(false) {
}

// Getters
Geolocation Rider::getCurrentLocation() const {
    return currentLocation;
}
Geolocation Rider::getDropoffLocation() const {
    return dropoffLocation;
}
float Rider::getRating() const {
    return rating;
}
string Rider::getPreferredPaymentMethod() const {
    return preferredPaymentMethod;
}
bool Rider::getRideStatus() const {
    return isRiding;
}

// Setters
void Rider::setCurrentLocation(Geolocation loc) {
    currentLocation = loc;
}
void Rider::setDropoffLocation(Geolocation loc) {
    dropoffLocation = loc;
}
void Rider::setRating(float newRating) {
    rating = newRating;
}
void Rider::setRatingCount(int count) {
    ratingCount = count;
}
int Rider::getRatingCount() const {
    return ratingCount;
}
void Rider::setPreferredPaymentMethod(string method) {
    preferredPaymentMethod = method;
}

// Core Methods
void Rider::requestRide(Geolocation dropoff) {
    if (isRiding) {
        cout << "Already in a ride!" << endl;
        return;
    }
    dropoffLocation = dropoff;
    isRiding = true;

    double distance =
        currentLocation.calculateDistance(currentLocation, dropoffLocation);
    cout << "Ride requested successfully! Distance : " << distance << " units."
         << endl;
}

void Rider::endRide() {
    if (!isRiding) {
        cout << "Not in a ride." << endl;
        return;
    }
    isRiding = false;
    currentLocation = dropoffLocation;
    cout << "Success. You have arrived at your destination." << endl;
}

// Overriden methods
void Rider::updateProfile() {
    int choice;
    cout << "Update Rider Profile" << endl;
    cout << "1. Update Basic Info (Inherited)" << endl;
    cout << "2. Update Preferred Payment Method" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        User::updateProfile();
    } else if (choice == 2) {
        cout
            << "Enter new Preferred Payment Method (e.g., Cash, Card, Bkash): ";
        cin >> preferredPaymentMethod;
        cout << "Payment method updated successfully!" << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
    updateFile();
}

void Rider::viewProfile() {
    cout << "Rider Profile " << endl;
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Date of birth: " << day << "\\" << month << "\\" << year << endl;
    cout << "Address: " << homeAddress << endl;
    cout << "Email: " << email << endl;
    cout << "User Name:" << userName << endl;
    cout << "Rating: " << rating << " Stars" << endl;
    cout << "Preferred Payment: " << preferredPaymentMethod << endl;
    cout << "Status: " << (isRiding ? "In a Ride" : "Not in a Ride") << endl;
    cout << "Current Location: (" << currentLocation.getLatitude() << ", "
         << currentLocation.getLongitude() << ")" << endl;
    if (isRiding) {
        cout << "Destination: (" << dropoffLocation.getLatitude() << ", "
             << dropoffLocation.getLongitude() << ")" << endl;
    }
    cout << "---------------------" << endl;
    return;
}

void Rider::saveData() {
    try {
        ofstream outFile("data/rider_credentials.csv", ios::app);

        if (!outFile.is_open()) {
            throw runtime_error(
                "Unable to open data/rider_credentials.csv for saving.");
        }
        outFile << firstName << "," << lastName << "," << phoneNumber << ","
                << homeAddress << "," << email << "," << userName << ","
                << password << "," << day << "," << month << "," << year << ","
                << rating << "," << preferredPaymentMethod << "," << isRiding
                << "\n";

        outFile.close();
        cout << "Rider data saved successfully" << endl;
    } catch (const exception &e) {
        cerr << "File Error: " << e.what() << endl;
    }
}

void Rider::updateFile() {
    ifstream inFile("data/rider_credentials.csv");
    vector<string> fileData;
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string f[13];
            for (int i = 0; i < 12; i++) {
                getline(ss, f[i], ',');
            }
            getline(ss, f[12]); // Last data
            if (f[5] == oldUserName) {
                string updated =
                    firstName + "," + lastName + "," + phoneNumber + "," +
                    homeAddress + "," + email + "," + userName + "," +
                    password + "," + to_string(day) + "," + to_string(month) +
                    "," + to_string(year) + "," + to_string(rating) + "," +
                    preferredPaymentMethod + "," + to_string(isRiding);
                fileData.push_back(updated);
            } else {
                fileData.push_back(line);
            }
        }
        inFile.close();
    }

    ofstream outFile("data/rider_credentials.csv");
    if (outFile.is_open()) {
        for (auto &updatedLine : fileData) {
            outFile << updatedLine << endl;
        }
        outFile.close();
        oldUserName = userName;
    }
}
