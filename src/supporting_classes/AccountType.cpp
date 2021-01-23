#include "ATMController/supporting_classes/AccountType.hpp"

/*************************/
/*************************/

AccountType::AccountType(long long deposit) {
    if (deposit < 0) {
        throw std::invalid_argument("Deposit can only be >= 0");
    } else if (deposit == 0) {
        balance = 0;
    } else {
        // Add Initial deposit as a credit transaction
        transactions.emplace_back(deposit);

        Validate();
    }
}

/*************************/
/*************************/

AccountType::AccountType() : balance(0) {}

/*************************/
/*************************/

void AccountType::Validate() {
    long long amount = 0;
    for (int i = 0; i < transactions.size(); i++) {
        amount += transactions[i].amount;
    }

    balance = amount;
}

/*************************/
/*************************/

long long AccountType::GetBalance() {
    Validate();
    return balance;
}

/*************************/
/*************************/

bool AccountType::AddTransaction(const Transaction& transaction) {
    Validate();

    // If balance does not go below zero
    if (balance + transaction.amount >= 0) {
        transactions.emplace_back(transaction.amount);
        Validate();
        return true;
    } else {
        // Not enough balance
        return false;
    }
}