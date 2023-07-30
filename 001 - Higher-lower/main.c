/*
 * /dpt/ Challenge
 *
 * #001 Higher/lower, heads/tails
 *
 * Higher/lower:
 * 1. The player one is dealt a card. The player then guesses whether the next card will be higher or lower than the
 * next card. If wrong, the player drinks once (because one card was showing). If correct, the player guesses again.
 * 2. After taking at least three cards, the player may choose to continue or pass. If the player passes, the next
 * player starts where the previous left off.
 * 3. When a player guesses incorrectly, they drink for each card showing. So, the strategy is to build up a lot of
 * cards and then pass it to the next player.
 * 4. Before play starts, determine by vote if equal cards are a loss or correct guess.
 *
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER 0
#define HIGHER 1
#define RANDOM_NUMBER_MAX 100
#define PLAYERS_LIMIT 10
#define ROUNDS_LIMITS 10
#define POINT 10

unsigned int random_uint(unsigned int limit);
bool random_bool();
bool get_bool_answer();
unsigned int get_uint_answer(int min, int limit);
void enter_to_continue();

char wait;

int main() {

    /*
     * Seed.
     */

    srandom( time(NULL) );

    /*
     * Title.
     */

    printf("#001 Higher/lower game\n\nPress \"Enter\" to start.");
    scanf("%c", &wait);

    /*
     * Set-up.
     */

    int answer;
    bool equalAreLoss, correctAnswer;
    unsigned int numberOfPlayers, actualPlayer = 1, numberOfRounds, round = 1, randomNumber, previousNumber;

    unsigned int playerPoints[PLAYERS_LIMIT];

    printf("\n@:=:@ SETTINGS @:=:@\n\n");

    printf("Equal cards are a loss? ");
    equalAreLoss = get_bool_answer();

    printf("Number of players ");
    numberOfPlayers = get_uint_answer(1, PLAYERS_LIMIT);

    printf("Number of rounds ");
    numberOfRounds = get_uint_answer(1, ROUNDS_LIMITS);

    /*
     * Print options
     */

    printf("\n#########################\n\n"); // Separator

    if (equalAreLoss)
        printf("Equal cards are a loss?: Yes\n");
    else
        printf("Equal cards are a loss?: No\n");

    printf("\nNumber of players:\t %d\n", numberOfPlayers);
    printf("\nNumber of rounds:\t %d\n", numberOfRounds);

    enter_to_continue();

    while (round <= numberOfRounds) {

        /*
         * Actual game.
         */

        printf("\n#########################\n\n"); // Separator
        printf("ROUND %d/%d. ", round, numberOfRounds);

        do {
            printf("Player %d turn.\n\n", actualPlayer);

            previousNumber = randomNumber = random_uint(RANDOM_NUMBER_MAX);
            printf("Your first number is: %d.\n\n", randomNumber);

            do {
                randomNumber = random_uint(RANDOM_NUMBER_MAX);
                printf("Is the next number lower (%d) or higher (%d) than %d? ", LOWER, HIGHER, previousNumber);

                answer = get_uint_answer(0, 1);

                /*
                 * Check answer
                 */

                if (randomNumber == previousNumber) {
                    if (equalAreLoss)
                        correctAnswer = false;
                    else
                        correctAnswer = true;
                } else if (((randomNumber > previousNumber) && answer == HIGHER) || ((randomNumber < previousNumber) && answer == LOWER)) {
                    correctAnswer = true;
                } else {
                    correctAnswer = false;
                }

                previousNumber = randomNumber;

                /*
                 * Send answer.
                 */

                if (correctAnswer) {
                    playerPoints[actualPlayer-1] += POINT;
                    printf("\nCorrect!\nThe number was:   %d\n", randomNumber);
                } else {
                    printf("\nIncorrect!\nThe number was: %d\n", randomNumber);

                    enter_to_continue();
                }

            } while (correctAnswer);

        printf("\n#########################\n\n"); // Separator

        } while ((++actualPlayer) <= (numberOfPlayers ));

        actualPlayer = 1;
        ++round;
    }

    /*
     * Scoreboard
     */

    printf("@:=:@ SCOREBOARD @:=:@\n\n");

    int i;

    for (i = 0; i < numberOfPlayers; ++i) {
        printf("Player %d: %dp\n", i, playerPoints[i]);
    }

    enter_to_continue();

    return 0;
}

/*
 * Get random unsigned int value.
 */

unsigned int random_uint(unsigned int limit) {
    return random() % limit;
}

/*
 * Get random boolean value.
 */

bool random_bool() {
    return random() % 2;
}

/*
 * Yes/No input.
 */

bool get_bool_answer() {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    printf("[Y/N]\n> ");

    while ((nread = getline(&line, &len, stdin)) != -1 && line[0] == '\n')
        printf("> ");

    if (tolower(line[0]) == 'y') {
        free(line);
        return true;
    }

    free(line);

    return false;
}

/*
 * Numeric input.
 */

unsigned int get_uint_answer(int min, int limit) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    printf("[%d - %d]\n> ", min, limit);
    while ((nread = getline(&line, &len, stdin)) != -1 && line[0] == '\n')
        printf("> ");

    unsigned int answer = atoi(line);

    if (answer > limit)
        answer = limit;

    if (answer < min)
        answer = min;

    free(line);
    return answer;
}

/*
 * "Press Enter to continue" message.
 */

void enter_to_continue() {
    printf("\nPress \"Enter\" to continue.");
    scanf("%c", &wait);
}
