#include <iostream>
#include <string>
#include "Account.h"

std::string Account::getLogin() {
    return _login;
}

int Account::getAccNum() {
    return _accNum;
}

float Account::getBalance() {
    return _balance;
}

void Account::withdraw(float withdrawAmount) {
    if (withdrawAmount > getBalance()) {
        std::cout << "Not enough money to withdraw!" << std::endl;
        std::cout << "You can withdraw only " << getBalance() << std::endl;
    } else {
        std::cout << "You withdrawn " << withdrawAmount << "$" << std::endl;
        _balance -= withdrawAmount;
        std::cout << "Now you have " << getBalance() << " on your account" << std::endl;
    }
}

void Account::deposit(float amount) {
    std::cout << "You deposit " << amount << " $ " << "to your account" << std::endl;
    _balance += amount;
    std::cout << "Now you have " << getBalance() << " on your account" << std::endl;
}

void Account::showInfo() {
    std::cout << "Your login : " << _login << std::endl;
    std::cout << "Your account number : " << _accNum << std::endl;
    std::cout << "Your current balance : " << getBalance() << std::endl;
}

Account::Account(const std::string &login, int accNum, float balance)
    : _login(login), _accNum(accNum), _balance(balance) {
}

Account::Account(const std::string &login, int accNum) : _login(login), _accNum(accNum), _balance(0) {
}
