#ifndef User_h
#define User_h
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cctype>
using namespace std;

struct UserRegistrationData {
    string firstName;
    string lastName;
    string phoneNumber;
    string homeAddress;
    string email;
    string userName;
    string password;
    int day, month, year;
};

class User{
protected:

    string firstName;
    string lastName;
    string phoneNumber;
    string homeAddress;
    string email;
    string userName;
    string oldUserName;
    string password;
    //Date of Birth
    int day,month,year;

public:

    User() : firstName(""), lastName(""), 
        phoneNumber(""), homeAddress(""), 
        email(""), userName(""), oldUserName(""),
        password(""), day(0), month(0), year(0){}
    
    User(string firstName, string lastName, 
        string phoneNumber,string address, 
        int day, int month, int year, 
        string email, string uname,
        string password)
        : firstName(firstName),
        lastName(lastName),
        phoneNumber(phoneNumber),
        homeAddress(address),
        day(day), month(month), year(year),
        email(email),
        userName(uname),
        oldUserName(uname),
        password(password){}

    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getUserName() const { return userName; }
    string getPassword() const { return password; }
    virtual void updateProfile();
    virtual void viewProfile()=0;
    virtual void saveData()=0;
    virtual void updateFile()=0;
};

UserRegistrationData registerCommonData();

#endif
