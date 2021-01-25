#include <iostream>
#include "ATMController.hpp"
#include "supporting_classes/Account.hpp"

int main() {
    Bank bank;

    // Add a new account with $1000 in savings and $10 in checkings
    bank.AddAccount(Account("123456789012", "123456", 1000, 10));

    // Making sure bank is owned by main, and not transfered to ATM1
    ATMController atm1(&bank);

    return 0;
}