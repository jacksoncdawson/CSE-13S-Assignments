#include "hangman_helpers.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_lowercase_letter(char c) {
    return c >= 'a' && c <= 'z';
}

char read_letter(void) {
    char c;
    printf("Guess a letter: ");
    scanf(" %c", &c);
    return c;
}

bool validate_secret(const char *secret) {

    if (strlen(secret) > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters\n");
        return false;
    }

    for (size_t i = 0; i < strlen(secret); i++) {
        if (!is_lowercase_letter(secret[i]) && secret[i] != ' ' && secret[i] != '-'
            && secret[i] != '\'') {
            printf("invalid character: '%c'\n", secret[i]);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    for (size_t i = 0; i < strlen(s); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

// Test functions
void test_is_lowercase_letter(void) {
    assert(is_lowercase_letter('a') == true);
    assert(is_lowercase_letter('z') == true);
    assert(is_lowercase_letter('A') == false);
    assert(is_lowercase_letter(' ') == false);
    printf("is_lowercase_letter tests passed.\n");
}

void test_validate_secret(void) {
    assert(validate_secret("test") == true);
    assert(validate_secret("test-with-hyphen") == true);
    assert(validate_secret("Test With Upper") == false);
    assert(validate_secret("test_with_invalid_char!") == false);
    assert(validate_secret(
               "this-is-a-very-long-secret-that-exceeds-the-maximum-allowed-length-"
               "aaaaaaaaaaaaaaababababababbabababababababbabababababababababababababababaababababab"
               "ababababababababbababababababbabaabbababababababababababababbababababbababababbabab"
               "abababbababababbababbababababababaababababbabababbababababbababababababababababa")
           == false);
    printf("validate_secret tests passed.\n");
}

void test_string_contains_character(void) {
    assert(string_contains_character("hello", 'e') == true);
    assert(string_contains_character("world", 'a') == false);
    assert(string_contains_character("", 'a') == false);
    printf("string_contains_character tests passed.\n");
}

int main(void) {
    test_is_lowercase_letter();
    test_validate_secret();
    test_string_contains_character();

    printf("All tests passed.\n");
    return 0;
}
