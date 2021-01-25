#include "supporting_classes/Bank.hpp"

/*************************/
/*************************/

void Bank::AddAccount(Account&& account) {
    if (
      accounts.find(std::hash<std::string>{}(account.cardNumber)) ==
      accounts.end()) {
        accounts.emplace(std::make_pair(
          std::hash<std::string>{}(account.cardNumber), std::move(account)));
    } else {
        throw std::invalid_argument(
          "Account with given card number already exists!");
    }
}

/*************************/
/*************************/

void Bank::Withdraw(
  std::string cardNumber,
  std::string pin,
  Account::TYPE type,
  long long amount) {
    auto ac = accounts.find(std::hash<std::string>{}(cardNumber));
    if (ac != accounts.end()) {
        return ac->second.Withdraw(pin, type, amount);
    } else {
        throw std::invalid_argument(
          "Account with given card number does not exist !");
    }
}

/*************************/
/*************************/

void Bank::Deposit(
  std::string cardNumber,
  std::string pin,
  Account::TYPE type,
  long long amount) {
    auto ac = accounts.find(std::hash<std::string>{}(cardNumber));
    if (ac != accounts.end()) {
        return ac->second.Deposit(pin, type, amount);
    } else {
        throw std::invalid_argument(
          "Account with given card number does not exist !");
    }
}

/*************************/
/*************************/

long long
Bank::GetBalance(std::string cardNumber, std::string pin, Account::TYPE type) {
    auto ac = accounts.find(std::hash<std::string>{}(cardNumber));
    if (ac != accounts.end()) {
        return ac->second.GetBalance(pin, type);
    } else {
        throw std::invalid_argument(
          "Account with given card number does not exist !");
    }
}

/*************************/
/*************************/

bool Bank::CheckPin(std::string cardNumber, std::string pin) {
    auto ac = accounts.find(std::hash<std::string>{}(cardNumber));
    if (ac != accounts.end()) {
        return ac->second.CheckPin(pin);
    } else {
        throw std::invalid_argument(
          "Account with given card number does not exist !");
    }
}