#ifndef __ATM_CONTROLLER_HPP__
#define __ATM_CONTROLLER_HPP__

#include "supporting_classes/Bank.hpp"

class ATMController {
public:
    ATMController(const Bank* bank);

private:
    // Ownership is outside ATMController
    const Bank* bankptr;
};
#endif