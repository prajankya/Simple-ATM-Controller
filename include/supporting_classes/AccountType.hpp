#ifndef __ACCOUNTTYPE_HPP__
#define __ACCOUNTTYPE_HPP__

#include <limits.h>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Transaction.hpp"

/**
 * @brief AccountType
 *
 * An small container for account, with specific type.
 * like Checkings or Savings
 *
 */
class AccountType {
private:
    void Validate();

protected:
    long long balance = 0;
    std::vector<Transaction> transactions;

public:
    /**
     * @brief Construct a new Account Type object
     *
     * @param deposit initial Amount
     */
    AccountType(long long deposit);

    /**
     * @brief Construct a new Account Type object
     *
     * No Initial Deposit, totals to zero
     */
    AccountType();

    // No copy
    AccountType(const AccountType&) = delete;

    // Move constructor
    AccountType(AccountType&&) = default;

    // Move assignment
    AccountType& operator=(AccountType&&) = default;

    /**
     * @brief Get the Balance of this account type
     *
     * @return long long Balance
     */
    long long GetBalance();

    /**
     * @brief Add Transaction
     *
     * @param transaction to add
     * @throws invalid_argument exception false if account does not have
     * sufficient balance or total is more than size of long long int
     */
    void AddTransaction(const Transaction& transaction);
};

#endif