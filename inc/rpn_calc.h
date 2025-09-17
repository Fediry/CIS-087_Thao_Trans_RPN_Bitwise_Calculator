#pragma once

#include "main.h"

using namespace std;

class rpn_calculator {
   private:
    stack<uint16_t> value_stack;
    shared_ptr<uint16_t> a_val;
    shared_ptr<uint16_t> b_val;
    shared_ptr<uint16_t> op_result;

   public:
    rpn_calculator() {}
    // using the rule of zero

    shared_ptr<uint16_t> command_enter(uint16_t value);
    shared_ptr<uint16_t> command_clear();
    shared_ptr<uint16_t> command_pop();
    shared_ptr<uint16_t> command_top();
    shared_ptr<uint16_t> command_left_shift();
    shared_ptr<uint16_t> command_right_shift();
    shared_ptr<uint16_t> rpn_calc(command const cmd, uint16_t const value);
};