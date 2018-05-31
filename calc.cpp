#include "calc.h"

using namespace std;

Operation::Operation() : type(Operation::empty_t), num(0), parantheses(0), op(0), next(-1){}

QString calculate_wrapper(const string& s) {
    try {
        return QString::number(calculate(s.c_str(), s.size()));
    } catch (int ex) {
        return "Ошибка в " + QString::number(ex) + " символе.";
    }
}

double calculate(const char* s, unsigned int len) {
    char* tokens = split_by_tokens(s, len);
    vector<Operation> ops = tokens_to_operations(tokens);
    delete[] tokens;
    double num = evaluate_operations(ops);
    return num;
}


char* split_by_tokens(const char* s, unsigned int len) {
    const char* s_end = s + len;
    char* tokens = new char[len * 12];
    char* edi = tokens;
    const char* esi = s;

    for (unsigned int z = 0; z < len * 12; ++z) {
        tokens[z] = 0;
    }

    while (esi < s_end) {
        double num = 0;
        bool neg = false;

        if (*esi == '-') {
            esi += 1;
            neg = true;
        }
        if (*esi == 0) {
            throw (int)(esi - s);
        }
        if (*esi == '+') {
            esi += 1;
            continue;
        }
        if (*esi == '(') {
            esi += 1;
            *edi = neg ? minus_opening_braket_token : opening_braket_token;
            edi += 1;
            continue;
        }
        // esi = number
        if ((unsigned char)(*esi - '0') > 9) // esi contains not digit
            throw (int)(esi - s);
        char* end_ptr;
        num = strtod(esi, &end_ptr);
        esi = end_ptr;
        *edi = num_token;
        edi += 1;
        *(double*)(edi) = num;
        edi += sizeof(double);
        while (*esi == ')') {
            *edi = closing_braket_token;
            edi += 1;
            esi += 1;
        }
        if (*esi == '(') {
            *edi = op_token;
            edi += 1;
            *edi = '*';
            edi += 1;
            *edi = opening_braket_token;
            edi += 1;
            esi += 1;
            continue;
        }
        if (*esi == 0)
            break;
        if (*esi == '+' or *esi == '-' or *esi == '*' or *esi == '/') {
            *edi = op_token;
            edi += 1;
            *edi = *esi;
            edi += 1;
            esi += 1;
        } else {
            throw (int)(esi - s);
        }
    }
    return tokens;
}


vector<Operation> tokens_to_operations(const char* tokens) {
    vector<Operation> ops;
    ops.emplace_back();
    stack<int> parantheses_nesting;
    int cur = 0;

    while(*tokens != 0) {
        if (*tokens == num_token) {
            tokens += 1;
            double num = *(double*)(tokens);
            tokens += sizeof(double);
            ops[cur].type = Operation::number_t;
            ops[cur].num = num;
        } else if (*tokens == op_token) {
            tokens += 1;
            ops[cur].op = *tokens;
            tokens += 1;
            ops.emplace_back();
            ops[cur].next = ops.size() - 1;
            cur = ops.size() - 1;
        } else if (*tokens == opening_braket_token or *tokens == minus_opening_braket_token ) {
            ops[cur].type = (*tokens == opening_braket_token) ? Operation::parantheses_t : Operation::minus_parantheses_t;
            tokens += 1;
            ops.emplace_back();
            ops[cur].parantheses = ops.size() - 1;
            parantheses_nesting.push(cur);
            cur = ops.size() - 1;
        } else if (*tokens == closing_braket_token) {
            tokens += 1;
            cur = parantheses_nesting.top();
            parantheses_nesting.pop();
        }
    }
    return ops;
}

double evaluate_operations(vector<Operation>& ops) {
    while(true) {
        vector<int> maybe_simple_exprs = {0};
        for(auto z = ops.begin(); z != ops.end(); ++z) {
            if (z->type == Operation::parantheses_t or z->type == Operation::minus_parantheses_t) {
                maybe_simple_exprs.push_back(z - ops.begin());
            }
        }
        vector<int> simple_exprs;
        for(auto z = maybe_simple_exprs.begin(); z < maybe_simple_exprs.end(); ++z) {
            int x = ops[*z].parantheses;
            while(true) {
                if (ops[x].type == Operation::parantheses_t or ops[x].type == Operation::minus_parantheses_t)
                    break;
                if (ops[x].next == -1) {
                    simple_exprs.push_back(*z);
                    break;
                }
                x = ops[x].next;
            }
        }
        for(auto z = simple_exprs.begin(); z < simple_exprs.end(); ++z) {
            int x = ops[*z].parantheses;
            while(ops[x].next != -1) {
                if (ops[x].op == '*' or ops[x].op == '/') {
                    if (ops[x].op == '*')
                        ops[x].num *= ops[ops[x].next].num;
                    if (ops[x].op == '/')
                        ops[x].num /= ops[ops[x].next].num;
                    ops[x].op = ops[ops[x].next].op;
                    ops[x].next = ops[ops[x].next].next;
                } else {
                    x = ops[x].next;
                }
            }
            x = ops[*z].parantheses;
            while(ops[x].next != -1) {
                if (ops[x].op == '+')
                    ops[x].num += ops[ops[x].next].num;
                if (ops[x].op == '-')
                    ops[x].num -= ops[ops[x].next].num;
                ops[x].op = ops[ops[x].next].op;
                ops[x].next = ops[ops[x].next].next;
            }
            ops[*z].num = ops[x].num;
            if (ops[*z].type == Operation::minus_parantheses_t)
                ops[*z].num = -ops[*z].num;
            ops[*z].type = Operation::number_t;
            ops[*z].parantheses = -1;
        }
        if (ops[0].next == -1)
            break;
    }
    return ops[0].num;
}
