#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "general.h"  // Include for CHECK_ALLOC and myGets
#include "Person.h"   // Include the Person struct definition

/**
 * Structure representing an employee's basic information.
 */
typedef struct {
    Person person;    /**< Base Person structure */
    int id;           /**< Unique employee ID, automatically incremented */
    char* position;   /**< Dynamically allocated employee position */
    double salary;    /**< Employee salary */
} Employee;

/**
 * Initializes an Employee object with the given last employee ID.
 *
 * @param employee A pointer to the Employee object to be initialized.
 * @param lastEmployeeID The last employee ID to be assigned to the Employee.
 */
void initEmployee(Employee* employee, int lastEmployeeID);

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
 * Raises the salary of an employee by a given percentage.
 * @param employee Pointer to the Employee structure whose salary is being raised.
 * @param raisePercentage The percentage by which to raise the salary.
 */
void raiseSalary(Employee* employee, double raisePercentage);

/**
 * Searches for an employee in an array of employees by their unique ID.
 * @param employees Array of Employee structures to search.
 * @param numEmployees Number of employees in the array.
 * @param id The unique ID of the employee to find.
 * @return Pointer to the found Employee structure, or NULL if the employee is not found.
 */
Employee* findEmployee(Employee** employees, int numEmployees, int id);

/**
 * Prints the details of an employee in a formatted manner.
 * @param employee Pointer to the Employee structure whose details are being printed.
 */
void printEmployeeDetails(const Employee* employee);

/**
 * Saves an employee's details to a binary file.
 * @param file Pointer to the binary file.
 * @param employee Pointer to the Employee structure to save.
 * @return 1 if the employee details are successfully saved, 0 otherwise.
 */
int saveEmployeeToBinary(FILE* file, const Employee* employee);

/**
 * Loads an employee's details from a binary file.
 * @param employee Pointer to the Employee structure to load the details into.
 * @param file Pointer to the binary file.
 * @return 1 if the employee details are successfully loaded, 0 otherwise.
 */
int loadEmployeeFromBinary(Employee* employee, FILE* file);

/**
 * Save employee details from the user, including name
 * and age.
 * @param employee Pointer to the Employee structure to store the details.
 */
void saveEmployee(FILE* file, const Employee* employee);

/**
 * Reads employee details from a file, including name and age.
 * @param file Pointer to the text file.
 */
Employee* loadEmployee(FILE* file);

/**
 * Frees the dynamically allocated memory for the employee's name and position.
 * @param employee Pointer to the Employee structure to free.
 */
void freeEmployee(Employee* employee);

/**
 * Frees the dynamically allocated memory for an array of employees.
 * @param employees Array of Employee structures to free.
 * @param numEmployees Number of employees in the array.
 */
void freeEmployees(Employee** employees, int numEmployees);

#endif // EMPLOYEE_H
