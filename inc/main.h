#pragma once

#include <stdint.h>

#include <bitset>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define INPUT_CSV_FILE "../rpn-input.csv"

// test controls
#define MIN_VALUE 0
#define MAX_VALUE 100

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
