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

    shared_ptr<uint16_t> result;

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
            result = bitwise_add(a_val, b_val);
            return result;
            break;
        default:
            break;
    }

    result = make_shared<uint16_t>(value_stack.top());
    return result;
}

shared_ptr<uint16_t> rpn_calculator::bitwise_add(shared_ptr<uint16_t> a_val, shared_ptr<uint16_t> b_val) {
    // work with copies in case operation overflows and we need to revert the stack
    uint16_t _a = *a_val;
    uint16_t _b = *b_val;
    bool overflow = false;

    // XOR (^) _a and _b will add them with no carry, while AND (&) _a and _b, then left shifting 1 bit will result in the carry.
    // Assign the results of the XOR back to _a and the AND back to _b, then repeat the process until _b(the carry) equals zero.
    // _a will contain the final result.
    while (_b != 0) {
        uint16_t no_carry = _a ^ _b;
        uint16_t carry = (_a & _b) << 1;
        _a = no_carry;
        _b = carry;
    }

    // check for overflow(of unsigned int) by seeing if the result is less then the original operands.
    if (_a > *a_val && _a > *b_val) {
        value_stack.push(_a);
        shared_ptr<uint16_t> result = make_shared<uint16_t>(value_stack.top());
        return result;
    }
    value_stack.push(*b_val);
    value_stack.push(*a_val);
    return nullptr;
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