#include "Date.h"


void initDate(Date* date) {
    
    scanf("%d/%d/%d",&date->day,&date->month,&date->year);
    while (!checkDateValidity(date))
    {
        printf("Error: Invalid date provided.\n");
        scanf("%d/%d/%d",&date->day,&date->month,&date->year);
    }   
}

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

int compareDates(const Date* date1, const Date* date2) {
    if (date1->year != date2->year) {
        return date1->year - date2->year;
    } else if (date1->month != date2->month) {
        return date1->month - date2->month;
    } else {
        return date1->day - date2->day;
    }
}

void printDate(const Date* date) {
    printf("%02d/%02d/%04d\n", date->day, date->month, date->year);
}

int saveDateToBinary(FILE* file, const Date* date) {
    return fwrite(date, sizeof(Date), 1, file) == 1;
}

int loadDateFromBinary(Date* date, FILE* file) {
    return fread(date, sizeof(Date), 1, file) == 1;
}

void saveDate(FILE* file, const Date* date) {
    fprintf(file, "%d/%d/%d", date->day, date->month, date->year);
}

void loadDate(FILE* file, Date* date) {
    fscanf(file, "%d/%d/%d", &date->day, &date->month, &date->year);
}
