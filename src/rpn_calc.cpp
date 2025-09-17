#include "rpn_calc.h"

shared_ptr<uint16_t> rpn_calculator::command_clear(stack<uint16_t> &v_stack) {
    while (!v_stack.empty()) {
        v_stack.pop();
    }

    return nullptr;
}

shared_ptr<uint16_t> rpn_calculator::command_enter(stack<uint16_t> &v_stack,
                                                   uint16_t value) {
    v_stack.push(value);
    uint16_t val = v_stack.top();
    shared_ptr<uint16_t> result = make_shared<uint16_t>(val);
    return result;
}

shared_ptr<uint16_t> rpn_calculator::rpn_calc(command const cmd,
                                              uint16_t const value = 0) {
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