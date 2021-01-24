#ifndef __BANK_HPP__
#define __BANK_HPP__

#include <functional>
#include <map>
#include <stdexcept>

#include "Account.hpp"

class Bank {
private:
    std::map<size_t, Account> accounts;

public:
    /**
     * @brief Add a new Account
     * (Only move constructor)
     * @param account
     */
    void AddAccount(Account&& account);

    /**
     * @brief Withdraw amount from type from the account with cardNumber
     *
     * @param cardNumber Cardnumber to get account from
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE_SAVING or
     * Account::TYPE_CHECKING)
     * @param amount amount to with draw
     * @throws invalid_argument
     */
    void Withdraw(
      std::string cardNumber,
      std::string pin,
      Account::TYPE type,
      long long amount);

    /**
     * @brief Deposit amount to type in the account with cardNumber
     *
     * @param cardNumber Cardnumber to get account from
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE_SAVING or
     * Account::TYPE_CHECKING)
     * @param amount amount to with draw
     * @throws invalid_argument
     */
    void Deposit(
      std::string cardNumber,
      std::string pin,
      Account::TYPE type,
      long long amount);

    /**
     * @brief Get Balance of type of account with cardNumber
     *
     * @param cardNumber Cardnumber to get account from
     * @param pin Card Pin
     * @param type of account (can be either Account::TYPE::TYPE_SAVING
     * or Account::TYPE::TYPE_CHECKING)
     * @return long long balance in the account
     * @throws invalid_argument if Pin is incorrect
     */
    long long
    GetBalance(std::string cardNumber, std::string pin, Account::TYPE type);

    /**
     * @brief Allows to check if the pin is valid for the account with
     * cardNumber
     *
     * @param cardNumber Cardnumber to get account from
     * @param pin 6 digits long pin
     * @return true if pin matches with the accounts pin
     * @return false otherwise
     */
    bool CheckPin(std::string cardNumber, std::string pin);
};

#endif