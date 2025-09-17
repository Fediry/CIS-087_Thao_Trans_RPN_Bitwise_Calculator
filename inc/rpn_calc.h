#pragma once

#include "main.h"

using namespace std;

class rpn_calculator {
   public:
    rpn_calculator() {}
    // using the rule of zero

    stack<uint16_t> value_stack;
    shared_ptr<uint16_t> command_clear(stack<uint16_t> &v_stack);
    shared_ptr<uint16_t> command_enter(stack<uint16_t> &v_stack,
                                       uint16_t value);
    shared_ptr<uint16_t> rpn_calc(command const cmd, uint16_t const value);
};