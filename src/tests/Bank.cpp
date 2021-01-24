
#include "gtest/gtest.h"

#include "ATMController/supporting_classes/Account.hpp"
#include "ATMController/supporting_classes/Bank.hpp"

TEST(Bank, AddAccount) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));
};

TEST(Bank, AddSameAccount) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456")));
    // Add account with same card number again
    EXPECT_ANY_THROW(bank.AddAccount(Account("123456789012", "123456")));
};

TEST(Bank, AddInvalidAccount) {
    Bank bank;

    EXPECT_ANY_THROW(bank.AddAccount(Account("123456789012", "")));
};

TEST(Bank, Withdraw) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));

    EXPECT_NO_THROW(
      bank.Withdraw("123456789012", "123456", Account::TYPE::TYPE_SAVING, 10));
};

TEST(Bank, InvalidWithdraw) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));

    EXPECT_ANY_THROW(
      bank.Withdraw("123456789012", "123456", Account::TYPE::TYPE_SAVING, 11));
};

TEST(Bank, WithdrawFromUnknownAccount) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));

    EXPECT_ANY_THROW(
      bank.Withdraw("123456789013", "123456", Account::TYPE::TYPE_SAVING, 10));
};

TEST(Bank, Deposit) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));

    EXPECT_NO_THROW(
      bank.Deposit("123456789012", "123456", Account::TYPE::TYPE_SAVING, 10));
};

TEST(Bank, DepositToUnknownAccount) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));

    EXPECT_ANY_THROW(
      bank.Deposit("123456789013", "123456", Account::TYPE::TYPE_SAVING, 10));
};

TEST(Bank, CheckBalance) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));

    EXPECT_EQ(
      bank.GetBalance("123456789012", "123456", Account::TYPE::TYPE_SAVING),
      10);

    EXPECT_EQ(
      bank.GetBalance("123456789012", "123456", Account::TYPE::TYPE_CHECKING),
      20);
};

TEST(Bank, CheckPin) {
    Bank bank;

    EXPECT_NO_THROW(bank.AddAccount(Account("123456789012", "123456", 10, 20)));

    EXPECT_TRUE(bank.CheckPin("123456789012", "123456"));
    EXPECT_FALSE(bank.CheckPin("123456789012", "122334"));
};