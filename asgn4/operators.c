#include "operators.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

double operator_add(double lhs, double rhs) {
    return lhs + rhs;
}

double operator_sub(double lhs, double rhs) {
    return lhs - rhs;
}

double operator_mul(double lhs, double rhs) {
    return lhs * rhs;
}

double operator_div(double lhs, double rhs) {
    return lhs / rhs;
}

double operator_mod(double lhs, double rhs) {
    return fmod(lhs, rhs);
}

bool apply_binary_operator(binary_operator_fn op) {
    double rhs, lhs, temp;
    if (!stack_pop(&temp)) {
        return false;
    }
    if (!stack_pop(&lhs)) {
        stack_push(temp);
        return false;
    }
    rhs = temp;
    stack_push(op(lhs, rhs));
    return true;
}

bool apply_unary_operator(unary_operator_fn op) {
    double operand;
    if (!stack_pop(&operand)) {
        return false;
    }
    stack_push(op(operand));
    return true;
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
