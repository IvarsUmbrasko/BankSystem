#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>
#include "Account.h"


int startInterface() {
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

void loggedInInterface(Account &acc) {
    int choice = 0;

    do {
        std::cout << "----Logged in " << acc.getLogin() << "------------" << std::endl;
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
                acc.deposit(amount);
                break;
            case 2:
                std::cout << "Write amount of $ what you want to withdraw : ";
                std::cin >> amount;
                acc.withdraw(amount);
                break;
            case 3:
                acc.showInfo();
                break;
        }
    } while (choice != 4);
}

int checkAccountExistence(const std::string &login, int accNum, std::vector<Account> &accVec) {
    for (int i = 0; i < accVec.size(); ++i) {
        if (login == accVec[i].getLogin() && accNum == accVec[i].getAccNum()) {
            return i;
        }
    }
    return -1;
}

void fetchAllAccounts(std::vector<Account> &accVec) {
    std::string text;
    std::string login;
    int accNum{0};
    float balance{0};
    std::ifstream OutputFile("../BankSystem/login.txt");
    int lineCnt{0};

    while (getline(OutputFile, text)) {
        if (text.empty()) {
            lineCnt = 0;
            continue;
        }

        lineCnt++;

        if (lineCnt == 1) {
            login = text;
        } else if (lineCnt == 2) {
            accNum = std::stoi(text);
        } else if (lineCnt == 3) {
            balance = std::stof(text);
            accVec.push_back(Account(login, accNum, balance));
        }
    }
}

void saveAllAccountsInFile(std::vector<Account> &accVec) {
    std::ofstream InputFile("../BankSystem/login.txt", std::ofstream::out | std::ofstream::trunc);
    for (int i = 0; i < accVec.size(); ++i) {
        InputFile << accVec[i].getLogin() << "\n";
        InputFile << accVec[i].getAccNum() << "\n";
        InputFile << accVec[i].getBalance() << "\n";
        InputFile << "\n";
    }
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

    if (checkAccountExistence(login, accNum, accVec) == -1) {
        std::cout << "Enter amount : ";
        float balance;
        std::cin >> balance;
        Account acc(login, accNum, balance);
        accVec.push_back(acc);
        std::cout << "New account was created successfully" << std::endl;
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
    std::cout << "---------------------------------------" << std::endl;

    Account acc(login, accNum);

    int check = checkAccountExistence(login, accNum, accVec);
    if (check >= 0) {
        loggedInInterface(accVec[check]);
    } else {
        std::cout << "Account doesn't exists" << std::endl;
    }
}

void showVec(std::vector<Account> &accVec) {
    for (int i =0; i< accVec.size(); ++i) {
        std::cout << accVec[i].getLogin() << std::endl;
        std::cout << accVec[i].getAccNum() << std::endl;
        std::cout << accVec[i].getBalance() << std::endl;
    }
}

int main() {
    std::vector<Account> accVec;
    fetchAllAccounts(accVec);
    while (true) {
        switch (startInterface()) {
            case 1:
                registrationInterface(accVec);
                break;
            case 2:
                loginInterface(accVec);
                break;
            case 3:
                saveAllAccountsInFile(accVec);
                return 0;
            case 4:
                showVec(accVec);
                break;
        }
    }
}
