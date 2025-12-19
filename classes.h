#include<iostream>
#include<string>
#include<cctype>


using namespace std;


class User{
    private:

        string firstName;
        string lastName;
        string phoneNumber;
        string homeAddress;
        string email;
        string userName;
        string password;

        int age;
        //Date of Birth
        int day;
        int month;
        int year;
    public:

        User():firstName(),lastName(),phoneNumber(),email(),password(){}
        User(string firstName,string lastName, string phoneNumber, int day, int month, int year, string email, string password):firstName(firstName),lastName(lastName),phoneNumber(phoneNumber),day(day),month(month),year(year),email(email),password(password){}
        void updateProfile(){
            viewProfile();
            cout<<"Update:"<<endl;
            cout<<"1.Name \n2.Phone Number\n 3.Date of Birth\n 4.Address 5.Email\n 6.User Name 7.Password\n 8.Exit" << endl;
            int choice;
            while(cin >> choice && choice!=8){
                string newFirstName;
                string newLastName;
                string newNumber;
                string newEmail;
                string newUserName;
                string newPassword;
                int day,month,year;

                switch (choice){
                    case 1:
                        cout << "Enter your first name: ";
                        cin >> newFirstName;
                        while (!is_Valid_Name(newFirstName)){
                            cout << "\n Invalid! Please enter again" << endl;
                            cin >> newFirstName;
                        }
                        firstName=newFirstName;

                        cout << "Enter your last name: ";
                        cin >> newLastName;
                        while (!is_Valid_Name(newLastName)){
                            cout << "\n Invalid! Please enter again" << endl;
                            cin >> newLastName;
                        }
                        lastName=newLastName;
                        break;
                    case 2:
                        cout << "Enter your phone number: ";
                        cin >> newNumber;
                        while (!is_Valid_Number(newNumber)){
                            cout << "\n Invalid! Please enter again" << endl;
                            cin >> newNumber;
                        }
                        phoneNumber=newNumber;
                        break;
                    // case 3://date of birth 
                    case 4:
                        cin >> homeAddress;
                        break;
                    case 5:
                        cout << "Enter your email: ";
                        cin >> newEmail;
                        while (!is_Valid_Email(newEmail)){
                            cout << "\n Invalid! Please enter again" << endl;
                            cin >> newEmail;
                        }
                        break;
                    case 6:
                    cout << "Enter a user name:";
                        cin >> newUserName;
                        //username validity should be checked by searching the file and looking for same username.
                        break;
                    case 7:
                        //first check old password then allow to change 
                        cout<<"Enter old password:";
                        //match pasword
                        cout<<"Enter new password:";
                        cin>>newPassword;
                        password=newPassword;
                        break;
                    default:
                        break;
                }
            }
        }

        void viewProfile(){
            cout << "Name: " << firstName << " " << lastName << endl;
            cout << "Phone Number: " << phoneNumber << endl;
            cout << "Date of birht: " << day << "\\" << month << "\\" << year << endl;
            cout << "Address: " << homeAddress << endl;
            cout << "Email: " << email << endl;
            cout << "User Name:" << userName << endl;
            return;
        }
        
    };
//Function Prototypes
User Register();
bool is_Valid_Number(string number);
bool is_Valid_Number(string number);
bool is_Valid_Email(string email);
bool is_Valid_Password(string password);

User Register(){
    string firstName;
    cout << "Enter your first name: ";
    cin >> firstName;
    while (!is_Valid_Name(firstName)){
        cout << "\n Invalid! Please enter again" << endl;
        cin >> firstName;
    }

    string lastName;
    cout << "Enter your last name: ";
    cin >> lastName;
    while (!is_Valid_Name(lastName)){
        cout << "\n Invalid! Please enter again" << endl;
        cin >> lastName;
    }

    string phoneNumber;
    cout << "Enter your phone number: ";
    cin >> phoneNumber;
    while (!is_Valid_Number(phoneNumber)){
        cout << "\n Invalid! Please enter again" << endl;
        cin >> phoneNumber;
    }

    int day, month, year;
    // cout << "Enter your date of birth(DD\MM\YYYY): ";
    // cin >> day >> month >> year;
    // while (!is_Valid_DOB(day,month,year)){
    //     cout << "Invalid! Please enter again" << endl;
    //     cin >> day >> month >> year;
    // }

    string email;
    cout << "Enter your email: ";
    cin >> email;
    while (!is_Valid_Email(email)){
        cout << "\n Invalid! Please enter again" << endl;
        cin >> email;
    }

    string userName; // store the username in a csv file
    cout << "Enter a user name:"; 
    cin >> userName;
    //username validity should be checked by searching the file and looking for same username.
    
    string password; // store password in csv file
    cout << "Enter a password of at least 8 characters: "; 
    cin >> password;
    while (!is_Valid_Password(password)){
        cout << "\n Invalid! Please enter again" << endl;
        cin >> password;
    }
    User newUser(firstName, lastName, phoneNumber, day, month, year, email, password);
    return newUser;
}
bool is_Valid_Name(string name){
    for (unsigned char c : name){
        if (!isalpha(c)){
            return false;
        }
    }
    return true;
}

bool is_Valid_Number(string number){
    for (unsigned char c : number){
        if (isalpha(c)){
            return false;
        }
    }
    return true;
}

bool is_Valid_Email(string email){
    int at_position;
    at_position = email.find_first_of("@");
    if (at_position < 0){
        return false;
    }
    else{
        return true;
    }
}
bool is_Valid_Password(string password){
    if (password.size() >= 8){
        return true;
    }
    else{
        return false;
    }
}
// bool is_Valid_DOB(int day,int month,int year) {
    
// }
