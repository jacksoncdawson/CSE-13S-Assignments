#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int isNumber(const char *str);
void parseCommandLineOptions(int argc, char *argv[], int *use_libm);
void promptForInput(void);
void processCalculations(char *input, int use_libm);
void handleNumber(char *token, int *errFlag);
void handleBinaryOperator(char token, int *errFlag);
void handleUnaryOperator(char token, int use_libm, int *errFlag);
void handleErrors(char *token, int *errFlag);

void testIsNumber(void);
void testProcessCalculations(void);

int main(int argc, char *argv[]) {
    int use_libm = 0;
    parseCommandLineOptions(argc, argv, &use_libm);

    testIsNumber();
    testProcessCalculations();

    return 0;
}

// TESTS HERE

void testIsNumber(void) {
    printf("Testing isNumber...\n");
    printf("Expect 1, %d\n", isNumber("123.456"));
    printf("Expect 0: %d\n", isNumber("abc"));
    printf("Expect 0: %d\n", isNumber("123abc"));
    printf("Expect 1: %d\n", isNumber("-123.456"));
    printf("Expect 0: %d\n", isNumber(""));
    printf("Expect 0: %d\n", isNumber(" "));
}

void testProcessCalculations(void) {
    printf("Testing processCalculations with use_libm=0...\n");
    char input1[] = "12 3 +";
    processCalculations(input1, 0);

    printf("Testing processCalculations with use_libm=1...\n");
    char input2[] = "12 3 +";
    processCalculations(input2, 1);
}

// TESTED FUNCTIONS HERE

int isNumber(const char *str) {
    char *end;
    if (str[0] == '\0' || isspace((unsigned char) str[0])) {
        return 0;
    }
    strtod(str, &end);
    return *end == '\0';
}

void parseCommandLineOptions(int argc, char *argv[], int *use_libm) {
    int opt;
    while ((opt = getopt(argc, argv, "mh")) != -1) {
        switch (opt) {
        case 'h': printf(USAGE, argv[0]); exit(0);
        case 'm': *use_libm = 1; break;
        default: fprintf(stderr, USAGE, argv[0]); exit(1);
        }
    }
}

void promptForInput(void) {
    fprintf(stderr, "> ");
}

void processCalculations(char *input, int use_libm) {
    char *token = strtok(input, " ");
    int errFlag = 0;
    while (token != NULL && errFlag == 0) {
        if (isNumber(token)) {
            handleNumber(token, &errFlag);
        } else if (strchr("+-*/%", token[0]) != NULL) {
            handleBinaryOperator(token[0], &errFlag);
        } else if (strchr("sctar", token[0]) != NULL) {
            handleUnaryOperator(token[0], use_libm, &errFlag);
        } else {
            handleErrors(token, &errFlag);
        }
        token = strtok(NULL, " ");
    }
    if (errFlag == 0) {
        stack_print();
        printf("\n");
    }
    stack_clear();
}

void handleNumber(char *token, int *errFlag) {
    double num = strtod(token, NULL);
    if (stack_size == STACK_CAPACITY) {
        fprintf(stderr, ERROR_NO_SPACE, num);
        *errFlag = 1;
        return;
    }
    stack_push(num);
}

void handleBinaryOperator(char token, int *errFlag) {
    binary_operator_fn op = NULL;
    switch (token) {
    case '+': op = operator_add; break;
    case '-': op = operator_sub; break;
    case '*': op = operator_mul; break;
    case '/': op = operator_div; break;
    case '%': op = operator_mod; break;
    }
    if (!apply_binary_operator(op)) {
        fprintf(stderr, ERROR_BINARY_OPERATOR);
        *errFlag = 1;
    }
}

void handleUnaryOperator(char token, int use_libm, int *errFlag) {
    unary_operator_fn op = NULL;
    if (use_libm) {
        switch (token) {
        case 's': op = sin; break;
        case 'c': op = cos; break;
        case 't': op = tan; break;
        case 'a': op = fabs; break;
        case 'r': op = sqrt; break;
        }
    } else {
        switch (token) {
        case 's': op = Sin; break;
        case 'c': op = Cos; break;
        case 't': op = Tan; break;
        case 'a': op = Abs; break;
        case 'r': op = Sqrt; break;
        }
    }
    if (!apply_unary_operator(op)) {
        fprintf(stderr, ERROR_UNARY_OPERATOR);
        *errFlag = 1;
    }
}

void handleErrors(char *token, int *errFlag) {
    *errFlag = 1;
    strlen(token) == 1 ? fprintf(stderr, ERROR_BAD_CHAR, token[0])
                       : fprintf(stderr, ERROR_BAD_STRING, token);
}
