#include "../include/Entities/Driver.h"
#include "../include/Entities/Rider.h"
#include "../include/Services/Ride.h"
#include <iostream>
using namespace std;

int main() {
    Driver fuad("Fuad", "Islam", "018...", "Uttara", 10, 5, 1990, "fuad@d.com",
                "fuadish", "pass321", "D-123", "Car", "Toyota Corolla", "DHA-11");

    Rider abir("Abir", "Boss", "017...", "Mirpur", 1, 1, 2000, "abir@test.com",
               "abir123", "pass888", 0.0, "Bkash");

    Geolocation dhaka(23.8103, 90.4125, "Dhaka");
    Geolocation banani(23.7940, 90.4043, "Banani");

    cout << "=== Rating Test ===" << endl;
    cout << "Initial Driver Rating: " << fuad.getRating() << " (count: " << fuad.getRatingCount() << ")" << endl;

    // Ride 1: rate driver 4 -> Expected avg = 4.0
    abir.setCurrentLocation(dhaka);
    Ride ride1(&abir, &fuad, dhaka, banani);
    ride1.startRide();
    ride1.completeRide();
    ride1.rateDriver(4);
    cout << "After ride 1 (rated 4): avg = " << fuad.getRating()
         << " (count: " << fuad.getRatingCount() << ")  [expected: 4.0]" << endl;

    // Ride 2: rate driver 2 -> Expected avg = 3.0
    abir.setCurrentLocation(dhaka);
    Ride ride2(&abir, &fuad, dhaka, banani);
    ride2.startRide();
    ride2.completeRide();
    ride2.rateDriver(2);
    cout << "After ride 2 (rated 2): avg = " << fuad.getRating()
         << " (count: " << fuad.getRatingCount() << ")  [expected: 3.0]" << endl;

    // Ride 3: rate driver 5 -> Expected avg = 3.67
    abir.setCurrentLocation(dhaka);
    Ride ride3(&abir, &fuad, dhaka, banani);
    ride3.startRide();
    ride3.completeRide();
    ride3.rateDriver(5);
    cout << "After ride 3 (rated 5): avg = " << fuad.getRating()
         << " (count: " << fuad.getRatingCount() << ")  [expected: 3.67]" << endl;

    return 0;
}