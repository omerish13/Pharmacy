#include "Pharmacy.h"
#include <stdlib.h>
#include <string.h>

void createNewOrder(Pharmacy* pharmacy, int customerID, int employeeID) {
    // Allocate memory for a new order
    Order* newOrder = (Order*)malloc(sizeof(Order));
    CHECK_ALLOC(newOrder);

    // Initialize the new order with the given customer and employee IDs
    initOrder(newOrder, customerID, employeeID);

    // Update the lastModified date of the order to the current date/time
    updateLastModified(newOrder);

    // Add the new order to the pharmacy's openOrders linked list
    addToList(&pharmacy->openOrders, newOrder);
}

void addEmployee(Pharmacy* pharmacy, const Employee* employee) {
    // Check if the employees array needs to be expanded
    if (pharmacy->employeeCount == pharmacy->employeeCapacity) {
        int newCapacity = pharmacy->employeeCapacity > 0 ? pharmacy->employeeCapacity * 2 : 1;  // Double the capacity, start with 1 if 0
        Employee* resizedArray = (Employee*)realloc(pharmacy->employees, newCapacity * sizeof(Employee));

        CHECK_ALLOC(resizedArray);

        pharmacy->employees = resizedArray;
        pharmacy->employeeCapacity = newCapacity;
    }

    // Add the new employee to the array and increment the count
    memcpy(&pharmacy->employees[pharmacy->employeeCount], employee, sizeof(Employee));
    pharmacy->employeeCount++;
}

void addCustomer(Pharmacy* pharmacy, const Customer* customer) {
    // Check if the customer array needs to be expanded
    if (pharmacy->customerCount == pharmacy->customerCapacity) {
        int newCapacity = pharmacy->customerCapacity > 0 ? pharmacy->customerCapacity * 2 : 1;  // Double the capacity, start with 1 if 0
        Customer* resizedArray = (Customer*)realloc(pharmacy->customers, newCapacity * sizeof(Customer));

        if (resizedArray == NULL) {
            // Handle reallocation failure; for simplicity, we just return here
            return;
        }

        pharmacy->customers = resizedArray;
        pharmacy->customerCapacity = newCapacity;
    }

    // Add the new customer to the array and increment the count
    memcpy(&pharmacy->customers[pharmacy->customerCount], customer, sizeof(Customer));
    pharmacy->customerCount++;
}

void removeEmployee(Pharmacy* pharmacy, int employeeID) {
    int found = 0;  // Flag to indicate if the employee was found

    for (int i = 0; i < pharmacy->employeeCount; i++) {
        if (pharmacy->employees[i].id == employeeID) {
            found = 1;
            
            // Shift the rest of the employees down by one to fill the gap
            size_t bytesToMove = (pharmacy->employeeCount - i - 1) * sizeof(Employee);
            memmove(&pharmacy->employees[i], &pharmacy->employees[i + 1], bytesToMove);

            pharmacy->employeeCount--;  // Decrease the count of employees
            break;  // Exit the loop once the employee is found and removed
        }
    }

    if (!found) {
        printf("Error: Employee with this ID is not part of Pharmacy staff.");
        return;
    }
}

// Helper function to compare order numbers, used by removeFromList
int compareOrderNumber(void* order, void* orderNumber) {
    Order* o = (Order*)order;
    int* num = (int*)orderNumber;
    return o->orderNumber - *num;  // 0 if equal
}

void cancelOrder(Pharmacy* pharmacy, int orderNumber) {
    // Find and remove the order from the openOrders linked list
    Order* removedOrder = removeFromList(&pharmacy->openOrders, compareOrderNumber, &orderNumber);

    if (removedOrder != NULL) {
        // Free the memory allocated for the removed order
        freeOrder(removedOrder);
        free(removedOrder);
    } else {
        printf("Error: Order with that ID hasn't been found!");
    }
}

void purchaseOrder(Pharmacy* pharmacy, int orderNumber) {
    // Move the order from openOrders to orderHistory and update stock
}
