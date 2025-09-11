#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class Account {
private:
    string _login;
    int _accNum;
    float _balance = 0;

public:
    float getBalance() {
        return _balance;
    }

    string getLogin() {
        return _login;
    }

    int getAccNum() {
        return _accNum;
    }

    void withdraw(float withdrawAmount) {
        if (withdrawAmount > getBalance()) {
            std::cout << "Not enough money to withdraw!" << std::endl;
            std::cout << "You can withdraw only " << getBalance() << std::endl;
        } else {
            std::cout << "You withdrawn " << withdrawAmount << "$" << std::endl;
            _balance -= withdrawAmount;
            std::cout << "Now you have " << getBalance() << " on your account" << std::endl;
        }
    }

    void deposit(float amount) {
        std::cout << "You deposit " << amount << " $ " << "to your account" << std::endl;
        _balance += amount;
        std::cout << "Now you have " << getBalance() << " on your account" << std::endl;
    }

    void showInfo() {
        std::cout << "Your login : " <<_login << std::endl;
        std::cout << "Your account number : " << _accNum << std::endl;
        std::cout << "Your current balance : " << getBalance() << std::endl;
    }

    Account(const string &login, int accNum, const float balance) {
        _login = login;
        _accNum = accNum;
        _balance = balance;
    }
};

int interface() {
    std::cout << "\n";
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "1. Create new account" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Choice : ";
    int choice = 0;
    std::cin >> choice;
    return choice;
}

void loggedInInterface(Account &accVec) {
    int choice = 0;

    do {
        std::cout << "------------Logged in " << accVec.getLogin() << "------------" << std::endl;
        std::cout << "1. Deposit: " << std::endl;
        std::cout << "2. Withdraw: " << std::endl;
        std::cout << "3. Show full info: " << std::endl;
        std::cout << "4. Exit: " << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Select: ";
        std::cin >> choice;
        float amount;

        switch (choice) {
            case 1:
                std::cout << "Enter amount of $ what you want deposit : ";
                std::cin >> amount;
                accVec.deposit(amount);
                break;
            case 2:
                std::cout << "Write amount of $ what you want to withdraw : ";
                std::cin >> amount;
                accVec.withdraw(amount);
                break;
            case 3:
                accVec.showInfo();
                break;
        }
    } while (choice != 4);
}



void newAccountInterface(std::vector<Account> &accVec) {
    std::cout << "-------------Account creation--------------------------" << std::endl;
    std::cout << "Enter login : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string login;
    std::getline(std::cin, login);

    std::cout << "Enter account number : ";
    int accNum;
    std::cin >> accNum;

    std::cout << "Enter amount : ";
    float balance;
    std::cin >> balance;

    std::cout << "---------------------------------------" << std::endl;

    Account acc(login, accNum, balance);
    accVec.push_back(acc);
}

void loginInterface(vector<Account> &accVec) {
    std::cout << "-------------------Login---------------------";
    std::cout << "Enter login : ";
    string login;
    getline(cin >> ws, login);
    std::cout << "Enter account number : ";
    int accNum;
    std::cin >> accNum;
    std::cout << "---------------------------------------";

    for (int i = 0; i < accVec.size(); ++i) {
        if (login.compare(accVec[i].getLogin()) == 0 && accNum == accVec[i].getAccNum()) {
            loggedInInterface(accVec[i]);
        }
    }
}


int main() {
    vector<Account> accVec;
    while (true) {
        switch (interface()) {
            case 1:
                newAccountInterface(accVec);
                break;
            case 2:
                loginInterface(accVec);
                break;
            case 3:
                return 0;
        }
    }
}
