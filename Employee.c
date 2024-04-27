#include "Employee.h"

void initEmployee(Employee* employee, int lastEmployeeID) {
    initPerson(&employee->person);
    employee->id = lastEmployeeID;  // Auto-increment the employee ID for each new employee
    setEmployeePosition(employee);
    setEmployeeSalary(employee);
}

void setEmployeePosition(Employee* employee) {
    char buffer[BUFFER_SIZE];
    printf("Enter employee position: ");
    myGets(buffer);
    employee->position = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC_VOID(employee->position);
    strcpy(employee->position, buffer);
}

void setEmployeeSalary(Employee* employee) {
    printf("Enter employee salary: ");
    scanf("%lf", &employee->salary);
    clearInputBuffer();
}

void raiseSalary(Employee* employee, double raisePercentage) {
    employee->salary += employee->salary * raisePercentage / 100;
}

Employee* findEmployee(Employee** employees, int numEmployees, int id) {
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i]->id == id) {
            return employees[i];
        }
    }
    return NULL;  // Employee not found
}

void printEmployeeDetails(const Employee* employee) {
    printf("Employee ID: %d, ", employee->id);
    printPersonDetails(&employee->person);
    printf("Position: %s, ", employee->position);
    printf("Salary: ₪%.2f\n", employee->salary);
}

int saveEmployeeToBinary(FILE* file, const Employee* employee) {
    // if ((!savePersonToBinary(file, &employee->person)) || ((!fwrite(&employee->id, sizeof(int), 1, file)) == 1))
    //     return 0;
    if (!savePersonToBinaryFileCompressed(file, &employee->person) || fwrite(&employee->id, sizeof(int), 1, file) != 1)
        return 0;
    int length = (int)strlen(employee->position) + 1;
    if (fwrite(&length, sizeof(int), 1, file) != 1 || fwrite(employee->position, sizeof(char), length, file) != length)
        return 0;
    return fwrite(&employee->salary, sizeof(double), 1, file) == 1;
}

int loadEmployeeFromBinary(Employee* employee, FILE* file) {
    // if (!loadPersonFromBinary(&employee->person, file) || fread(&employee->id, sizeof(int), 1, file) != 1)
    //     return 0;
    if (!loadPersonFromBinaryFileCompressed(&employee->person, file) || fread(&employee->id, sizeof(int), 1, file) != 1)
        return 0;
    int length;
    if (fread(&length, sizeof(int), 1, file) != 1)
        return 0;
    employee->position = (char*)malloc(length);
    CHECK_ALLOC_INT(employee->position);
    if (fread(employee->position, sizeof(char), length, file) != length)
        return 0;
    return fread(&employee->salary, sizeof(double), 1, file) == 1;
}

void saveEmployee(FILE* file, const Employee* employee) {
    savePerson(file, &employee->person);
    fprintf(file, "%d\n", employee->id);
    fprintf(file, "%s\n", employee->position);
    fprintf(file, "%.2f\n", employee->salary);
}

Employee* loadEmployee(FILE* file) {
    Employee* employee = (Employee*)malloc(sizeof(Employee));
    CHECK_ALLOC_STRUCT(employee);
    loadPerson(&employee->person,file);
    fscanf(file, "%d\n", &employee->id);
    char buffer[BUFFER_SIZE];
    fscanf(file, "%s\n", buffer);
    employee->position = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC_STRUCT(employee->position);
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
