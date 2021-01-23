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