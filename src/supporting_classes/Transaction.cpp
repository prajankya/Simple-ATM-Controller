#include "ATMController/supporting_classes/Transaction.hpp"

Transaction::Transaction(long long&& amount, const std::time_t&& at)
    : amount(std::move(amount)), at(std::move(at)) {}
