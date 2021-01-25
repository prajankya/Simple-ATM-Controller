#include "ATMController.hpp"

/*************************/
/*************************/

ATMController::ATMController(Bank* bank_)
    : bank_ptr(bank_),
      current_state(STATE::NO_CARD_INSERTED),
      current_cardNumber(""),
      current_cardPin("") {}

/*************************/
/*************************/

void ATMController::InsertCard(std::string cardNumber) {
    // STATE check
    if (current_state != STATE::NO_CARD_INSERTED) {
        throw std::invalid_argument(
          "WRONG STATE! " + StateToString(current_state));
    }

    // Validate card number
    if (cardNumber.length() != 12) {
        throw std::invalid_argument("Card number should be 12 digits long");
    }

    // all characters are numbers
    if (!std::regex_match(cardNumber, std::regex("[0-9]+"))) {
        throw std::invalid_argument(
          "Card number should contain only valid digits");
    }

    if (bank_ptr->CheckAccount(cardNumber)) {
        // Going to Next State
        current_cardNumber = cardNumber;
        current_state = STATE::CARD_INSERTED;
    } else {
        throw std::invalid_argument(
          "The provided Card Number cannot be validated with any account known "
          "to "
          "the Bank");
    }
}

/*************************/
/*************************/

void ATMController::EnterPin(std::string pin) {
    // STATE check
    if (current_state != STATE::CARD_INSERTED) {
        throw std::invalid_argument(
          "WRONG STATE! " + StateToString(current_state));
    }

    // Validate Pin
    if (pin.length() != 6) {
        throw std::invalid_argument("Pin should be 6 digits long");
    }

    // all characters are numbers
    if (!std::regex_match(pin, std::regex("[0-9]+"))) {
        throw std::invalid_argument("Pin should contain only valid digits");
    }

    if (bank_ptr->CheckPin(current_cardNumber, pin)) {
        // Going to Next State
        current_cardPin = pin;
        current_state = STATE::PIN_TESTED;
    } else {
        throw std::invalid_argument("The provided Pin is incorrect");
    }
}

/*************************/
/*************************/

void ATMController::SelectAccount(Account::TYPE type) {
    // STATE check
    if (current_state != STATE::PIN_TESTED) {
        throw std::invalid_argument(
          "WRONG STATE! " + StateToString(current_state));
    }

    current_accountType = type;
    current_state = STATE::ACCOUNT_READY;
}

/*************************/
/*************************/

long long ATMController::GetBalance() {
    // STATE check
    if (current_state != STATE::ACCOUNT_READY) {
        throw std::invalid_argument(
          "WRONG STATE! " + StateToString(current_state));
    }
    return bank_ptr->GetBalance(
      current_cardNumber, current_cardPin, current_accountType);
}

/*************************/
/*************************/

void ATMController::Withdraw(long long amount) {
    // STATE check
    if (current_state != STATE::ACCOUNT_READY) {
        throw std::invalid_argument(
          "WRONG STATE! " + StateToString(current_state));
    }

    bank_ptr->Withdraw(
      current_cardNumber, current_cardPin, current_accountType, amount);
}

/*************************/
/*************************/

void ATMController::Deposit(long long amount) {
    // STATE check
    if (current_state != STATE::ACCOUNT_READY) {
        throw std::invalid_argument(
          "WRONG STATE! " + StateToString(current_state));
    }

    bank_ptr->Deposit(
      current_cardNumber, current_cardPin, current_accountType, amount);
}

/*************************/
/*************************/

void ATMController::EjectCard() {
    // STATE check
    if (current_state == STATE::NO_CARD_INSERTED) {
        throw std::invalid_argument("No card Inserted !");
    }
    current_cardNumber = "";
    current_cardPin = "";
    current_state = STATE::NO_CARD_INSERTED;
}

/*************************/
/*************************/

ATMController::STATE ATMController::GetState() {
    return current_state;
}

/*************************/
/*************************/

const std::string ATMController::StateToString(
  ATMController::STATE state) const {
    switch (state) {
    case STATE::NO_CARD_INSERTED:
        return "NO_CARD_INSERTED";
    case STATE::CARD_INSERTED:
        return "CARD_INSERTED";
    case STATE::PIN_TESTED:
        return "PIN_TESTED";
    case STATE::ACCOUNT_READY:
        return "ACCOUNT_READY";
    default:
        return "UNKNOWN_STATE";
    }
}