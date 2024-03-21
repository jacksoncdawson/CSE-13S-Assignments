#include "hangman_helpers.h"

int main(int argc, char *argv[]) {

    // check for correct usage
    if (argc != 2) {
        printf("wrong number of arguments\n");
        printf("usage: ./hangman <secret word or phrase>\n");
        printf("if the secret is mulltiple words, you must quote it\n");
        return 1;
    }

    // validate secret word
    if (!validate_secret(argv[1])) {
        return 1;
    }

    // Set up game
    char *secret = argv[1];
    char guess[strlen(secret) + 1];
    initializeGuess(guess, secret);

    char eliminated[27];
    initializeEliminated(eliminated);
    int mistakes = 0;

    // game loop
    while (true) {
        clearScreen(CLEAR_SCREEN);

        printArt(mistakes);

        printSecret(secret, guess);

        printEliminated(eliminated);

        if (mistakes == LOSING_MISTAKE) {
            printf("%s %s\n", "You lose! The secret phrase was:", secret);
            break;
        } else if (isWinner(secret, guess)) {
            printf("%s %s\n", "You win! The secret phrase was:", secret);
            break;
        } else {
            handleGuess(secret, guess, eliminated, &mistakes);
        }
    }
    return 0;
}
