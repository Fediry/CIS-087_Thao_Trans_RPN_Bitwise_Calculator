#pragma once

#include "main.h"
#include "rpn-calculator.h"

using namespace std;

class tests {
   public:
    tests() : {}
    // using rule of zero

    void header();
    void print_row(bool const test_success, command const cmd,
                   int16_t const value, shared_ptr<uint_t> top_of_stack);
}