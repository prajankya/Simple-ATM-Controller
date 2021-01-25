
#include "gtest/gtest.h"

#include "ATMController.hpp"
#include "supporting_classes/Account.hpp"
#include "supporting_classes/Bank.hpp"

TEST(ATMController, ConnectBank) {
    Bank bank;

    bank.AddAccount(Account("123456789012", "123456", 10, 20));

    EXPECT_NO_THROW(ATMController atm(&bank));
};

TEST(ATMController, GetState) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 10, 20));

    ATMController atm(&bank);

    EXPECT_EQ(atm.GetState(), ATMController::STATE::NO_CARD_INSERTED);
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

TEST(ATMController, SelectAccountValid) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");

    EXPECT_NO_THROW(atm1.SelectAccount(Account::TYPE::TYPE_SAVING));
};

TEST(ATMController, SelectAccountChangeType) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");

    EXPECT_NO_THROW(atm1.SelectAccount(Account::TYPE::TYPE_SAVING));

    // Cannot Change account type later
    EXPECT_ANY_THROW(atm1.SelectAccount(Account::TYPE::TYPE_CHECKING));
    // Cannot Change account type later
    EXPECT_ANY_THROW(atm1.SelectAccount(Account::TYPE::TYPE_SAVING));
};
TEST(ATMController, SelectAccountValidChecking) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");

    EXPECT_NO_THROW(atm1.SelectAccount(Account::TYPE::TYPE_CHECKING));
};

TEST(ATMController, SelectAccountCheckSTATE) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::PIN_TESTED);
    EXPECT_NO_THROW(atm1.SelectAccount(Account::TYPE::TYPE_CHECKING));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);

    // throws error if in wrong state
    EXPECT_ANY_THROW(atm1.SelectAccount(Account::TYPE::TYPE_SAVING));
};

TEST(ATMController, GetBalance) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");
    atm1.SelectAccount(Account::TYPE::TYPE_CHECKING);

    EXPECT_EQ(atm1.GetBalance(), 20);
};

TEST(ATMController, GetBalanceCheckSTATE) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");
    atm1.SelectAccount(Account::TYPE::TYPE_SAVING);

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_EQ(atm1.GetBalance(), 100);
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
};

TEST(ATMController, Withdraw) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 100, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");
    atm1.SelectAccount(Account::TYPE::TYPE_SAVING);

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_NO_THROW(atm1.Withdraw(100));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);

    EXPECT_ANY_THROW(atm1.Withdraw(1));
};

TEST(ATMController, Deposit) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 0, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");
    atm1.SelectAccount(Account::TYPE::TYPE_SAVING);

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_NO_THROW(atm1.Deposit(LLONG_MAX));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);

    EXPECT_ANY_THROW(atm1.Deposit(1));
};

TEST(ATMController, Eject) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 0, 20));

    ATMController atm1(&bank);
    atm1.InsertCard("123456789012");
    atm1.EnterPin("123456");
    atm1.SelectAccount(Account::TYPE::TYPE_SAVING);

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_NO_THROW(atm1.EjectCard());
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::NO_CARD_INSERTED);

    EXPECT_ANY_THROW(atm1.EjectCard());
};

TEST(ATMController, StateToString) {
    Bank bank;
    ATMController atm1(&bank);

    EXPECT_EQ(
      atm1.StateToString(ATMController::STATE::NO_CARD_INSERTED),
      "NO_CARD_INSERTED");

    EXPECT_EQ(
      atm1.StateToString(ATMController::STATE::CARD_INSERTED), "CARD_INSERTED");

    EXPECT_EQ(
      atm1.StateToString(ATMController::STATE::PIN_TESTED), "PIN_TESTED");

    EXPECT_EQ(
      atm1.StateToString(ATMController::STATE::ACCOUNT_READY), "ACCOUNT_READY");
};

TEST(ATMController, Flow) {
    Bank bank;
    bank.AddAccount(Account("123456789012", "123456", 123, 20));

    ATMController atm1(&bank);
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::NO_CARD_INSERTED);
    EXPECT_EQ(atm1.StateToString(atm1.GetState()), "NO_CARD_INSERTED");

    EXPECT_NO_THROW(atm1.InsertCard("123456789012"));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::CARD_INSERTED);
    EXPECT_EQ(atm1.StateToString(atm1.GetState()), "CARD_INSERTED");

    EXPECT_NO_THROW(atm1.EnterPin("123456"));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::PIN_TESTED);
    EXPECT_EQ(atm1.StateToString(atm1.GetState()), "PIN_TESTED");

    EXPECT_NO_THROW(atm1.SelectAccount(Account::TYPE::TYPE_SAVING));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_EQ(atm1.StateToString(atm1.GetState()), "ACCOUNT_READY");

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_NO_THROW(atm1.Deposit(100));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_EQ(atm1.GetBalance(), 223);
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);

    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_NO_THROW(atm1.Withdraw(210));
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);
    EXPECT_EQ(atm1.GetBalance(), 13);
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::ACCOUNT_READY);

    EXPECT_NO_THROW(atm1.EjectCard());
    EXPECT_EQ(atm1.GetState(), ATMController::STATE::NO_CARD_INSERTED);
    EXPECT_EQ(atm1.StateToString(atm1.GetState()), "NO_CARD_INSERTED");
};
