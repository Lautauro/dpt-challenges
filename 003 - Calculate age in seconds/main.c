/*
 * /dpt/ Challenge
 *
 * #003 - Calculate age in seconds
 * bonus: accounting for leap years.
 *
 * Given a date, calculate the time between then and now, and express it in seconds.
 *
 * TODO: Read the actual date from the computer.
 *
 */

#include <stdio.h>
#define DAY_IN_SECONDS 86400
#define YEAR_IN_SECONDS (DAY_IN_SECONDS * 365)
#define LEAP_YEAR_IN_SECONDS (DAY_IN_SECONDS * 364)
#define ACTUAL_DAY 3
#define ACTUAL_MONTH 8
#define ACTUAL_YEAR 2023

unsigned long age_to_seconds(int day, int month, int year);

int main(){
    printf("23y = %lis\n", age_to_seconds(0, 0, 2017));

    return 0;
}

unsigned long age_to_seconds(int day, int month, int year) {
    if (year > ACTUAL_YEAR)
        return 0;

    int i, leapYears = 0;

    /*
     * Count leap years.
     */

    for (i = year - (year % 4); i <= ACTUAL_YEAR; i += 4) {
        if ((i >= year && (i % 100)) || !(i % 400)) {
            ++leapYears;
        }
    }

    printf("%d años bisiestos.\n", leapYears);

    return (YEAR_IN_SECONDS * ((ACTUAL_YEAR - year) - leapYears) )+ (leapYears * LEAP_YEAR_IN_SECONDS);
}
