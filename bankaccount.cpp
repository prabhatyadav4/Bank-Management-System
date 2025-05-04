#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Color functions for console output
void Red()    { cout << "\033[31m"; }
void Green()  { cout << "\033[32m"; }
void Yellow() { cout << "\033[33m"; }
void Blue()   { cout << "\033[34m"; }
void Magenta(){ cout << "\033[35m"; }
void White()  { cout << "\033[37m"; }
void Reset()  { cout << "\033[0m"; }

// Bank account class
class bankAccount {
    private:
        string bankName = "SBI"; // Default bank name
        int bankCode; // Bank code
        string accountHolderName; // Account holder's name
        string accountNumber; // Account number
        string accountPassword; // Account password
        string aadharNum; // Aadhar number
        string email; // Email address
        string phoneNumber; // Phone number
        double balance; // Account balance
        vector<string> transactionHistory; // Transaction history
    
    public:
        void savetoFile(); // Save account data to file
        void loadfromFile(); // Load account data from file
        void mainMenu(); // Main menu after login
        void createAccount(); // Create a new account
        void loginBankAccount(); // Login to an account
        void depositMoney(); // Deposit money
        void withdrawMoney(); // Withdraw money
        void checkBalance(); // Check account balance
        void accountDetails(); // Display account details
        void alltransactionHistory(); // Display transaction history
};

// Save account data to a file
void bankAccount::savetoFile() {
    ofstream file(accountNumber + ".txt");
    if(file.is_open()){
        file<<accountHolderName<<endl;
        file<<accountNumber<<endl;
        file<<accountPassword<<endl;
        file<<aadharNum<<endl;
        file<<email<<endl;
        file<<phoneNumber<<endl;
        file<<balance<<endl;
        for(auto transaction: transactionHistory){
            file<<transaction<<endl;
        }
        file.close();
    }
    else{
        cout<<"Error File Opening!"<<endl;
    }
}

// Load account data from a file
void bankAccount::loadfromFile(){
    ifstream file(accountNumber + ".txt");
    if(file.is_open()){
        getline(file, accountHolderName);
        getline(file, accountNumber);
        getline(file, accountPassword);
        getline(file, aadharNum);
        getline(file, email);
        getline(file, phoneNumber);
        file>>balance;
        file.ignore();
        string transaction;
        while(getline(file, transaction)){
            transactionHistory.push_back(transaction);
        }
        file.close();
    }
    else{
        cout<<"Error File Opening!"<<endl;
    }
}

void bankAccount::mainMenu(){
    int choice;
    do{
        cout<<"--------------------------------------------------------------------------------------------"<<endl;
        cout<<"Enter 1 for Deposit Money"<<endl;
        cout<<"Enter 2 for Withdraw Money"<<endl;
        cout<<"Enter 3 for Check Balance"<<endl;
        cout<<"Enter 4 for Account Details"<<endl;
        cout<<"Enter 5 for Transaction History"<<endl;
        cout<<"Enter 6 for Log Out"<<endl;
        cout<<"---------------------------------------------------------------------------------------------"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        cin.ignore();
        system("cls");

        switch(choice){
            case 1: 
                depositMoney();
                break;
            case 2: 
                withdrawMoney();
                break;
            case 3: 
                checkBalance();
                break;
            case 4: 
                accountDetails();
                break;
            case 5: 
                alltransactionHistory();
                break;
            case 6: 
                cout<<"Logging Out..."<<endl; 
                break;
            default: 
               cout<<"Invalid Choice! Please Try Again.";
        }
    }
    while(choice != 6);
}

void bankAccount::createAccount(){
    cout<<"                 Create Account               "<<endl;
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    Green();
    cout<<"Enter your Full Name     : ";
    getline(cin, accountHolderName);
    cout<<"Enter E-mail Id          : ";
    getline(cin, email);
    cout<<"Enter your Phone Number  : ";
    getline(cin, phoneNumber);
    cout<<"Enter your Aadhar Number : ";
    getline(cin, aadharNum);
    cout<<"Set an Account Password  : ";
    getline(cin, accountPassword);
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    Reset();
    balance = 500.0;
    ifstream file("State-Bank-of-India.txt");
    if(file.is_open()){
        file>>bankCode;
        file.close();
        ofstream output("State-Bank-of-India.txt");
        if(output.is_open()){
            output<<bankCode+1;
            output.close();
        }
        else{
            cout<<"File Opening Error!"<<endl;
        }
    }
    else{
        cout<<"File Opening Error!"<<endl;
    }
    accountNumber = bankName + to_string(bankCode);
    transactionHistory.push_back("Deposit: " + to_string(balance));

    Yellow();
    cout<<"Account Created Successfully!"<<endl;
    cout<<"Account Number   : "<<accountNumber<<endl;
    cout<<"Account Password : "<<accountPassword<<endl;
    cout<<"Minimum Balance  : 500.0"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    Reset();
    savetoFile();
}

void bankAccount::loginBankAccount(){
    string enteredAccountNumber;
    string enteredPassword;
    Blue();
    cout<<"               Login Account               "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Enter Account Number     : ";
    getline(cin, enteredAccountNumber);
    accountNumber = enteredAccountNumber;
    ifstream file(enteredAccountNumber + ".txt");
    if(file.is_open()){
        loadfromFile();
        cout<<"Enter Account Password   : ";
        getline(cin, enteredPassword);
        if(accountPassword == enteredPassword){
            cout<<"Login Successful!"<<endl;
            mainMenu();
        }
        else{
            cout<<"Invalid Password!"<<endl;
        }
        file.close();
    }   
    else{
        cout<<"Account Not Found!"<<endl; 
    }
}

void bankAccount::depositMoney(){
    double amount;
    cout<<"Enter amount to be deposited: ";
    cin>>amount;
    cin.ignore();
    if(amount>0){
        balance += amount;
        transactionHistory.push_back("Deposit: " + to_string(amount));
        ofstream file(accountNumber + ".txt", ios::app);
        if(file.is_open()){
            cout<<"Deposit Successful!"<<endl;
            cout<<"Deposit: "+ to_string(amount) + "\n";
            file.close();
        }
        else{
            cout<<"Deposit Not Successful!: "<<endl;
        }
    }
    else{
        cout<<"Invalid Amount!"<<endl;
    }
}

void bankAccount::withdrawMoney(){
    double amount;
    cout<<"Enter the amount to be withdraw: ";
    cin>>amount;
    cin.ignore();
    if(amount>0 && amount <= balance){
        balance -= amount;
        transactionHistory.push_back("Withdraw : " + to_string(amount));
        ofstream file(accountNumber + ".txt", ios::app);
        if(file.is_open()){
            cout<<"Withdraw Successful!"<<endl;
            cout<<"New Balance: "<<balance<<endl;
            file<<"Withdraw:" + to_string(amount) + "\n";
            file.close();
        }
        else{
            cout<<"Withdraw Not Successful!"<<endl;
        }
    }
    else{
        cout<<"Invalid Amount!"<<endl;
    }
}

void bankAccount::checkBalance(){
    cout<<"Current Balance: "<<balance<<endl;
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
}

void bankAccount::accountDetails(){
    Red();
    cout<<"|-----------------------------|"<<endl;
    cout<<"|     State Bank of India     |"<<endl;
    cout<<"|-----------------------------|"<<endl;
    White();
    cout<<"Account Holder Name   : "<<accountHolderName<<endl;
    cout<<"Account Number        : "<<accountNumber<<endl;
    cout<<"Aadhar Number         : "<<aadharNum<<endl;
    cout<<"Email Id              : "<<email<<endl;
    cout<<"Phone Number          : "<<phoneNumber<<endl;
    cout<<"Current Balance       : "<<balance<<endl;
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    Reset();
}

void bankAccount::alltransactionHistory(){
    cout<<"Transaction History:"<<endl;
    Yellow();
    cout<<"----------------------------------------------------------------------------------------------"<<endl;
    cout<<"Account Holder Name: "<<accountHolderName<<endl;
    cout<<"Account Number: "<<accountNumber<<endl;
    for(const auto& transaction : transactionHistory){
        cout<< transaction<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------------"<<endl;
    Reset();
}

int main(){
    bankAccount account;
    int choice;
    do{
        cout<<" Welcome to State Bank of India"<<endl;
        cout<<"----------------------------------------------------------------------------------------------"<<endl;
        cout<<"1. Create Account"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cin.ignore();
        system("cls");
        switch(choice){
            case 1: 
                account.createAccount();
                break;
            case 2: 
                account.loginBankAccount();
                break;
            case 3: 
                cout<<"Exiting..."<<endl;
                break;
            default:
                cout<<"Invalid Choice! Please Try Again."<<endl;
        }
    }
    while(choice != 3);
    return 0;
}