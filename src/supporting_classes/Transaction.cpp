#include "ATMController/supporting_classes/Transaction.hpp"

/*************************/
/*************************/

Transaction::Transaction(long long amount) : amount(amount), at(std::time(0)) {
    if (amount == 0) {
        throw std::invalid_argument("Transaction cannot be of amount \'0\'");
    }
}

/*************************/
/*************************/

Transaction::Transaction(long long amount, std::time_t at)
    : amount(amount), at(at) {}
