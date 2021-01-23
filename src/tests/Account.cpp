
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

TEST(Account, CheckPinCorrect) {
    Account ac("123456789012", "123456", 1, 2);

    EXPECT_TRUE(ac.CheckPin("123456"));
};

TEST(Account, CheckPinWrong) {
    Account ac("123456789012", "123456", 1, 2);

    EXPECT_FALSE(ac.CheckPin("112233"));
};
