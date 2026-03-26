#include "../include/Entities/Driver.h"
#include "../include/Entities/Rider.h"
#include "../include/Services/DriverMatchingService.h"
#include "../include/Services/Ride.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// ============ Load accounts from CSV ============

void loadRiders(vector<Rider *> &riders) {
    ifstream file("data/rider_credentials.csv");
    if (!file.is_open())
        return;
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        try {
            stringstream ss(line);
            string f[13];
            for (int i = 0; i < 12; i++)
                getline(ss, f[i], ',');
            getline(ss, f[12]); // last field
            riders.push_back(new Rider(f[0], f[1], f[2], f[3], stoi(f[7]),
                                       stoi(f[8]), stoi(f[9]), f[4], f[5], f[6],
                                       stof(f[10]), f[11]));
        } catch (...) {
            continue;
        } // skip bad lines
    }
    file.close();
}

void loadDrivers(vector<Driver *> &drivers) {
    ifstream file("data/driver_credentials.csv");
    if (!file.is_open())
        return;
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        try {
            stringstream ss(line);
            string f[16];
            for (int i = 0; i < 15; i++)
                getline(ss, f[i], ',');
            getline(ss, f[15]); // last field
            drivers.push_back(new Driver(
                f[0], f[1], f[2], f[3], stoi(f[7]), stoi(f[8]), stoi(f[9]),
                f[4], f[5], f[6], f[10], f[11], f[12], f[13], stof(f[14])));
        } catch (...) {
            continue;
        }
    }
    file.close();
}

// ============ Registration ============

Rider *registerRider() {
    cout << "\n--- Rider Registration ---" << endl;
    UserRegistrationData commonData = registerCommonData();

    string payment;
    cout << "Payment (Cash/Bkash): ";
    cin >> payment;

    Rider *newRider = new Rider(commonData.firstName, commonData.lastName, commonData.phoneNumber,
                                commonData.homeAddress, commonData.day, commonData.month,
                                commonData.year, commonData.email, commonData.userName,
                                commonData.password, 0.0, payment);
    newRider->saveData();
    cout << "Registration successful!" << endl;
    return newRider;
}

Driver *registerDriver() {
    cout << "\n--- Driver Registration ---" << endl;
    UserRegistrationData commonData = registerCommonData();

    string license, vType, vModel, plate;
    cout << "License: ";
    cin >> license;
    cout << "Vehicle type (Bike/CNG/Car): ";
    cin >> vType;
    cout << "Vehicle model: ";
    cin.ignore();
    getline(cin, vModel);
    cout << "License plate: ";
    cin >> plate;

    Driver *newDriver = new Driver(commonData.firstName, commonData.lastName, commonData.phoneNumber,
                                   commonData.homeAddress, commonData.day, commonData.month,
                                   commonData.year, commonData.email, commonData.userName,
                                   commonData.password, license, vType, vModel, plate);
    newDriver->saveData();
    cout << "Registration successful!" << endl;
    return newDriver;
}

// ============ Rider Menu ============

void riderMenu(Rider *rider, vector<Driver *> &drivers) {
    DriverMatchingService matcher;
    int choice = 0;
    while (choice != 4) {
        cout << "\n--- Rider Menu ---\nHello, " << rider->getFirstName() << "!"
             << endl;
        cout << "1. Request a Ride\n2. View Profile\n3. Update Profile\n4. "
                "Logout"
             << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            string pickupName, dropoffName;
            double pickLat, pickLon, dropLat, dropLon;
            cout << "\nPickup name: ";
            cin.ignore();
            getline(cin, pickupName);
            cout << "Pickup lat: ";
            cin >> pickLat;
            cout << "Pickup lon: ";
            cin >> pickLon;
            cout << "Dropoff name: ";
            cin.ignore();
            getline(cin, dropoffName);
            cout << "Dropoff lat: ";
            cin >> dropLat;
            cout << "Dropoff lon: ";
            cin >> dropLon;
            Geolocation pickup(pickLat, pickLon, pickupName);
            Geolocation dropoff(dropLat, dropLon, dropoffName);
            rider->setCurrentLocation(pickup);
            Driver *matched = matcher.findAvailableDriver(drivers);
            if (!matched) {
                cout << "No drivers available." << endl;
                continue;
            }
            cout << "\nDriver: " << matched->getFirstName() << " | "
                 << matched->getVehicleModel() << " ("
                 << matched->getVehicleType() << ") | "
                 << matched->getLicensePlate() << endl;
            Ride ride(rider, matched, pickup, dropoff);
            cout << "Fare: BDT " << ride.getFare() << endl;
            cout << "Confirm? (1=Yes / 0=No): ";
            int confirm;
            cin >> confirm;
            if (confirm != 1) {
                ride.cancelRide("Declined");
                continue;
            }
            ride.startRide();
            cout << "\n[Press 1 when arrived]: ";
            int x;
            cin >> x;
            ride.completeRide();
            ride.displayReceipt();
            cout << "Rate driver (1-5): ";
            int rating;
            cin >> rating;
            ride.rateDriver(rating);
        } else if (choice == 2) {
            rider->viewProfile();
        } else if (choice == 3) {
            rider->updateProfile();
        } else if (choice == 4) {
            cout << "Logging out..." << endl;
        }
    }
}

// ============ Driver Menu ============

void driverMenu(Driver *driver) {
    int choice = 0;
    while (choice != 4) {
        cout << "\n--- Driver Menu ---\nHello, " << driver->getFirstName()
             << "!" << endl;
        cout << "1. Toggle Availability ("
             << (driver->getAvailability() ? "Available" : "Unavailable") << ")"
             << endl;
        cout << "2. View Profile\n3. Update Profile\n4. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            driver->toggleAvailability();
        } else if (choice == 2) {
            driver->viewProfile();
        } else if (choice == 3) {
            driver->updateProfile();
        } else if (choice == 4) {
            cout << "Logging out..." << endl;
        }
    }
}

// ============ Main ============

int main() {
    vector<Rider *> riders;
    vector<Driver *> drivers;

    // Load saved accounts from CSV
    loadRiders(riders);
    loadDrivers(drivers);

    // Add default sample data if CSV was empty (first run)
    if (riders.empty()) {
        riders.push_back(new Rider("Abir", "Boss", "01712345678", "Mirpur", 1,
                                   1, 2000, "abir@test.com", "abir", "pass888",
                                   0.0, "Bkash"));
    }
    if (drivers.empty()) {
        drivers.push_back(new Driver(
            "Fuad", "Islam", "01812345678", "Uttara", 10, 5, 1990, "fuad@d.com",
            "fuad", "pass123", "D-001", "Car", "Toyota Corolla", "DHA-1234"));
        drivers.push_back(new Driver("Karim", "Ahmed", "01912345678", "Gulshan",
                                     15, 3, 1988, "karim@d.com", "karim",
                                     "pass456", "D-002", "Bike", "Honda CB150",
                                     "DHA-5678"));
        drivers.push_back(new Driver("Rahim", "Khan", "01612345678", "Banani",
                                     20, 8, 1992, "rahim@d.com", "rahim",
                                     "pass789", "D-003", "CNG", "Bajaj RE",
                                     "DHA-9012"));
    }

    cout << "Loaded " << riders.size() << " rider(s) and " << drivers.size()
         << " driver(s)." << endl;

    int choice = 0;
    while (true) {
        cout << "\n================================\n      PATHAO "
                "RIP-OFF\n================================"
             << endl;
        cout << "1. Login\n2. Register\n3. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        }
        if (choice == 2) {
            cout << "\n1. Rider\n2. Driver\nRegister as: ";
            int type;
            cin >> type;
            if (type == 1)
                riders.push_back(registerRider());
            else if (type == 2)
                drivers.push_back(registerDriver());
            continue;
        }
        if (choice == 1) {
            string uname, pass;
            bool found = false;
            cout << "Username: ";
            cin >> uname;
            cout << "Password: ";
            cin >> pass;
            for (int i = 0; i < (int)riders.size() && !found; i++)
                if (riders[i]->getUserName() == uname &&
                    riders[i]->getPassword() == pass) {
                    riderMenu(riders[i], drivers);
                    found = true;
                }
            for (int i = 0; i < (int)drivers.size() && !found; i++)
                if (drivers[i]->getUserName() == uname &&
                    drivers[i]->getPassword() == pass) {
                    driverMenu(drivers[i]);
                    found = true;
                }
            if (!found)
                cout << "Invalid username or password." << endl;
        }
    }
    for (int i = 0; i < (int)riders.size(); i++)
        delete riders[i];
    for (int i = 0; i < (int)drivers.size(); i++)
        delete drivers[i];
    return 0;
}