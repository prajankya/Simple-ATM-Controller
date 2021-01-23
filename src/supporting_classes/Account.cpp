#include "ATMController/supporting_classes/Account.hpp"

/*************************/
/*************************/

Account::Account(
  const std::string& cardNumber,
  std::string pin,
  long long saving,
  long long checking)
    : cardNumber(cardNumber), saving(saving), checking(checking) {
    // Basic validate Card number
    if (cardNumber.length() != 12) {
        throw std::invalid_argument("Card number should be 12 digits long");
    }

    // all characters are numbers
    if (!std::regex_match(cardNumber, std::regex("[0-9]+"))) {
        throw std::invalid_argument(
          "Card number should contain only valid digits");
    }

    if (pin.length() != 6) {
        throw std::invalid_argument("Pin should be 6 digits long");
    }

    // all characters are numbers
    if (!std::regex_match(pin, std::regex("[0-9]+"))) {
        throw std::invalid_argument("Pin should contain only valid digits");
    }

    // TODO: Using basic hash for simplicity sake
    pin_hash = std::hash<std::string>{}(pin);
}

/*************************/
/*************************/

bool Account::CheckPin(std::string pin) {
    return std::hash<std::string>{}(pin) == pin_hash;
}

/*************************/
/*************************/

bool Account::Withdraw(std::string pin, Account::TYPE type, long long amount) {
    if (!CheckPin(pin)) {
        throw std::invalid_argument("Invalid Pin!");
    }

    if (amount < 0) {
        throw std::invalid_argument("Cannot withdraw negative amount!");
    } else if (amount == 0) {
        throw std::invalid_argument("Cannot withdraw zero amount!");
    }

    // Convert to negative, to withdraw
    amount = -amount;

    if (type == TYPE::TYPE_CHECKING) {
        return checking.AddTransaction(Transaction(amount));
    } else if (type == TYPE::TYPE_SAVING) {
        return saving.AddTransaction(Transaction(amount));
    } else {
        throw std::invalid_argument("Invalid Account Type!");
    }
}

/*************************/
/*************************/

bool Account::Deposit(std::string pin, Account::TYPE type, long long amount) {
    if (!CheckPin(pin)) {
        throw std::invalid_argument("Invalid Pin!");
    }

    if (amount < 0) {
        throw std::invalid_argument("Cannot Deposit negative amount!");
    } else if (amount == 0) {
        throw std::invalid_argument("Cannot Deposit zero amount!");
    }

    if (type == TYPE::TYPE_CHECKING) {
        return checking.AddTransaction(Transaction(amount));
    } else if (type == TYPE::TYPE_SAVING) {
        return saving.AddTransaction(Transaction(amount));
    } else {
        throw std::invalid_argument("Invalid Account Type!");
    }
}

/*************************/
/*************************/

long long Account::GetBalance(std::string pin, Account::TYPE type) {
    if (!CheckPin(pin)) {
        throw std::invalid_argument("Invalid Pin!");
    }

    if (type == TYPE::TYPE_CHECKING) {
        return checking.GetBalance();
    } else if (type == TYPE::TYPE_SAVING) {
        return saving.GetBalance();
    } else {
        throw std::invalid_argument("Invalid Account Type!");
    }
}