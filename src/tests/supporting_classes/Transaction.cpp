
#include <ctime>

#include "gtest/gtest.h"

#include "ATMController/supporting_classes/Transaction.hpp"

TEST(Transaction, CreateNewTransaction) {
    Transaction t(10, std::time(0));

    EXPECT_EQ(t.amount, 10);
};

TEST(Transaction, EmptyTransaction) {
    EXPECT_ANY_THROW(Transaction(0));
};
