#include "Date.h"


void initDate(Date* date) {
    
    scanf("%d/%d/%d",date->day,date->month,date->year);
    while (!checkDateValidity(date))
    {
        printf("Error: Invalid date provided.\n");
        scanf("%d/%d/%d",date->day,date->month,date->year);
    }   
}

/**
 * Checks the validity of a given date, considering the correct range of days for each month
 * and leap years for February.
 * 
 * @param date A pointer to a Date structure to be validated.
 * @return int Returns 1 (true) if the date is valid, taking into account leap years and the correct number of days in each month. Returns 0 (false) for invalid dates.
 */
int checkDateValidity(Date* date) {
    // Check for valid year
    if (date->year < 1) return 0;

    // Check for valid month
    if (date->month < 1 || date->month > 12) return 0;

    // Check for valid day
    switch (date->month) {
        case 2: // February
            if ((date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0)) && (date->day >= 1 && date->day <= 29))
                return 1; // Leap year
            else
                return (date->day >= 1 && date->day <= 28); // Non-leap year
        case 4: case 6: case 9: case 11: // April, June, September, November
            return (date->day >= 1 && date->day <= 30);
        default: // All other months
            return (date->day >= 1 && date->day <= 31);
    }
}

/**
 * Prints the details of a given date in DD/MM/YYYY format.
 * 
 * @param date A pointer to a Date structure whose details are to be printed.
 */
void printDateDetails(Date* date) {
    printf("%02d/%02d/%04d\n", date->day, date->month, date->year);
}
