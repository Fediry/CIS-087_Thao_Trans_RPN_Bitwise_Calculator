#pragma once

#include "main.h"

using namespace std;

enum bw_op : uint16_t { left_shift = 0, right_shift, bw_or, bw_and, bw_add };

class rpn_calculator {
   private:
    stack<uint16_t> value_stack;

   public:
    rpn_calculator() {}
    // using the rule of zero

    shared_ptr<uint16_t> command_enter(uint16_t value);
    shared_ptr<uint16_t> command_clear();
    shared_ptr<uint16_t> command_pop();
    shared_ptr<uint16_t> command_top();
    shared_ptr<uint16_t> command_bw_operation(bw_op op);
    shared_ptr<uint16_t> bitwise_add(shared_ptr<uint16_t> a_val, shared_ptr<uint16_t> b_val);
    shared_ptr<uint16_t> rpn_calc(command const cmd, uint16_t const value);
};