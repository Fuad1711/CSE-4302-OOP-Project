#ifndef User_h
#define User_h
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
using namespace std;

class User{
    protected:

        string firstName;
        string lastName;
        string phoneNumber;
        string homeAddress;
        string email;
        string userName;
        string password;

        //Date of Birth
        int day,month,year;
        int age;
    public:

        User():firstName(),lastName(),phoneNumber(),homeAddress(),email(),userName(),password(),day(),month(),year(){}
        User(string firstName,string lastName, string phoneNumber,string address, int day, int month, int year, string email,string uname, string password):
        firstName(firstName),
        lastName(lastName),
        phoneNumber(phoneNumber),
        homeAddress(address),
        day(day),
        month(month),
        year(year),
        email(email),
        userName(uname),
        password(password){}
        void updateProfile();
        void viewProfile();
        void saveData();
};

#endif