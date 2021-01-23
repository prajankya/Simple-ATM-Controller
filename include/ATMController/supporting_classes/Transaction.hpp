#ifndef __TRANSACTION_HPP__
#define __TRANSACTION_HPP__

#include <ctime>
#include <string>

/**
 * @brief Transaction
 *
 */

class Transaction {
private:
    const long long amount;
    const std::time_t at;

public:
    /**
     * @brief Create a new Transaction
     *
     * @param amount of the Transaction
     * @param at time of the Trasaction
     */
    Transaction(long long&& amount, const std::time_t&& at);

    // cannot copy a transaction
    Transaction(const Transaction&&) = delete;

    // no assignment
    // Transaction& operator=(const Transaction&) = delete;
};

#endif