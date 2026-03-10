#include "../../include/Entities/User.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Function Prototypes
bool is_Valid_Name(string name);
bool is_Valid_Number(string number);
bool is_Valid_Email(string email);
bool is_Valid_DOB(int day, int month, int year);
bool is_Valid_Username(string uname);
bool is_Valid_Password(string password);

void User::updateProfile() {
    viewProfile();
    cout << "Update:" << endl;
    cout << "1.Name \n2.Phone Number\n 3.Date of Birth\n 4.Address 5.Email\n "
            "6.User Name 7.Password\n 8.Exit"
         << endl;
    int choice;
    while (cin >> choice && choice != 8) {
        string newFirstName;
        string newLastName;
        string newNumber;
        string newEmail;
        string newAddress;
        string newUserName;
        string newPassword;
        int day, month, year;
        switch (choice) {
        case 1:
            cout << "Enter your first name: ";
            cin >> newFirstName;
            while (!is_Valid_Name(newFirstName)) {
                cout << "\n Invalid! Please enter again" << endl;
                cin >> newFirstName;
            }
            firstName = newFirstName;

            cout << "Enter your last name: ";
            cin >> newLastName;
            while (!is_Valid_Name(newLastName)) {
                cout << "\n Invalid! Please enter again" << endl;
                cin >> newLastName;
            }
            lastName = newLastName;
            break;
        case 2:
            cout << "Enter your phone number: ";
            cin >> newNumber;
            while (!is_Valid_Number(newNumber)) {
                cout << "\n Invalid! Please enter again" << endl;
                cin >> newNumber;
            }
            phoneNumber = newNumber;
            break;
        // case 3://date of birth
        case 4:
            cin.ignore();
            getline(cin, newAddress);
            homeAddress = newAddress;
            break;
        case 5:
            cout << "Enter your email: ";
            cin >> newEmail;
            while (!is_Valid_Email(newEmail)) {
                cout << "\n Invalid! Please enter again" << endl;
                cin >> newEmail;
            }
            email = newEmail;
            break;
        case 6:
            cout << "Enter a user name:";
            cin >> newUserName;
            // username validity should be checked by searching the file and
            // looking for same username.
            break;
        case 7:
            // first check old password then allow to change
            cout << "Enter old password:";
            // match pasword
            cout << "Enter new password:";
            cin >> newPassword;
            password = newPassword;
            break;
        default:
            break;
        }
    }
}

void User::viewProfile() {
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Date of birth: " << day << "\\" << month << "\\" << year << endl;
    cout << "Address: " << homeAddress << endl;
    cout << "Email: " << email << endl;
    cout << "User Name:" << userName << endl;
    return;
}

User Register() {

    // Name
    string firstName, lastName;
    cout << "Enter your first name: ";
    cin >> firstName;
    while (!is_Valid_Name(firstName)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> firstName;
    }
    cout << "Enter your last name: ";
    cin >> lastName;
    while (!is_Valid_Name(lastName)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> lastName;
    }

    // Phone Number
    string phoneNumber;
    cout << "Enter your phone number: ";
    cin >> phoneNumber;
    while (!is_Valid_Number(phoneNumber)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> phoneNumber;
    }

    // Address
    string address;
    cout << "Enter your home address: ";
    cin.ignore();
    getline(cin, address);

    // Date of Birth
    int day, month, year;
    cout << "Enter your date of birth(DD\\MM\\YYYY): ";
    cin >> day >> month >> year;
    while (!is_Valid_DOB(day, month, year)) {
        cout << "Invalid! Please enter again" << endl;
        cin >> day >> month >> year;
    }

    // Email
    string email;
    cout << "Enter your email: ";
    cin >> email;
    while (!is_Valid_Email(email)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> email;
    }

    // User name
    string userName; // store the username in a csv file
    cout << "Enter a user name:";
    cin >> userName;
    while (!is_Valid_Username(userName)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> userName;
    }
    // username validity should be checked by searching the file and looking for
    // same username.

    // Password
    string password; // store password in csv file
    cout << "Enter a password of at least 8 characters: ";
    cin >> password;
    while (!is_Valid_Password(password)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> password;
    }
    User newUser(firstName, lastName, phoneNumber, address, day, month, year,
                 email, userName, password);
    return newUser;
}

void User::saveData() {
    ofstream outFile("data/User_credentials.csv", ios::app);

    if (outFile.is_open()) {
        outFile << userName << "," << password << "," << firstName << ","
                << lastName << "," << phoneNumber << "," << email << "," << day
                << "/" << month << "/" << year << endl;
        outFile.close();
    }
}

bool is_Valid_Name(string name) {
    for (unsigned char c : name) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool is_Valid_Number(string number) {
    for (unsigned char c : number) {
        if (isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool is_Valid_Email(string email) {
    int at_position;
    at_position = email.find_first_of("@");
    if (at_position < 0) {
        return false;
    } else {
        return true;
    }
}

bool is_Valid_Username(string uname) {
    ifstream inFile("data/User_credentials.csv");
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            int position = line.find(',');
            string found = line.substr(0, position);
            if (uname == found) {
                return false;
            }
        }
        inFile.close();
    }
    return true;
}

bool is_Valid_Password(string password) {
    if (password.size() >= 8) {
        return true;
    } else {
        return false;
    }
}

bool is_Valid_DOB(int day, int month, int year) {
    if (year < 1910 || year > 2026)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return (day <= 30);
    }
    if (month == 2) {
        bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (leap) {
            return (day <= 29);
        } else
            return (day <= 28);
    }
    return true;
}
