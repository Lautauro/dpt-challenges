/*
 * /dpt/ Challenge
 *
 * #000 Random name generator
 * bonus: with usernames and passwords
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMBER_OF_NAMES 6
#define NUMBER_OF_PREFIX 2
#define NUMBER_OF_SUFFIX 4

const char *namesList[]  = { "John", "Mateo", "David", "Thom", "Cristian", "Alejo" };
const char *prefixList[] = { "The", "Untitled" };
const char *suffixList[] = { "Master", "Destroyer", "Gamer", "Pro" };

unsigned int random_uint(unsigned int limit) {
    unsigned int output = rand() % limit;
    return output;
}

void random_name(char output[]) {
    bool generateNumber; // Generate random number?
    char type, outputName[14] = "", outputPrefix[14] = "", outputSuffix[14] = "", outputNumber[4];

    // Type of generation.
    type = rand() % 3;
    generateNumber = rand() % 2;

    switch (type) {
        case 0:
            strcpy(outputPrefix, prefixList[random_uint(NUMBER_OF_PREFIX)]);
            strcpy(outputName, namesList[random_uint(NUMBER_OF_NAMES)]);
            strcpy(outputSuffix, suffixList[random_uint(NUMBER_OF_SUFFIX)]);
            break;
        case 1:
            strcpy(outputPrefix, prefixList[random_uint(NUMBER_OF_PREFIX)]);
            strcpy(outputName, namesList[random_uint(NUMBER_OF_NAMES)]);
            generateNumber = true;
            break;
        case 2:
            strcpy(outputName, namesList[random_uint(NUMBER_OF_NAMES)]);
            strcpy(outputSuffix, suffixList[random_uint(NUMBER_OF_SUFFIX)]);
            break;
    }

    strcpy(output, outputPrefix);
    strcat(output, outputName);
    strcat(output, outputSuffix);

    if (generateNumber) {
        sprintf(outputNumber, "%d", random_uint(9000));
        strcat(output, outputNumber);
    }
}

int main() {
    srand(time(NULL)); // SEED

    char str[1000];
    int i;

    printf("#000 Random name generator:\n\n");

    for (i = 0; i < 5; ++i) {
        random_name(str);
        printf("Username: %s\n", str);
    }

    return 0;
}
