#include "../include/Entities/Driver.h"
#include "../include/Entities/User.h"
#include <iostream>

using namespace std;

int main() {
  // User ayman("Aymannow", "Chowdhury", "017...", "Dhaka", 14, 2, 2005, "a@b.com",
  //            "ayman_nz", "pass123");
  // ayman.saveData();

  Driver fuad("fudu", "fudu", "018...", "Uttara", 10, 5, 1990, "fudu@d.com",
              "fuduish", "pass321", "D-123", "Car", "Toyota Corolla", "DHA-11");
  // fuad.viewProfile();
  fuad.saveData();

  return 0;
}