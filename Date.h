#ifndef DATE_H
#define DATE_H

#include <stdio.h>

/**
 * Structure representing a calendar date.
 */
typedef struct {
    int day;    /**< Day of the month (1-31) */
    int month;  /**< Month of the year (1-12) */
    int year;   /**< Year as a four-digit number */
} Date;

/**
 * Initializes a Date structure with provided values and checks for validity.
 * @param date Pointer to the Date structure to initialize.
 * @param day Day of the month to set.
 * @param month Month of the year to set.
 * @param year Year to set.
 */
void initDate(Date* date);

/**
 * Checks the validity of the provided date.
 * @param date Pointer to the Date structure to validate.
 * @return Returns 1 if the date is valid, 0 otherwise.
 */
int checkDateValidity(Date* date);

/**
 * Prints the date in a standardized format (DD/MM/YYYY).
 * @param date Pointer to the Date structure to print.
 */
void printDate(Date* date);

#endif // DATE_H
