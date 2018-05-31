#ifndef CALC_H
#define CALC_H
#include <iostream>
#include <QString>
#include <utility>
#include <tuple>
#include <cstdlib>
#include <stack>
#include <vector>


#define num_token 1
#define op_token 2
#define opening_braket_token 3
#define closing_braket_token 4
#define minus_opening_braket_token 5

struct Operation {
    enum types {
        empty_t,
        number_t,
        parantheses_t,
        minus_parantheses_t
    } type;
    double num;
    int parantheses;
    char op;
    int next;


    Operation();
};

QString calculate_wrapper(const std::string& s);

double calculate(const char* s, unsigned int len);
char* split_by_tokens(const char* s, unsigned int len);
std::vector<Operation> tokens_to_operations(const char* tokens);
double evaluate_operations(std::vector<Operation>& ops);

#endif // CALC_H
