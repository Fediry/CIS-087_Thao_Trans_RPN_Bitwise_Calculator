#include "rpn_calc.h"

shared_ptr<uint16_t> rpn_calculator::command_pop() {
    if (value_stack.empty()) {
        return nullptr;
    }

    value_stack.pop();
    shared_ptr<uint16_t> result = make_shared<uint16_t>(value_stack.top());
    return result;
}

shared_ptr<uint16_t> rpn_calculator::command_top() {
    if (value_stack.empty()) {
        return nullptr;
    }

    shared_ptr<uint16_t> result = make_shared<uint16_t>(value_stack.top());
    return result;
}

shared_ptr<uint16_t> rpn_calculator::command_clear() {
    while (!value_stack.empty()) {
        value_stack.pop();
    }

    return nullptr;
}

shared_ptr<uint16_t> rpn_calculator::command_enter(uint16_t value) {
    value_stack.push(value);
    uint16_t val = value_stack.top();
    shared_ptr<uint16_t> result = make_shared<uint16_t>(val);
    return result;
}

shared_ptr<uint16_t> rpn_calculator::rpn_calc(command const cmd, uint16_t const value = 0) {
    // initialize the stack... might not be needed once other functions are in
    // place.
    // value_stack.push(0U);
    shared_ptr<uint16_t> result = nullptr;

    switch (cmd) {
        case cmd_enter:
            result = command_enter(value);
            return result;
            break;
        case cmd_clear:
            result = command_clear();
            return result;
            break;
        case cmd_pop:
            result = command_pop();
            return result;
            break;
        case cmd_top:
            result = command_top();
            return result;
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