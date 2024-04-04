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
 * Compares two dates to determine which comes first.
 * @param date1 Pointer to the first Date structure to compare.
 * @param date2 Pointer to the second Date structure to compare.
 * @return Returns a negative value if date1 comes before date2, 0 if they are equal, and a positive value if date1 comes after date2.
 */
int compareDates(const Date* date1, const Date* date2);

/**
 * Prints the date in a standardized format (DD/MM/YYYY).
 * @param date Pointer to the Date structure to print.
 */
void printDate(const Date* date);

/**
 * Saves the date to a file in the format "DD/MM/YYYY".
 * @param file Pointer to the file to save the date to.
 * @param date Pointer to the Date structure to save.
 */
void saveDate(FILE* file, const Date* date);

/**
 * Loads the date from a file in the format "DD/MM/YYYY".
 * @param file Pointer to the file to load the date from.
 * @param date Pointer to the Date structure to load.
 */
void loadDate(FILE* file, Date* date);

#endif // DATE_H
