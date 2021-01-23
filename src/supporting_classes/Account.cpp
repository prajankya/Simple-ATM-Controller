#include "ATMController/supporting_classes/Account.hpp"

/*************************/
/*************************/

Account::Account(const std::string cardNumber, unsigned long pin)
    : cardNumber(cardNumber), pin(pin) {
    // TODO: check cardNumber if valid

    // validate pin
    if (floor(log10(pin) + 1) != 6) {
        throw std::invalid_argument("Pin should be 6 digits long");
    }
}