
#include "gtest/gtest.h"

#include "ATMController.hpp"
#include "supporting_classes/Account.hpp"
#include "supporting_classes/Bank.hpp"

TEST(ATMController, ConnectBank) {
    Bank bank;

    bank.AddAccount(Account("123456789012", "123456", 10, 20));

    ATMController atm(&bank);
};