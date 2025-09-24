#ifndef BANKSYSTEM_ACCOUNT_H
#define BANKSYSTEM_ACCOUNT_H


class Account {
private:
    std::string _login;
    int _accNum;
    float _balance = 0;

public:
    std::string getLogin();

    int getAccNum();

    float getBalance();

    void withdraw(float withdrawAmount);

    void deposit(float amount);

    void showInfo();

    Account(const std::string &login, int accNum, float balance);

    Account(const std::string &login, int accNum);
};


#endif //BANKSYSTEM_ACCOUNT_H
