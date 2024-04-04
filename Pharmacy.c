#include "Pharmacy.h"
#include <stdlib.h>
#include <string.h>

void initPharmacy(Pharmacy* pharmacy) {
    pharmacy->name = NULL;
    initAddress(&pharmacy->address);
    initStock(&pharmacy->stock);
    pharmacy->employees = NULL;
    pharmacy->employeeCount = 0;
    pharmacy->employeeCapacity = 0;
    pharmacy->customers = NULL;
    pharmacy->customerCount = 0;
    pharmacy->customerCapacity = 0;
    initList(&pharmacy->openOrders);
    initList(&pharmacy->orderHistory);
    pharmacy->prescriptions = NULL;
    pharmacy->prescriptionCount = 0;
    pharmacy->prescriptionCapacity = 0;
}

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
        Employee** resizedArray = (Employee**)realloc(pharmacy->employees, newCapacity * sizeof(Employee*));

        CHECK_ALLOC(resizedArray);

        pharmacy->employees = resizedArray;
        pharmacy->employeeCapacity = newCapacity;
    }

    // Add the new employee to the array and increment the count
    pharmacy->employees[pharmacy->employeeCount] = (Employee*)malloc(sizeof(Employee));
    memcpy(pharmacy->employees[pharmacy->employeeCount], employee, sizeof(Employee));
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
        if (pharmacy->employees[i]->id == employeeID) {
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
    // Find and remove the order from the openOrders linked list
    Order* finalizedOrder = removeFromList(&pharmacy->openOrders, compareOrderNumber, &orderNumber);

    if (finalizedOrder != NULL) {
        // Update the stock based on the products in the order
        OrderProductNode* currentNode = finalizedOrder->orderProducts;
        while (currentNode != NULL) {
            updateStock(&pharmacy->stock, currentNode->product, currentNode->quantity);
            currentNode = currentNode->next;
        }

        // Add the finalized order to the orderHistory linked list
        addToList(&pharmacy->orderHistory, finalizedOrder);
    } else {
        printf("Error: This order doesn't exist!");
    }
}

// Helper function to print all customers
void printAllCustomers(const Pharmacy* pharmacy) {
    printf("List of Customers:\n");
    for (int i = 0; i < pharmacy->customerCount; ++i) {
        printf("%d: %s\n", pharmacy->customers[i].id, pharmacy->customers[i].name);
    }
}

// Helper function to print all employees
void printAllEmployees(const Pharmacy* pharmacy) {
    printf("List of Employees:\n");
    for (int i = 0; i < pharmacy->employeeCount; ++i) {
        printf("%d: %s\n", pharmacy->employees[i]->id, pharmacy->employees[i]->name);
    }
}

void addNewPrescriptionToPharmacy(Pharmacy* pharmacy) {
    Prescription newPrescription;

    // Print all customers to let the user choose
    printAllCustomers(pharmacy);

    int customerID,quantity,used=0;
    char* medicineID;
    // Get Customer ID from the client
    printf("Enter the Customer ID for the new prescription: ");
    scanf("%d", &customerID);

    // Get other prescription details from the client
    printf("Enter the Medicine ID for the new prescription: ");
    char buffer[BUFFER_SIZE];
    myGets(buffer);
    medicineID = (char*)malloc(strlen(buffer)+1);
    CHECK_ALLOC(medicineID);
    strcpy(medicineID,buffer);

    printf("Enter the quantity for the prescription: ");
    scanf("%d", &quantity);

    Date d;
    // Use initDate to set the expiration date
    initDate(&d);  // Assuming initDate prompts the client for date information

    // Resize the prescriptions array if necessary
    if (pharmacy->prescriptionCount >= pharmacy->prescriptionCapacity) {
        int newCapacity = pharmacy->prescriptionCapacity > 0 ? pharmacy->prescriptionCapacity * 2 : 1;
        Prescription* resizedArray = (Prescription*)realloc(pharmacy->prescriptions, newCapacity * sizeof(Prescription));
        if (!resizedArray) {
            printf("Failed to allocate memory for new prescriptions.\n");
            return;
        }
        pharmacy->prescriptions = resizedArray;
        pharmacy->prescriptionCapacity = newCapacity;
    }

    initPrescription(&newPrescription,customerID,medicineID,d,quantity);
    // Add the new prescription to the array and increment the count
    pharmacy->prescriptions[pharmacy->prescriptionCount++] = newPrescription;
}

void addProductOrMedicineToOrder(Pharmacy* pharmacy, Order* order) {
    showAvailableProducts(&pharmacy->stock);  // Assuming this lists all available products and medicines
    int productCode, quantity;
    printf("Enter Product/Medicine Code to add to order: ");
    scanf("%d", &productCode);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Function to add product/medicine to order, based on productCode
    Product* product = findProduct(&pharmacy->stock,productCode);
    if (!product){
        Medicine* medicine = findMedicine(&pharmacy->stock,productCode);
        if (!medicine){
            printf("Product wiht the ID %d does not exist",productCode);
            return;
        }
        addMedicineToOrder(order,pharmacy->prescriptions,pharmacy->prescriptionCount,&pharmacy->stock,productCode,order->customerID);
    }
    addProductToOrder(order, &pharmacy->stock, productCode, quantity);
}

void updateProductQuantityOrder(Pharmacy* pharmacy,Order* order) {
    printOrderProducts(order);
    int productCode, newQuantity;
    printf("Enter Product Code to update quantity: ");
    scanf("%d", &productCode);
    printf("Enter new quantity: ");
    scanf("%d", &newQuantity);
    
    Product* product = findProduct(&pharmacy->stock,productCode);
    if (!product){
        Medicine* medicine = findMedicine(&pharmacy->stock,productCode);
        if (!medicine){
            printf("Product wiht the ID %d does not exist",productCode);
            return;
        }
        updateProductQuantityInOrder(&pharmacy->stock,order,productCode,newQuantity);
    }
    updateProductQuantityInOrder(&pharmacy->stock, order, productCode, newQuantity);
}

void raiseSalaryClient(Pharmacy* pharmacy) {
    printAllEmployees(pharmacy);
    int employeeID;
    printf("Enter the ID of the employee to raise the salary: ");
    scanf("%d", &employeeID);

    Employee* employee = findEmployee(pharmacy->employees, pharmacy->employeeCount, employeeID);

    if (employee != NULL) {
        // Get precents to raise the salary
        printf("Enter the percentage to raise the salary: ");
        double percent;
        scanf("%lf", &percent);
        // Function to raise salary of employee
        raiseSalary(employee,percent);
    } else {
        printf("Employee with ID %d not found.\n", employeeID);
    }
}

void freePharmacy(Pharmacy* pharmacy) {
    freeEmployees(pharmacy->employees, pharmacy->employeeCount);
    freeCustomers(pharmacy->customers, pharmacy->customerCount);
    freePrescriptions(pharmacy->prescriptions, pharmacy->prescriptionCount);
    freeStock(&pharmacy->stock);
    freeList(&pharmacy->openOrders, freeOrder);
    freeList(&pharmacy->orderHistory, freeOrder);
}
