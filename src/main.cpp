#include "../include/Entities/Driver.h"
#include "../include/Entities/Rider.h"
#include "../include/Entities/User.h"
#include <iostream>

using namespace std;

int main() {
    // User ayman("Aymannow", "Chowdhury", "017...", "Dhaka", 14, 2, 2005,
    // "a@b.com",
    //            "ayman_nz", "pass123");
    // ayman.saveData();

    Driver fuad("fudu", "fudu", "018...", "Uttara", 10, 5, 1990, "fudu@d.com",
                "fuduish", "pass321", "D-123", "Car", "Toyota Corolla",
                "DHA-11");
    // fuad.viewProfile();
    fuad.saveData();

    Rider abir("Abir", "boss", "017...", "Mirpur", 1, 1, 2000, "abir@test.com",
               "abir123", "pass888", 4.9, "Bkash");

    abir.setCurrentLocation(GeoLocation(23.8103, 90.4125)); // Dhaka

    abir.requestRide(GeoLocation(23.7940, 90.4043)); // Banani
    abir.viewProfile();
    abir.endRide();
    abir.viewProfile();
    abir.saveData();

    return 0;
}