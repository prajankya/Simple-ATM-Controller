
#include "gtest/gtest.h"

#include "ATMController/supporting_classes/Account.hpp"

TEST(Account, InitializeValid) {
    EXPECT_NO_THROW(Account("11", 123456));
};

TEST(Account, InValidPinSizeLess) {
    EXPECT_ANY_THROW(Account("11", 12345));
};

TEST(Account, InValidPinSizeMore) {
    EXPECT_ANY_THROW(Account("11", 1234567));
};