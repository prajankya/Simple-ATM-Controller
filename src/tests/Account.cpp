
#include "gtest/gtest.h"

#include "ATMController/supporting_classes/Account.hpp"

TEST(Account, InitializeValid) {
    EXPECT_NO_THROW(Account("123456789012", "123456"));
};

TEST(Account, InValidPinSizeLess) {
    EXPECT_ANY_THROW(Account("123456789012", "12345"));
};

TEST(Account, InValidPinSizeMore) {
    EXPECT_ANY_THROW(Account("123456789012", "1234567"));
};

TEST(Account, PinAllZero) {
    EXPECT_NO_THROW(Account("123456789012", "000000"));
};

TEST(Account, PinAllLeadingZeros) {
    EXPECT_NO_THROW(Account("123456789012", "000001"));
};

TEST(Account, NegativePin) {
    EXPECT_ANY_THROW(Account("123456789012", "-12345"));
};

TEST(Account, InValidCardSizeLess) {
    EXPECT_ANY_THROW(Account("12345678901", "123456"));
};

TEST(Account, InValidCardSizeMore) {
    EXPECT_ANY_THROW(Account("1234567890123", "123456"));
};

TEST(Account, NoCardNumber) {
    EXPECT_ANY_THROW(Account("", "123456"));
};

TEST(Account, ZeroBalance) {
    EXPECT_NO_THROW(Account("123456789012", "123456", 0, 0));
};

TEST(Account, NegativeSavings) {
    EXPECT_ANY_THROW(Account("123456789012", "123456", -1, 0));
};

TEST(Account, NegativeCheckings) {
    EXPECT_ANY_THROW(Account("123456789012", "123456", 0, -1));
};

TEST(Account, PositiveSavings) {
    EXPECT_NO_THROW(Account("123456789012", "123456", 100, 200));
};

TEST(Account, CheckCorrectPin) {
    Account ac("123456789012", "123456", 1, 2);

    EXPECT_TRUE(ac.CheckPin("123456"));
};

TEST(Account, CheckWrongPin) {
    Account ac("123456789012", "123456", 1, 2);

    EXPECT_FALSE(ac.CheckPin("112233"));
};

TEST(Account, WithdrawSaving) {
    Account ac("123456789012", "123456", 100, 2);

    EXPECT_TRUE(ac.Withdraw("123456", Account::TYPE::TYPE_SAVING, 100));
};

TEST(Account, WithdrawSavingInvalid) {
    Account ac("123456789012", "123456", 100, 2);

    EXPECT_FALSE(ac.Withdraw("123456", Account::TYPE::TYPE_SAVING, 101));
};

TEST(Account, WithdrawSavingNegative) {
    Account ac("123456789012", "123456", 100, 2);

    EXPECT_ANY_THROW(ac.Withdraw("123456", Account::TYPE::TYPE_SAVING, -10));
};

TEST(Account, WithdrawSavingMultiple) {
    Account ac("123456789012", "123456", 100, 2);

    EXPECT_TRUE(ac.Withdraw("123456", Account::TYPE::TYPE_SAVING, 50));
    EXPECT_TRUE(ac.Withdraw("123456", Account::TYPE::TYPE_SAVING, 50));
    EXPECT_FALSE(ac.Withdraw("123456", Account::TYPE::TYPE_SAVING, 1));
};

TEST(Account, WithdrawChecking) {
    Account ac("123456789012", "123456", 1, 100);

    EXPECT_TRUE(ac.Withdraw("123456", Account::TYPE::TYPE_CHECKING, 100));
};

TEST(Account, WithdrawCheckingInvalid) {
    Account ac("123456789012", "123456", 1, 100);

    EXPECT_FALSE(ac.Withdraw("123456", Account::TYPE::TYPE_CHECKING, 101));
};

TEST(Account, WithdrawCheckingNegative) {
    Account ac("123456789012", "123456", 1, 100);

    EXPECT_ANY_THROW(ac.Withdraw("123456", Account::TYPE::TYPE_CHECKING, -10));
};

TEST(Account, WithdrawCheckingMultiple) {
    Account ac("123456789012", "123456", 1, 100);

    EXPECT_TRUE(ac.Withdraw("123456", Account::TYPE::TYPE_CHECKING, 50));
    EXPECT_TRUE(ac.Withdraw("123456", Account::TYPE::TYPE_CHECKING, 50));
    EXPECT_FALSE(ac.Withdraw("123456", Account::TYPE::TYPE_CHECKING, 1));
};

TEST(Account, DepositSaving) {
    Account ac("123456789012", "123456", 100, 2);

    EXPECT_TRUE(ac.Deposit("123456", Account::TYPE::TYPE_SAVING, 100));
};

TEST(Account, DepositSavingInvalid) {
    Account ac("123456789012", "123456", LLONG_MAX, 2);

    EXPECT_FALSE(ac.Deposit("123456", Account::TYPE::TYPE_SAVING, 1));
};

TEST(Account, DepositSavingNegative) {
    Account ac("123456789012", "123456", 100, 2);

    EXPECT_ANY_THROW(ac.Deposit("123456", Account::TYPE::TYPE_SAVING, -10));
};

TEST(Account, DepositChecking) {
    Account ac("123456789012", "123456", 1, 100);

    EXPECT_TRUE(ac.Deposit("123456", Account::TYPE::TYPE_CHECKING, 100));
};

TEST(Account, DepositCheckingInvalid) {
    Account ac("123456789012", "123456", 1, LLONG_MAX);

    EXPECT_FALSE(ac.Deposit("123456", Account::TYPE::TYPE_CHECKING, 1));
};

TEST(Account, DepositCheckingNegative) {
    Account ac("123456789012", "123456", 1, 100);

    EXPECT_ANY_THROW(ac.Deposit("123456", Account::TYPE::TYPE_CHECKING, -10));
};
