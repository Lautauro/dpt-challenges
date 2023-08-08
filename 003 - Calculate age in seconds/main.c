/*
 * /dpt/ Challenge
 *
 * #003 - Calculate age in seconds
 * bonus: accounting for leap years.
 *
 * Given a date, calculate the time between then and now, and express it in seconds.
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define DAY_IN_SECONDS 86400

//  TODO: Read the actual date from the computer.
#define ACTUAL_DAY 8
#define ACTUAL_MONTH 8
#define ACTUAL_YEAR 2023

bool is_leap_year(int year);
unsigned long age_to_days(int year);
unsigned long age_to_seconds(int year);
unsigned int get_uint_input(int min, int max);

int main(void){
    unsigned int year, age;
    unsigned long ageToSeconds, ageToMinutes, ageToHours, ageToDays;

    printf("Year of birth: ");
    year = get_uint_input(1000, ACTUAL_YEAR);

    age          = ACTUAL_YEAR - year;
    ageToDays    = age_to_days(year);
    ageToHours   = ageToDays * 24;
    ageToMinutes = ageToHours * 60;
    ageToSeconds = ageToMinutes * 60;

    printf("\n%d years, %lu days, %lu hours, %lu minutes, %lu seconds.\n\n", age, ageToDays, ageToHours, ageToMinutes, ageToSeconds);

    return 0;
}

bool is_leap_year(int year) {
    if ((year % 4 == 0 && year % 100 > 0) || !(year % 400))
        return true;
    return false;
}

unsigned long age_to_days(int yearOfBirth) {

    /*
     * Reject if yearOfBirth is not valid.
     */

    if (yearOfBirth > ACTUAL_YEAR)
        return 0;

    int leapYears = 0;
    unsigned short dayOfTheCurrentYear;
    unsigned int yearsSince = (ACTUAL_YEAR - yearOfBirth) - 1;

    /*
     * Calculate day of the current year.
     */

    if (is_leap_year(ACTUAL_YEAR)) {
        dayOfTheCurrentYear = ((366.0 / 12.0) * (ACTUAL_MONTH - 1) + ACTUAL_DAY);
    } else {
        dayOfTheCurrentYear = ((365.0 / 12.0) * (ACTUAL_MONTH - 1) + ACTUAL_DAY);
    }

    /*
     * Count leap years.
     */

    for (int i = yearOfBirth - (yearOfBirth % 4); i <= ACTUAL_YEAR; i += 4) {
        if ((i >= yearOfBirth && (i % 100)) || !(i % 400)) {
            ++leapYears;
        }
    }

    return (dayOfTheCurrentYear + ((yearsSince) * 365) + leapYears);
}

unsigned long age_to_seconds(int yearOfBirth) {
    return DAY_IN_SECONDS * age_to_days(yearOfBirth);
}

unsigned int get_uint_input(int min, int max) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    unsigned int number;

    printf("\n> ");
    while (((nread = getline(&line, &len, stdin)) != -1 && line[0] == '\n'))
        printf("> ");

    number = atoi(line);
    free(line);

    if (number > max) number = max;
    if (number < min) number = min;

    return number;
}

