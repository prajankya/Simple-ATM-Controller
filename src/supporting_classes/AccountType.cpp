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

void AccountType::AddTransaction(const Transaction& transaction) {
    Validate();

    // Test Limits
    if (transaction.amount > 0 && balance > 0) {
        if (balance > LLONG_MAX - transaction.amount) {
            // max limit
            throw std::invalid_argument("Account reached maximum limit !");
        }
    }  // no need for other three cases, as it will reduce the size of number

    // If balance does not go below zero
    if (balance + transaction.amount >= 0) {
        transactions.emplace_back(transaction.amount);
        Validate();
        return;
    } else {
        // Not enough balance
        throw std::invalid_argument(
          "Account does not have sufficient balance !");
    }
}