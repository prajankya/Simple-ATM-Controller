#ifndef __ACCOUNT_TYPE_HPP__
#define __ACCOUNT_TYPE_HPP__

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

    // No assignment
    AccountType& operator=(const AccountType&) = delete;

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
     * @return true if Transaction was successful
     * @return false if not enough balance
     */
    bool AddTransaction(const Transaction& transaction);
};

#endif