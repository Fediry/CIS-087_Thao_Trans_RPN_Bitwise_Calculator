#pragma once

#include "main.h"
#include "rpn_calc.h"

using namespace std;

// test harness structs and params
#define VALUE_NULLPTR -999
uint8_t const width = 16U;
uint8_t const table_width[] = {14, 18, 14, 18, 14, 18};

class tests {
   private:
    rpn_calculator calc;
    vector<string> command_name = {
        "cmd_enter",       "cmd_clear", "cmd_pop", "cmd_top", "cmd_left_shift",
        "cmd_right_shift", "cmd_or",    "cmd_and", "cmd_add"};

   public:
    tests() : calc() {}
    // using rule of zero

    void header();
    void print_row(bool const test_success, command const cmd,
                   int16_t const value, shared_ptr<uint16_t> top_of_stack);
    vector<string> split(string const &s, string const &delimiter);
    void init_command_map(unordered_map<string, command> &command_map);
    bool parse_csv_line(string const line,
                        unordered_map<string, command> command_map,
                        command &input_cmd, uint16_t &input_value,
                        int32_t &answer_value);
    bool test();
};