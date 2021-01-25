#ifndef __ATM_CONTROLLER_HPP__
#define __ATM_CONTROLLER_HPP__

#include <stdexcept>

#include "supporting_classes/Bank.hpp"

class ATMController {
public:
    /**
     * @brief STATE of the ATM Controller
     *
     * NO_CARD_INSERTED +--> CARD_INSERTED +--> PIN_TESTED +--> ACCOUNT_READY
     */
    enum class STATE {
        NO_CARD_INSERTED,
        CARD_INSERTED,
        PIN_TESTED,
        ACCOUNT_READY
    };

    /**
     * @brief Construct a new ATMController object
     *
     * @param bank Pointer to an existing Bank object(external ownership)
     */
    ATMController(Bank* bank);

    /**
     * @brief Insert Card
     *
     * @param cardNumber 12 digit Card number
     *
     * Must be in NO_CARD_INSERTED state when calling this function
     */
    void InsertCard(std::string cardNumber);

    /**
     * @brief Entering the pin for the given card (using InsertCard(cardNumber))
     *
     * @param pin 6 digit pin for the card
     *
     * Must be in CARD_INSERTED state when calling this function
     */
    void EnterPin(std::string pin);

    /**
     * @brief Choose a type of account
     *
     * @param type of account (between Account::TYPE::TYPE_SAVING and
     * Account::TYPE::TYPE_CHECKING)
     *
     * Must be in PIN_TESTED state when calling this function
     */
    void SelectAccount(Account::TYPE type);

    /**
     * @brief Get the Balance of the current account
     *
     * @return long long balance
     *
     * Must be in ACCOUNT_READY state when calling this function
     */
    long long GetBalance();

    /**
     * @brief Withdraw amount from the current account
     *
     * @param amount to be withdrawn
     *
     * Must be in ACCOUNT_READY state when calling this function
     */
    void Withdraw(long long amount);

    /**
     * @brief Deposit amount to the current account
     *
     * @param amount to be deposited
     *
     * Must be in ACCOUNT_READY state when calling this function
     */
    void Deposit(long long amount);

    /**
     * @brief Ejecting the current card
     *
     * Can be in any state except NO_CARD_INSERTED when calling this function
     */
    void EjectCard();

    /**
     * @brief Get the Current State of ATMController
     *
     * @return ATMController::STATE
     */
    ATMController::STATE GetState();

    /**
     * @brief Get a String representation of given state
     *
     * @param state
     * @return const std::string
     */
    const std::string StateToString(ATMController::STATE state) const;

private:
    // Ownership is outside ATMController
    Bank* bank_ptr;

    std::string current_cardNumber;
    std::string current_cardPin;
    Account::TYPE current_accountType;

    ATMController::STATE current_state;
};
#endif