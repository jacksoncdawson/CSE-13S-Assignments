#include "names.h"

#include <stdio.h>
#include <stdlib.h>

#define SEED 4823

// set up die
typedef enum { DOT, LEFT, RIGHT, CENTER } Position;
Position die[6] = { DOT, DOT, DOT, LEFT, CENTER, RIGHT };

// set up player
typedef struct {
    const char *name;
    int chips;
} Player;

// roll the die (use random() % 6)
Position rollDie(void) {
    return die[random() % 6];
}

// returns 1 if there is a winner; 0 otherwise
int isWinner(Player players[], int num_players) {
    int players_with_chips = 0;
    for (int j = 0; j < num_players; j++) {
        if (players[j].chips > 0) {
            players_with_chips++;
        }
    }
    return players_with_chips == 1;
}

int main(void) {

    // prompt user to input num of players
    int num_players = 3;
    printf("Number of players (3 to 10)? ");
    int scanf_result = scanf("%d", &num_players);

    // validate user input
    if (scanf_result < 1 || num_players < 3 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    // prompt user for random seed
    unsigned seed = SEED;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    // validate user input
    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
        srandom(SEED);
    } else {
        srandom(seed);
    }

    // Create Players Array
    Player players[num_players];

    // Fill Players Array
    for (int i = 0; i < num_players; i++) {
        Player player;
        player.name = player_name[i];
        player.chips = 3;
        players[i] = player;
    }

    int winnerFound = 0;
    while (!winnerFound) {

        // for each player, starting at player 0
        for (int i = 0; i < num_players; i++) {
            Player player = players[i];

            int rollCount = 0;
            int chips = player.chips;

            if (chips > 0) {
                for (int j = 0; j < chips; j++) {

                    if (rollCount == 3) {
                        break;
                    }

                    Position roll = rollDie();
                    rollCount++;

                    if (roll == LEFT) {
                        players[(i + 1) % num_players].chips++;
                        player.chips -= 1;
                    } else if (roll == RIGHT) {
                        players[(i - 1 + num_players) % num_players].chips++;
                        player.chips -= 1;
                    } else if (roll == CENTER) {
                        player.chips -= 1;
                    } else if (roll == DOT) {
                        continue;
                    }
                }
                players[i] = player;
                printf("%s: ends her turn with %d\n", player.name, player.chips);
            } else {
                continue;
            }

            if (isWinner(players, num_players)) {
                winnerFound = 1;
                break;
            };
        }
    }
    for (int i = 0; i < num_players; i++) {
        if (players[i].chips > 0) {
            printf("%s won!\n", players[i].name);
            break;
        }
    }
    return 0;
}
