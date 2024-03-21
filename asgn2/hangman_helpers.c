#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    return c >= 'a' && c <= 'z';
}

char read_letter(void) {
    printf("Guess a letter: ");
    char c;
    scanf(" %c", &c);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
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

bool isWinner(const char *secret, const char *guess) {
    if (strcmp(secret, guess) == 0) {
        return true;
    }
    return false;
}

void printSecret(const char *secret, const char *guess) {
    printf("    Phrase: ");
    for (size_t i = 0; i < strlen(secret); i++) {
        if (string_contains_character(punctuation, secret[i])) {
            printf("%c", secret[i]);
        } else if (string_contains_character(guess, secret[i])) {
            printf("%c", secret[i]);
        } else {
            printf("_");
        }
    }
    printf("\n");
}

void initializeEliminated(char eliminated[]) {
    for (int i = 0; i < 26; i++) {
        eliminated[i] = '_';
    }
    eliminated[26] = '\0';
}

void printEliminated(const char *eliminated) {
    printf("Eliminated: ");
    for (size_t i = 0; i < 26; i++) {
        if (eliminated[i] != '_') {
            printf("%c", eliminated[i]);
        }
    }
    printf("\n\n");
}

void eliminateGuess(char c, int *mistakes, char *eliminated) {
    int index = c - 'a';
    eliminated[index] = c;
    (*mistakes)++;
}

void handleGuess(const char *secret, char *guess, char *eliminated, int *mistakes) {

    int validGuess = 0;
    char c;

    while (!validGuess) {
        c = read_letter();

        // if c is lowercase
        if (is_lowercase_letter(c)) {
            // if c is in secret
            if (string_contains_character(secret, c)) {
                // if c is already in guess, re-prompt
                if (string_contains_character(guess, c)) {
                    continue;
                }
                for (size_t i = 0; i < strlen(secret); i++) {
                    if (secret[i] == c) {
                        guess[i] = c;
                    }
                }
                validGuess = 1;
            } else if (!string_contains_character(eliminated, c)) {
                eliminateGuess(c, mistakes, eliminated);
                validGuess = 1;
            }
        }
    }
}

void initializeGuess(char *guess, const char *secret) {
    for (size_t i = 0; i < strlen(secret); i++) {
        if (string_contains_character(punctuation, secret[i])) {
            guess[i] = secret[i];
        } else {
            guess[i] = '_';
        }
    }
    guess[strlen(secret)] = '\0';
}

void printArt(int num) {
    printf("%s\n\n", arts[num]);
}

void clearScreen(char *clear_code) {
    printf("%s", clear_code);
}
