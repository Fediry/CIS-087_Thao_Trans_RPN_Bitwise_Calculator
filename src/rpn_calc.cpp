#include "rpn_calc.h"

shared_ptr<uint16_t> rpn_calculator::command_enter(uint16_t value) {
    value_stack.push(value);
    shared_ptr<uint16_t> result = make_shared<uint16_t>(value_stack.top());
    return result;
}

shared_ptr<uint16_t> rpn_calculator::command_clear() {
    while (!value_stack.empty()) {
        value_stack.pop();
    }

    return nullptr;
}

shared_ptr<uint16_t> rpn_calculator::command_pop() {
    if (value_stack.empty()) {
        return nullptr;
    }
    value_stack.pop();

    // recheck stack size before trying to return pointer
    if (value_stack.empty()) {
        return nullptr;
    } else {
        shared_ptr<uint16_t> result = make_shared<uint16_t>(value_stack.top());
        return result;
    }
}

shared_ptr<uint16_t> rpn_calculator::command_top() {
    if (value_stack.empty()) {
        return nullptr;
    }

    shared_ptr<uint16_t> result = make_shared<uint16_t>(value_stack.top());
    return result;
}

shared_ptr<uint16_t> rpn_calculator::command_bw_operation(char const op) {
    if (value_stack.size() < 2) {
        return nullptr;
    }

    a_val = make_shared<uint16_t>(value_stack.top());
    value_stack.pop();
    b_val = make_shared<uint16_t>(value_stack.top());
    value_stack.pop();
    switch (op) {
        case '<':
            value_stack.push(*b_val << *a_val);
            break;
        case '>':
            value_stack.push(*b_val >> *a_val);
            break;
        case '|':
            value_stack.push(*b_val | *a_val);
            break;
        case '&':
            value_stack.push(*b_val & *a_val);
            break;
        default:
            break;
    }

    shared_ptr<uint16_t> result = command_top();
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
        case cmd_left_shift:
            result = command_bw_operation('<');
            return result;
            break;
        case cmd_right_shift:
            result = command_bw_operation('>');
            return result;
            break;
        case cmd_or:
            result = command_bw_operation('|');
            return result;
            break;
        case cmd_and:
            result = command_bw_operation('&');
            return result;
            break;
        default:
            return result;
    }
}