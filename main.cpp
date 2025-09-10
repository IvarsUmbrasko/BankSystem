#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
private:
    string _login;
    string _password;
    float _balance = 0;

public:
    float getBalance() {
        return _balance;
    }

    void withdraw(float withdrawAmount) {
        if (withdrawAmount > getBalance()) {
            std::cout << "Not enough money to withdraw" << std::endl;
        } else {
            std::cout << "You withdrawn " << withdrawAmount << "$";
            _balance -= withdrawAmount;
            std::cout << "Now you have " << getBalance() << " on your account";
        }
    }

    void deposit(float amount) {
        std::cout << "You deposit " << amount << " $ " << "to your account";
        _balance += amount;
        std::cout << "Now you have " << getBalance() << " on your account";
    }

    void showInfo() {
        std::cout << _login << std::endl;
        std::cout << _password << std::endl;
        std::cout << getBalance() << std::endl;
    }

    Account(const string& login, const string& password, const float balance) {
        _login = login;
        _password = password;
        _balance = balance;
    }
};

int interface() {
    std::cout << "1. Create new account" << std::endl;
    std::cout << "2. Login" << std::endl;
    int choice = 0;
    std::cin >> choice;
    return choice;
}

void newAccountInterface(vector<Account>& accVec) {
    std::cout << "Enter login" << std::endl;
    string login;
    getline(cin, login);
    std::cout << "Enter password" << std::endl;
    string password;
    getline(cin, password);
    std::cout << "Enter amount" << std::endl;
    float balance;
    std::cin >> balance;
    Account acc(login, password, balance);
    accVec.push_back(acc);
}

void loggedInInterface() {
    char quit;
    do {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "1. Deposit: " << std::endl;
        std::cout << "2. Withdraw: " << std::endl;
        std::cout << "3. Show full info: " << std::endl;
        std::cout << "Select: ";
        int choice = 0;
        std::cin >> choice;
        std::cout << "---------------------------------------" << std::endl;

        std::cout << "Do you want continue? y/n : ";
        std::cin >> quit;
    } while (quit != 'n');
}


int main() {
    vector<Account> accVec;
    switch (interface()) {
        case 1:
            newAccountInterface(accVec);
            break;
        case 2:
            loggedInInterface();
            break;
    }
}
