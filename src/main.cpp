#include <iostream>
#include "../include/Entities/User.h"

using namespace std;

int main() {
    User ayman("Aymannow", "Chowdhury", "017...", "Dhaka", 14, 2, 2005, "a@b.com", "ayman_nz", "pass123");
    ayman.saveData();
    return 0;
}