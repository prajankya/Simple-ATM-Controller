#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#include <math.h>
#include <ctime>
#include <functional>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "AccountType.hpp"

class Account {
public:
    const std::string cardNumber;

private:
    std::size_t pin_hash;

    AccountType saving;
    AccountType checking;

public:
    enum class TYPE { TYPE_SAVING, TYPE_CHECKING };

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
     * @param saving initial balance for saving account(defaults to 0)
     * @param checking initial balance for checking account(defaults to 0)
     */
    Account(
      const std::string& cardNumber,
      std::string pin,
      long long saving = 0,
      long long checking = 0);

    /**
     * @brief Construct a new Account
     * (Move Constructor)
     */
    Account(Account&& other) = default;

    /**
     * @brief Withdraw amount from type of account
     *
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE_SAVING or
     * Account::TYPE_CHECKING)
     * @param amount amount to with draw
     * @throws invalid_argument if Pin is incorrect or if account does not have
     * sufficient balance
     */
    void Withdraw(std::string pin, Account::TYPE type, long long amount);

    /**
     * @brief Deposit amount to type of account
     *
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE_SAVING or
     * Account::TYPE_CHECKING)
     * @param amount amount to with draw
     * @throws invalid_argument if Pin is incorrect or total is more than size
     * of long long int
     */
    void Deposit(std::string pin, Account::TYPE type, long long amount);

    /**
     * @brief Get Balance of the given type of account
     *
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE::TYPE_SAVING
     * or Account::TYPE::TYPE_CHECKING)
     * @return long long balance in the account
     * @throws invalid_argument if Pin is incorrect
     */
    long long GetBalance(std::string pin, Account::TYPE type);

    /**
     * @brief Allows to check if the pin is valid for the current account
     *
     * @param pin 6 digits long pin
     * @return true if pin matches with the accounts pin
     * @return false otherwise
     */
    bool CheckPin(std::string pin);
};

#endif