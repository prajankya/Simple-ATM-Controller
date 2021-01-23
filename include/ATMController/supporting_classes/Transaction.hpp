#ifndef __TRANSACTION_HPP__
#define __TRANSACTION_HPP__

#include <ctime>
#include <stdexcept>
#include <string>

/**
 * @brief Transaction
 *
 */

struct Transaction {
    const long long amount;
    const std::time_t at;

    /**
     * @brief Create a new Transaction
     *
     * @param amount of Transaction
     * "at" time will default to current time
     */
    Transaction(long long amount);

    /**
     * @brief Create a new Transaction
     *
     * @param amount of the Transaction
     * @param at time of the Transaction
     */
    Transaction(long long amount, std::time_t at);

    // move constructor should be available, default is fine
    Transaction(Transaction&&) = default;

    Transaction() = delete;

    // cannot copy a transaction
    Transaction(const Transaction&) = delete;

    // no assignment
    Transaction& operator=(const Transaction&) = delete;
};

#endif