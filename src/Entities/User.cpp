#include "../../include/Entities/User.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function Prototypes
bool is_Valid_Name(string name);
bool is_Valid_Number(string number);
bool is_Valid_Email(string email);
bool is_Valid_DOB(int day, int month, int year);
bool is_Valid_Username(string uname);
bool is_Taken_Username(string uname);
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
        int newDay, newMonth, newYear;
        switch (choice) {
        case 1:
            // Name
            cout << "Enter your first name: \n";
            cin >> newFirstName;
            while (!is_Valid_Name(newFirstName)) {
                cout << "\n Invalid! Please enter again" << endl;
                cin >> newFirstName;
            }
            firstName = newFirstName;

            cout << "Enter your last name: \n";
            cin >> newLastName;
            while (!is_Valid_Name(newLastName)) {
                cout << "\n Invalid! Please enter again" << endl;
                cin >> newLastName;
            }
            lastName = newLastName;
            break;
        case 2:
            // Phone Number
            cout << "Enter your phone number: \n";
            cin >> newNumber;
            while (!is_Valid_Number(newNumber)) {
                cout << "Invalid! Please enter again" << endl;
                cin >> newNumber;
            }
            phoneNumber = newNumber;
            break;
        case 3:
            // DOB
            cout << "Enter your date of Birth: \n";
            cin >> newDay >> newMonth >> newYear;
            while(!is_Valid_DOB(newDay,newMonth,newYear)){
                cout << "Invalid! Please enter again" << endl;
                cin >> newDay >> newMonth >> newYear;
            }
            day=newDay;
            month=newMonth;
            year=newYear;
            break;
        case 4:
            // Address
            cin.ignore();
            getline(cin, newAddress);
            homeAddress = newAddress;
            break;
        case 5:
            // Email
            cout << "Enter your email: ";
            cin >> newEmail;
            while (!is_Valid_Email(newEmail)) {
                cout << "Invalid! Please enter again" << endl;
                cin >> newEmail;
            }
            email = newEmail;
            break;
        case 6:
            // User name
            cout << "Enter a user name:";
            cin >> newUserName;
            while (is_Taken_Username(newUserName)) {
                cout << "Invalid! Please enter again";
                cin >> newUserName;
            }
            userName = newUserName;
            cout << "Username updated successfully" << endl;
            break;
        case 7:
            // Password
            string oldPassword;
            cout << "Enter your current password";
            cin >> oldPassword;
            if (oldPassword == password) {
                cout << "Enter new password (min 8 characters):" << endl;
                cin >> newPassword;

                while (!is_Valid_Password(newPassword) ||
                       newPassword != oldPassword) {
                    cout << "Invalid Password. Try again: " << endl;
                    cin >> newPassword;
                }
                password = newPassword;
                cout << "Password Updated" << endl;
            }
            break;
        
        default:
            break;
        }
    }
    updateFile();
}

User *Register() {

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
    while (is_Taken_Username(userName)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> userName;
    }

    // Password
    string password; // store password in csv file
    cout << "Enter a password of at least 8 characters: ";
    cin >> password;
    while (!is_Valid_Password(password)) {
        cout << "\n Invalid! Please enter again" << endl;
        cin >> password;
    }
    cout << "Error: Base abstract User cannot be instantiated via this function directly without knowing the derived type." << endl;
    return nullptr;
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

void User::updateFile() {
    ifstream inFile("data/User_credentials.csv");
    vector<string> fileData;
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            int position = line.find(',');
            string currentUser = line.substr(0, position);
            if (currentUser == userName) {
                string updated = userName + ',' + password + ',' + firstName +
                                 ',' + lastName + ',' + phoneNumber + ',' +
                                 email + ',' + to_string(day) + "/" +
                                 to_string(month) + "/" + to_string(year);
                fileData.push_back(updated);
            } else {
                fileData.push_back(line);
            }
        }
        inFile.close();
    }

    ofstream outFile("data/User_credentials.csv");
    if (outFile.is_open()) {
        for (auto &line : fileData) {
            outFile << line << endl;
        }
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
        if (!isdigit(c)) {
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

bool is_Taken_Username(string uname) {
    ifstream inFile("data/User_credentials.csv");
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            int position = line.find(',');
            string found = line.substr(0, position);
            if (uname == found) {
                return true;
            }
        }
        inFile.close();
    }
    return false;
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
