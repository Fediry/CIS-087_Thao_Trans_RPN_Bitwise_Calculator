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

shared_ptr<uint16_t> rpn_calculator::command_bw_operation(bw_op op) {
    if (value_stack.size() < 2) {
        return nullptr;
    }

    shared_ptr<uint16_t> a_val = make_shared<uint16_t>(value_stack.top());
    value_stack.pop();
    shared_ptr<uint16_t> b_val = make_shared<uint16_t>(value_stack.top());
    value_stack.pop();
    switch (op) {
        case left_shift:
            value_stack.push(*b_val << *a_val);
            break;
        case right_shift:
            value_stack.push(*b_val >> *a_val);
            break;
        case bw_or:
            value_stack.push(*b_val | *a_val);
            break;
        case bw_and:
            value_stack.push(*b_val & *a_val);
            break;
        case bw_add:
            bitwise_add(a_val, b_val);
            break;
        default:
            break;
    }

    shared_ptr<uint16_t> result = command_top();
    return result;
}

shared_ptr<uint16_t> rpn_calculator::bitwise_add(shared_ptr<uint16_t> a_val, shared_ptr<uint16_t> b_val) {
    // save current values in case operation fails
    uint16_t save_a_val = *a_val;
    uint16_t save_b_val = *b_val;
}

shared_ptr<uint16_t> rpn_calculator::rpn_calc(command const cmd, uint16_t const value = 0) {
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
            result = command_bw_operation(left_shift);
            return result;
            break;
        case cmd_right_shift:
            result = command_bw_operation(right_shift);
            return result;
            break;
        case cmd_or:
            result = command_bw_operation(bw_or);
            return result;
            break;
        case cmd_and:
            result = command_bw_operation(bw_and);
            return result;
            break;
        case cmd_add:
            result = command_bw_operation(bw_add);
            return result;
            break;
        default:
            return result;
    }
}