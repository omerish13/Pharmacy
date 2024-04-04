#include "Employee.h"

static int lastEmployeeID = 0;  // Static variable to keep track of the last used employee ID

void initEmployee(Employee* employee) {
    initPerson(&employee->person);
    employee->id = ++lastEmployeeID;  // Auto-increment the employee ID for each new employee
    setEmployeePosition(employee);
    setEmployeeSalary(employee);
}

void setEmployeePosition(Employee* employee) {
    char buffer[BUFFER_SIZE];
    printf("Enter employee position: ");
    myGets(buffer);
    employee->position = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(employee->position);
    strcpy(employee->position, buffer);
}

void setEmployeeSalary(Employee* employee) {
    char buffer[BUFFER_SIZE];
    printf("Enter employee salary: ");
    myGets(buffer);
    employee->salary = atof(buffer);
}

void raiseSalary(Employee* employee, double raisePercentage) {
    employee->salary += employee->salary * raisePercentage / 100;
}

Employee* findEmployee(Employee** employees, int numEmployees, int id) {
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i]->id == id) {
            return &employees[i];
        }
    }
    return NULL;  // Employee not found
}

void printEmployeeDetails(const Employee* employee) {
    printf("Employee ID: %d ", employee->id);
    printPersonDetails(&employee->person);
    printf("Position: %s ", employee->position);
    printf("Salary: $%.2f\n", employee->salary);
}

void saveEmployee(FILE* file, const Employee* employee) {
    savePerson(file, &employee->person);
    fprintf(file, "%d\n", employee->id);
    fprintf(file, "%s\n", employee->position);
    fprintf(file, "%.2f\n", employee->salary);
}

Employee* loadEmployee(FILE* file) {
    Employee* employee = (Employee*)malloc(sizeof(Employee));
    CHECK_ALLOC(employee);
    loadPerson(file, &employee->person);
    fscanf(file, "%d\n", &employee->id);
    char buffer[BUFFER_SIZE];
    fscanf(file, "%s\n", buffer);
    employee->position = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(employee->position);
    strcpy(employee->position, buffer);
    fscanf(file, "%lf\n", &employee->salary);
    return employee;
}

void freeEmployee(Employee* employee) {
    freePerson(&employee->person);
    free(employee->position);
    employee->position = NULL;
}

void freeEmployees(Employee** employees, int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        freeEmployee(employees[i]);
    }
    free(employees);
    employees = NULL;
}
