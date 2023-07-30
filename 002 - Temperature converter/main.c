/*
 * /dpt/ Challenge
 *
 * #002 - Temperature converter
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

float fahr_to_cel(float fahr);
float kelv_to_cel(float kelv);
float rank_to_cel(float rank);
unsigned int get_uint_input(int min, int max, bool showRange);

int main() {
    unsigned option;
    float temperature, temperatureConverted;
    char temperatureLetter;

    printf("Temperature converter:");
    printf("1 - Fahrenheit to Celsius.\n");
    printf("2 - Kelvin to Celsius.\n");
    printf("3 - Rankie to Celsius.\n");
    option = get_uint_input(1, 3, false);

    printf("\nCelsius: ");
    temperature = get_uint_input(0, 900, false);

    switch(option) {
        case 1:
        temperatureConverted = fahr_to_cel(temperature);
        temperatureLetter = 'F';
        break;
        case 2:
        temperatureConverted = kelv_to_cel(temperature);
        temperatureLetter = 'K';
        break;
        case 3:
        temperatureConverted = rank_to_cel(temperature);
        temperatureLetter = 'R';
        break;
    }

    printf("\n%0.2fº%c = %0.2fºC\n",temperature, temperatureLetter, temperatureConverted);

    return 0;
}

float fahr_to_cel(float fahr) {
    return (fahr - 32.0) * (5.0 / 9.0);
}

float kelv_to_cel(float kelv) {
    return kelv - 273.15;
}

float rank_to_cel(float rank) {
    return (rank - 491.67) * ( 5.0 / 9.0 ) ;
}

unsigned int get_uint_input(int min, int max, bool showRange) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    unsigned int number;

    if (showRange) printf("[ %d - %d ]", min, max);
    printf("\n> ");
    while ((nread = getline(&line, &len, stdin)) != -1 && line[0] == '\n')
        printf("> ");

    number = atoi(line);
    free(line);

    if (number > max) number = max;
    if (number < min) number = min;

    return number;
}
