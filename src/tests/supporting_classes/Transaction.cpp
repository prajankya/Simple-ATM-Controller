
#include <ctime>

#include "gtest/gtest.h"

#include "ATMController/supporting_classes/Transaction.hpp"

TEST(Transaction, CreateNewTransaction) {
    Transaction(0, std::time(0));

    EXPECT_TRUE(true);
};
