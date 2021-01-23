
#include <ctime>

#include "gtest/gtest.h"

#include "ATMController/supporting_classes/AccountType.hpp"

TEST(AccountType, CreateNewAccountType) {
    AccountType actype(10);

    EXPECT_EQ(actype.GetBalance(), 10);
};

TEST(AccountType, NegativeInitialDeposit) {
    EXPECT_ANY_THROW(AccountType actype(-10));
};

TEST(AccountType, InitialDeposit) {
    EXPECT_NO_THROW(AccountType actype(11));
};

TEST(AccountType, NOInitialDeposit) {
    AccountType actype;
    EXPECT_EQ(actype.GetBalance(), 0);
};

TEST(AccountType, ZeroInitialDeposit) {
    AccountType actype(0);
    EXPECT_EQ(actype.GetBalance(), 0);
};

TEST(AccountType, TestAddTransaction) {
    AccountType actype(123);

    EXPECT_TRUE(actype.AddTransaction(Transaction(234)));

    EXPECT_EQ(actype.GetBalance(), 357);

    EXPECT_FALSE(actype.AddTransaction(Transaction(-500)));

    EXPECT_TRUE(actype.AddTransaction(Transaction(-300)));
    EXPECT_EQ(actype.GetBalance(), 57);

    EXPECT_TRUE(actype.AddTransaction(Transaction(-57)));
    EXPECT_EQ(actype.GetBalance(), 0);
}

TEST(AccountType, TestValidate) {
    AccountType actype(0);
    auto balance = actype.GetBalance();

    EXPECT_EQ(balance, 0);

    EXPECT_EQ(balance, 0);
};
