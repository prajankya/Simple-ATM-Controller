#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#include <math.h>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>

#include "AccountType.hpp"

class Account {
private:
    const std::string cardNumber;
    unsigned long pin;

    AccountType saving;
    AccountType checking;

public:
    enum class ACCOUNT_TYPE { TYPE_SAVING, TYPE_CHECKING };

    // Empty constructor
    Account() = delete;

    // No copy
    Account(const Account&) = delete;

    // No assignment
    Account& operator=(const Account&) = delete;

    /**
     * @brief Create a new Account
     *
     * @param cardNumber
     * @param pin for card
     * defaults saving balance to 0
     * defaults checking balance to 0
     */
    Account(const std::string cardNumber, unsigned long pin);

    /**
     * @brief Create a new Account
     *
     * @param cardNumber
     * @param pin for card
     * @param saving is the initial balance set for saving account
     * @param checking is the initial balance set for checking account
     */
    Account(
      const std::string cardNumber,
      unsigned long pin,
      long long saving,
      long long checking);

    /**
     * @brief Withdraw from given @param amount
     *
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE_SAVING or
     * Account::TYPE_CHECKING)
     * @param amount amount to with draw
     * @return true if the withdraw is successful
     * @return false if not enough balance
     * @throws invalid_argument if Pin is incorrect
     */
    bool Withdraw(unsigned long pin, enum ACCOUNT_TYPE type, long long amount);

    /**
     * @brief Deposit from given @param amount
     *
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE_SAVING or
     * Account::TYPE_CHECKING)
     * @param amount amount to with draw
     * @return true if the deposit is successful
     * @return false if not enough balance
     * @throws invalid_argument if Pin is incorrect
     */
    bool Deposit(unsigned long pin, enum ACCOUNT_TYPE type, long long amount);

    /**
     * @brief Get Balance of the given type of account
     *
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE_SAVING or
     * Account::TYPE_CHECKING)
     * @return long long balance in the account
     * @throws invalid_argument if Pin is incorrect
     */
    long long Balance(unsigned long pin, enum ACCOUNT_TYPE type);
};

#endif