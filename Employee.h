#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "general.h"  // Include for CHECK_ALLOC and myGets

/**
 * Structure representing an employee's basic information.
 */
typedef struct {
    int id;           /**< Unique employee ID, automatically incremented */
    char* name;       /**< Dynamically allocated employee name */
    char* position;   /**< Dynamically allocated employee position */
    double salary;    /**< Employee salary */
} Employee;

/**
 * Initializes an Employee structure with a unique ID and other provided details.
 * @param employee Pointer to the Employee structure to initialize.
 */
void initEmployee(Employee* employee);

/**
 * Sets the name of an employee after dynamically allocating memory for it.
 * @param employee Pointer to the Employee structure whose name is being set.
 */
void setEmployeeName(Employee* employee);

/**
 * Sets the position of an employee after dynamically allocating memory for it.
 * @param employee Pointer to the Employee structure whose position is being set.
 */
void setEmployeePosition(Employee* employee);

/**
 * Sets the salary of an employee based on the user's input.
 * @param employee Pointer to the Employee structure whose salary is being set.
 */
void setEmployeeSalary(Employee* employee);

/**
 * Prints the details of an employee in a formatted manner.
 * @param employee Pointer to the Employee structure whose details are being printed.
 */
void printEmployeeDetails(const Employee* employee);

#endif // EMPLOYEE_H
