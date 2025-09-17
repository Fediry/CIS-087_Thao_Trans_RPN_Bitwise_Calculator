#include "main.h"

#include "rpn-calculator.h"
#include "tests.h"

using namespace std;

enum command : uint16_t {
    cmd_enter = 0,
    cmd_clear,
    cmd_pop,
    cmd_top,
    cmd_left_shift,
    cmd_right_shift,
    cmd_or,
    cmd_and,
    cmd_add,
};
vector<string> command_name = {"cmd_enter", "cmd_clear",      "cmd_pop",
                               "cmd_top",   "cmd_left_shift", "cmd_right_shift",
                               "cmd_or",    "cmd_and",        "cmd_add"};
uint8_t const width = 16U;

shared_ptr<uint16_t> command_clear(stack<uint16_t> &v_stack) {
    while (!v_stack.empty()) {
        v_stack.pop();
    }

    return nullptr;
}

shared_ptr<uint16_t> command_enter(stack<uint16_t> &v_stack, uint16_t value) {
    v_stack.push(value);
    uint16_t val = v_stack.top();
    shared_ptr<uint16_t> result = make_shared<uint16_t>(val);
    return result;
}

/*
 * *** STUDENTS SHOULD WRITE CODE FOR THIS FUNCTION ***
 * Students should create or add any data structures needed.
 * Students should create or add any functions or classes they may need.
 */
shared_ptr<uint16_t> rpn_calc(command const cmd, uint16_t const value = 0) {
    stack<uint16_t> value_stack;
    // initialize the stack... might not be needed once other functions are in
    // place.
    value_stack.push(0U);
    shared_ptr<uint16_t> result = nullptr;

    switch (cmd) {
        case cmd_enter:
            result = command_enter(value_stack, value);
            return result;
            break;
        case cmd_clear:
            result = command_clear(value_stack);
            break;
        default:
            break;
    }

    // this is example code which returns a (smart shared) pointer to 16-bit
    // value
    // uint16_t val = 0b1001100100000011;
    // shared_ptr<uint16_t> result = make_shared<uint16_t>(val);
    return result;
}

int main() {
    if (!test()) {
        return -1;
    }
    return 0;
}