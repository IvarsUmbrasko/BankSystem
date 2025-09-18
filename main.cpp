#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>

class Account {
private:
    std::string _login;
    int _accNum;
    float _balance = 0;

public:
    std::string getLogin() {
        return _login;
    }

    int getAccNum() {
        return _accNum;
    }

    float getBalance() {
        return _balance;
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
        std::cout << "Your login : " << _login << std::endl;
        std::cout << "Your account number : " << _accNum << std::endl;
        std::cout << "Your current balance : " << getBalance() << std::endl;
    }

    Account(const std::string &login, int accNum, const float balance) {
        _login = login;
        _accNum = accNum;
        _balance = balance;
    }

    Account(const std::string &login, int accNum) {
        _login = login;
        _accNum = accNum;
    }
};

int startInterface() {
    std::cout << "\n";
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "1. Create new account"<< std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "4. Fetch all accounts" << std::endl;
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

bool checkAccountExistence(Account acc) {
    std::string text;
    int lineCnt = 0;
    bool halfVerification = false;
    std::ifstream OutputFile("../BankSystem/login.txt");

    while (getline(OutputFile, text)) {
        if (text.empty()) {
            lineCnt = 0;
            continue;
        }

        lineCnt++;

        switch (lineCnt) {
            case 1:
                if (text.compare(acc.getLogin()) == 0) {
                    halfVerification = true;
                }
                break;
            case 2:
                int fileAccNum = std::stoi(text);
                if (fileAccNum == acc.getAccNum() && halfVerification) {
                    return true;
                }
                lineCnt = 0;
                break;
        }
    }
    return false;
}

void fetchAllAccounts(std::vector<Account> &accVec) {
    std::string text;
    std::string login;
    int accNum {0};
    float balance {0};
    std::ifstream OutputFile("../BankSystem/login.txt");
    int lineCnt {0};

    while (getline(OutputFile, text)) {
        if (text.empty()) {
            lineCnt = 0;
            continue;
        }

        lineCnt++;

        if (lineCnt == 1 ) {
            login = text;
        } else if (lineCnt == 2) {
            accNum = std::stoi(text);
        } else if (lineCnt == 3) {
            balance = std::stof(text);
            accVec.push_back(Account(login, accNum, balance));
        }
    }

    for (int i = 0; i<accVec.size(); ++i) {
        std::cout << accVec[i].getLogin() << std::endl;
        std::cout << accVec[i].getAccNum() << std::endl;
        std::cout << accVec[i].getBalance() << std::endl;
    }
}

void writeAccountInFile(Account acc) {
    std::ofstream InputFile("../BankSystem/login.txt", std::fstream::app);
    InputFile << acc.getLogin() << "\n";
    InputFile << acc.getAccNum() << "\n";
    InputFile << acc.getBalance() << "\n";
    std::cout << "New account was saved successfully";
    InputFile.close();
}

void registrationInterface(std::vector<Account> &accVec) {
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

    Account acc(login, accNum, balance);
    if (!checkAccountExistence(acc)) {
        writeAccountInFile(acc);
        accVec.push_back(acc);
    } else {
        std::cout << "Account exists" << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
}

void loginInterface(std::vector<Account> &accVec) {
    std::cout << "-------------------Login---------------------" << std::endl;
    std::cout << "Enter login : ";
    std::string login;
    std::getline(std::cin >> std::ws, login);
    std::cout << "Enter account number : ";
    int accNum;
    std::cin >> accNum;
    std::cout << "---------------------------------------";

    Account acc(login, accNum);

    if (checkAccountExistence(acc)) {
        loggedInInterface(acc);
    } else {
        std::cout << "Account exists" << std::endl;
    }

    // for (int i = 0; i < accVec.size(); ++i) {
    //     if (login.compare(accVec[i].getLogin()) == 0 && accNum == accVec[i].getAccNum()) {
    //         loggedInInterface(accVec[i]);
    //     }
    // }
}


int main() {
    std::vector<Account> accVec;

    while (true) {
        switch (startInterface()) {
            case 1:
                registrationInterface(accVec);
                break;
            case 2:
                loginInterface(accVec);
                break;
            case 3:
                return 0;
            case 4:
                fetchAllAccounts(accVec);
        }
    }
}
