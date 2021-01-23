
#include <ctime>

#include "gtest/gtest.h"

#include "ATMController/supporting_classes/AccountType.hpp"

TEST(AccountType, InitialDeposit) {
    EXPECT_NO_THROW(AccountType(11));
};

TEST(AccountType, NegativeInitialDeposit) {
    EXPECT_ANY_THROW(AccountType(-10));
};

TEST(AccountType, GetBalance) {
    AccountType actype(10);

    EXPECT_EQ(actype.GetBalance(), 10);
};

TEST(AccountType, NOInitialDeposit) {
    AccountType actype;
    EXPECT_EQ(actype.GetBalance(), 0);
};

TEST(AccountType, ZeroInitialDeposit) {
    AccountType actype(0);
    EXPECT_EQ(actype.GetBalance(), 0);
};

TEST(AccountType, CreditTransaction) {
    AccountType actype(123);

    EXPECT_TRUE(actype.AddTransaction(Transaction(234)));

    EXPECT_EQ(actype.GetBalance(), 357);
}

TEST(AccountType, DebitTransaction) {
    AccountType actype(123);

    EXPECT_TRUE(actype.AddTransaction(Transaction(-100)));

    EXPECT_EQ(actype.GetBalance(), 23);
}

TEST(AccountType, MixedTransaction) {
    AccountType actype(123);

    EXPECT_TRUE(actype.AddTransaction(Transaction(234)));

    EXPECT_EQ(actype.GetBalance(), 357);

    EXPECT_FALSE(actype.AddTransaction(Transaction(-500)));

    EXPECT_TRUE(actype.AddTransaction(Transaction(-300)));
    EXPECT_EQ(actype.GetBalance(), 57);

    EXPECT_TRUE(actype.AddTransaction(Transaction(-57)));
    EXPECT_EQ(actype.GetBalance(), 0);
}

TEST(AccountType, MAXLimit) {
    AccountType actype(LLONG_MAX);

    EXPECT_FALSE(actype.AddTransaction(Transaction(1)));
}

// // Cannot do anything to detect this, as eventually its a valid value
// TEST(AccountType, MINLimit_overflow) {
//     EXPECT_NO_THROW(AccountType(LLONG_MIN - 1));
// }