#include "Employee.h"

static int lastEmployeeID = 0;  // Static variable to keep track of the last used employee ID

void initEmployee(Employee* employee) {
    employee->id = ++lastEmployeeID;  // Auto-increment the employee ID for each new employee
    setEmployeeName(employee);
    setEmployeePosition(employee);
    setEmployeeSalary(employee);
}

void setEmployeeName(Employee* employee) {
    char buffer[BUFFER_SIZE];
    printf("Enter employee name: ");
    myGets(buffer, BUFFER_SIZE);
    employee->name = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(employee->name);
    strcpy(employee->name, buffer);
}

void setEmployeePosition(Employee* employee) {
    char buffer[BUFFER_SIZE];
    printf("Enter employee position: ");
    myGets(buffer, BUFFER_SIZE);
    employee->position = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(employee->position);
    strcpy(employee->position, buffer);
}

void setEmployeeSalary(Employee* employee) {
    char buffer[BUFFER_SIZE];
    printf("Enter employee salary: ");
    myGets(buffer, BUFFER_SIZE);
    employee->salary = atof(buffer);
}

void printEmployeeDetails(const Employee* employee) {
    printf("Employee ID: %d\n", employee->id);
    printf("Name: %s\n", employee->name);
    printf("Position: %s\n", employee->position);
    printf("Salary: $%.2f\n", employee->salary);
}