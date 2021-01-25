
#include "gtest/gtest.h"

#include "ATMController.hpp"
#include "supporting_classes/Account.hpp"
#include "supporting_classes/Bank.hpp"

TEST(ATMController, ConnectBank) {
    Bank bank;

    bank.AddAccount(Account("123456789012", "123456", 10, 20));

    EXPECT_NO_THROW(ATMController atm(&bank));
};

TEST(ATMController, InsertCardNoAccount) {
    Bank bank;
    ATMController atm1(&bank);

    EXPECT_ANY_THROW(atm1.InsertCard("123456789012"));
};

TEST(ATMController, InsertCardValidAccount) {
    Bank bank;

    ATMController atm1(&bank);

    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    EXPECT_NO_THROW(atm1.InsertCard("123456789012"));
};

TEST(ATMController, InsertCardInvalidCardNumber) {
    Bank bank;

    ATMController atm1(&bank);

    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    // Invalid length
    EXPECT_ANY_THROW(atm1.InsertCard("123456789"));

    // Invalid character
    EXPECT_ANY_THROW(atm1.InsertCard("12345678901A"));
};

TEST(ATMController, InsertCardMultipleAccounts) {
    Bank bank;

    ATMController atm1(&bank);

    bank.AddAccount(Account("123456789012", "123456", 100, 20));
    bank.AddAccount(Account("123456789123", "123444", 200, 43));

    EXPECT_NO_THROW(atm1.InsertCard("123456789012"));
};

TEST(ATMController, InsertCardCheckSTATE) {
    Bank bank;

    ATMController atm1(&bank);

    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::NO_CARD_INSERTED);
    EXPECT_NO_THROW(atm1.InsertCard("123456789012"));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::CARD_INSERTED);

    // throws error if inserting while one card_inserted
    EXPECT_ANY_THROW(atm1.InsertCard("123456789012"));
};

TEST(ATMController, EnterPinValid) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");

    EXPECT_NO_THROW(atm1.EnterPin("123456"));
};

TEST(ATMController, EnterPinWrongPin) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");

    // Wrong Pin
    EXPECT_ANY_THROW(atm1.EnterPin("123455"));
};

TEST(ATMController, EnterPinInvalidPin) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");

    // Invalid Pin
    EXPECT_ANY_THROW(atm1.EnterPin("123ABC"));
};

TEST(ATMController, EnterPinCheckSTATE) {
    Bank bank;

    ATMController atm1(&bank);

    bank.AddAccount(Account("123456789012", "123456", 100, 20));
    atm1.InsertCard("123456789012");

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::CARD_INSERTED);
    EXPECT_NO_THROW(atm1.EnterPin("123456"));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::PIN_TESTED);

    // throws error if in wrong state
    EXPECT_ANY_THROW(atm1.EnterPin("123456"));
};