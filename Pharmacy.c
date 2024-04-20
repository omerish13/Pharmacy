#include "Pharmacy.h"
#include <stdlib.h>
#include <string.h>

void initPharmacy(Pharmacy* pharmacy) {
    pharmacy->name = (char*)malloc(BUFFER_SIZE);
    CHECK_ALLOC_VOID(pharmacy->name);
    pharmacy->employees = NULL;
    pharmacy->employeeCount = 0;
    pharmacy->employeeCapacity = 0;
    pharmacy->customers = NULL;
    pharmacy->customerCount = 0;
    pharmacy->customerCapacity = 0;
    initList(&pharmacy->orderHistory);
    pharmacy->prescriptions = NULL;
    pharmacy->prescriptionCount = 0;
    pharmacy->prescriptionCapacity = 0;
}

void initPharmacyClient(Pharmacy* pharmacy) {
    pharmacy->name = (char*)malloc(BUFFER_SIZE);
    CHECK_ALLOC_VOID(pharmacy->name);
    setPharmacyName(pharmacy->name);
    initAddress(&pharmacy->address);
    initStock(&pharmacy->stock);
    pharmacy->employees = NULL;
    pharmacy->employeeCount = 0;
    pharmacy->employeeCapacity = 0;
    pharmacy->customers = NULL;
    pharmacy->customerCount = 0;
    pharmacy->customerCapacity = 0;
    initList(&pharmacy->orderHistory);
    pharmacy->prescriptions = NULL;
    pharmacy->prescriptionCount = 0;
    pharmacy->prescriptionCapacity = 0;
}

void setPharmacyName(char* name) {
    printf("Enter the name of the pharmacy: ");
    myGets(name);
}

Order* createNewOrder(Pharmacy* pharmacy, int customerID, int employeeID) {
    // Allocate memory for a new order
    Order* newOrder = (Order*)malloc(sizeof(Order));
    CHECK_ALLOC_STRUCT(newOrder);

    // Initialize the new order with the given customer and employee IDs
    Employee* employee = findEmployee(pharmacy->employees, pharmacy->employeeCount, employeeID);
    initOrder(newOrder, customerID, employee, pharmacy->orderHistory.size + 1);
    showOrder(newOrder);

    // Update the lastModified date of the order to the current date/time
    updateLastModified(newOrder);
    
    return newOrder;
}

Order* createNewOrderInteractive(Pharmacy* pharmacy) {
    if (pharmacy->customerCount == 0) {
        printf("No customers available. Please add a customer first.\n");
        return NULL;
    }
    Order* newOrder = (Order*)malloc(sizeof(Order));
    CHECK_ALLOC_STRUCT(newOrder);
    int customerID, employeeID;
    printAllCustomers(pharmacy);
    printf("Enter the Customer ID for the new order: ");
    scanf("%d", &customerID);
    printAllEmployees(pharmacy);
    printf("Enter the Employee ID for the new order: ");
    scanf("%d", &employeeID);

    return createNewOrder(pharmacy, customerID, employeeID);
}


void addEmployee(Pharmacy* pharmacy, const Employee* employee) {
    // Check if the employees array needs to be expanded
    if (pharmacy->employeeCount == pharmacy->employeeCapacity) {
        int newCapacity = pharmacy->employeeCapacity > 0 ? pharmacy->employeeCapacity * 2 : 1;  // Double the capacity, start with 1 if 0
        Employee** resizedArray = (Employee**)realloc(pharmacy->employees, newCapacity * sizeof(Employee*));

        CHECK_ALLOC_VOID(resizedArray);

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

void removeEmployeeInteractive(Pharmacy* pharmacy) {
    if (pharmacy->employeeCount == 0) {
        printf("No employees available to remove.\n");
        return;
    }
    printAllEmployees(pharmacy);
    int employeeID;
    printf("Enter the ID of the employee to remove: ");
    scanf("%d", &employeeID);

    removeEmployee(pharmacy, employeeID);
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

void cancelOrder(Order* order) {
    freeOrder(order);
    free(order);
}

void purchaseOrder(Pharmacy* pharmacy,Order* order) {

    if (order != NULL) {
        // Update the stock based on the products in the order
        ListNode* currentNode = order->orderProducts->head;
        while (currentNode != NULL) {
            OrderProductNode* orderProduct = (OrderProductNode*)currentNode->item;
            decreaseStockQuantity(&pharmacy->stock, orderProduct->productCode, orderProduct->quantity);
            currentNode = currentNode->next;
        }

        // Add the finalized order to the orderHistory linked list
        addToList(&pharmacy->orderHistory, order);
    } else {
        printf("Error: This order doesn't exist!");
    }
}

// Helper function to print all customers
void printAllCustomers(const Pharmacy* pharmacy) {
    printf("List of Customers:\n");
    for (int i = 0; i < pharmacy->customerCount; ++i) {
        printf("%d: %s\n", pharmacy->customers[i].id, pharmacy->customers[i].person.name);
    }
}

// Helper function to print all employees
void printAllEmployees(const Pharmacy* pharmacy) {
    printf("List of Employees:\n");
    for (int i = 0; i < pharmacy->employeeCount; ++i) {
        printf("%d: %s\n", pharmacy->employees[i]->id, pharmacy->employees[i]->person.name);
    }
}

void addNewPrescriptionToPharmacy(Pharmacy* pharmacy) {
    Prescription newPrescription;

    if (pharmacy->customerCount == 0) {
        printf("No customers available. Please add a customer first.\n");
        return;
    }
    // Print all customers to let the user choose
    printAllCustomers(pharmacy);

    int customerID,quantity;
    char* medicineID;
    // Get Customer ID from the client
    printf("Enter the Customer ID for the new prescription: ");
    Customer* customer;
    do
    {
        scanf("%d", &customerID);
        clearInputBuffer();
        customer = findCustomerByID(pharmacy->customers,pharmacy->customerCount,customerID);
        if (customer == NULL){
            printf("Customer with the ID %d does not exist. Please enter a valid ID: ",customerID);
        }
    } while (customer == NULL);
    
    

    // Get other prescription details from the client
    printf("Enter the Medicine ID for the new prescription: ");
    char buffer[BUFFER_SIZE];
    myGets(buffer);
    medicineID = (char*)malloc(strlen(buffer)+1);
    CHECK_ALLOC_VOID(medicineID);
    strcpy(medicineID,buffer);

    printf("Enter the quantity for the prescription: ");
    scanf("%d", &quantity);
    clearInputBuffer();
    

    Date d;
    // Use initDate to set the expiration date
    printf("Enter date (dd/mm/yyyy): ");
    initDate(&d);
    
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

    initPrescription(&newPrescription,pharmacy->customers,pharmacy->customerCount,customerID,medicineID,&pharmacy->stock,d,quantity,pharmacy->prescriptionCount+1);
    // Add the new prescription to the array and increment the count
    pharmacy->prescriptions[pharmacy->prescriptionCount++] = newPrescription;
}

void addEmployeeInteractive(Pharmacy* pharmacy) {
    Employee newEmployee;
    initEmployee(&newEmployee, pharmacy->employeeCount + 1);

    // Add the new employee to the pharmacy
    addEmployee(pharmacy, &newEmployee);
}

void addCustomerInteractive(Pharmacy* pharmacy) {
    Customer newCustomer;
    initCustomer(&newCustomer, pharmacy->customerCount + 1);

    // Add the new customer to the pharmacy
    addCustomer(pharmacy, &newCustomer);
}

void addProductOrMedicineToOrder(Pharmacy* pharmacy, Order* order) {
    showAvailableProducts(&pharmacy->stock);
    int productCode, quantity;
    printf("Enter Product/Medicine Code to add to order: ");
    scanf("%d", &productCode);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Function to add product/medicine to order, based on productCode
    Product* product = findProduct(&pharmacy->stock,productCode);
    if (product == NULL){
        Medicine* medicine = findMedicine(&pharmacy->stock,productCode);
        if (medicine == NULL){
            printf("Product with the ID %d does not exist",productCode);
            return;
        }
        if (addMedicineToOrder(order,pharmacy->prescriptions,pharmacy->prescriptionCount,&pharmacy->stock,medicine,order->customerID)){
            printf("Medicine added to order.\n");
            return;
        }
        else
        {
            printf("Failed to add medicine to order.\n");
            return;
        }
    }
    if (addProductToOrder(order, &pharmacy->stock, product, quantity))
        printf("Product added to order.\n");
    else
        printf("Failed to add product to order.\n");
}

void updateProductQuantityOrder(Pharmacy* pharmacy,Order* order) {
    printf("Order Products:\n");
    printList(order->orderProducts,&printOrderProductNode);
    printf("Order Medicines:\n");
    printList(order->orderMedicines,&printOrderMedicineNode);
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

void replaceEmployeeInOrder(Pharmacy* pharmacy, Order* order) {
    printAllEmployees(pharmacy);
    int employeeID;
    printf("Enter the ID of the employee to replace: ");
    scanf("%d", &employeeID);

    Employee* newEmployee = findEmployee(pharmacy->employees, pharmacy->employeeCount, employeeID);

    if (newEmployee != NULL) {
        // Function to replace employee in order
        updateEmployeeInOrder(order,newEmployee);
    } else {
        printf("Employee with ID %d not found.\n", employeeID);
    }
}

void printPharmacyDetails(const Pharmacy* pharmacy) {
    printf("Pharmacy Name: %s\n", pharmacy->name);
    printAddressDetails(&pharmacy->address);
    printf("Number of Employees: %d\n", pharmacy->employeeCount);
    printf("Number of Customers: %d\n", pharmacy->customerCount);
    printf("Number of Prescriptions: %d\n", pharmacy->prescriptionCount);
    printf("Prescriptions:\n");
    printPrescriptions(pharmacy->prescriptions, pharmacy->prescriptionCount);
    printf("Number of Orders: %d\n", pharmacy->orderHistory.size);
    printStockDetails(&pharmacy->stock);
}

int savePharmacyToBinary(FILE* file, const Pharmacy* pharmacy) {
    // Save the pharmacy name
    int length = (int)strlen(pharmacy->name)+1;
    if (fwrite(&length, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(pharmacy->name, sizeof(char), length, file) != length) {
        return 0;
    }
    // Save the pharmacy address
    if (!saveAddressToBinary(&pharmacy->address,file)) {
        return 0;
    }

    // Save the pharmacy stock
    if (!saveStockToBinary(&pharmacy->stock,file)) {
        return 0;
    }

    // Save the number of employees
    if (fwrite(&pharmacy->employeeCount, sizeof(int), 1, file) != 1) {
        return 0;
    }

    // Save the employees
    for (int i = 0; i < pharmacy->employeeCount; i++) {
        if (!saveEmployeeToBinary(file, pharmacy->employees[i])) {
            return 0;
        }
    }

    // Save the number of customers
    if (fwrite(&pharmacy->customerCount, sizeof(int), 1, file) != 1) {
        return 0;
    }

    // Save the customers
    for (int i = 0; i < pharmacy->customerCount; i++) {
        if (!saveCustomerToBinary(file, &pharmacy->customers[i])) {
            return 0;
        }
    }

    // Save the number of prescriptions
    if (fwrite(&pharmacy->prescriptionCount, sizeof(int), 1, file) != 1) {
        return 0;
    }

    // Save the prescriptions
    for (int i = 0; i < pharmacy->prescriptionCount; i++) {
        if (!savePrescriptionToBinary(&pharmacy->prescriptions[i],file)) {
            return 0;
        }
    }

    // Save the order history
    if (!saveListBinary(file, &pharmacy->orderHistory, (int (*)(FILE*, const void*))saveOrderToBinary)) {
        return 0;
    }

    return 1;
}

void savePharmacyToFile(FILE* file, const Pharmacy* pharmacy) {
    fprintf(file, "%s\n", pharmacy->name);
    saveAddress(&pharmacy->address, file);
    saveStock(&pharmacy->stock, file);
    fprintf(file, "%d\n", pharmacy->employeeCount);
    for (int i = 0; i < pharmacy->employeeCount; i++) {
        saveEmployee(file, pharmacy->employees[i]);
    }
    fprintf(file, "%d\n", pharmacy->customerCount);
    for (int i = 0; i < pharmacy->customerCount; i++) {
        saveCustomer(file, &pharmacy->customers[i]);
    }
    fprintf(file, "%d\n", pharmacy->prescriptionCount);
    for (int i = 0; i < pharmacy->prescriptionCount; i++) {
        savePrescription(&pharmacy->prescriptions[i], file);
    }
    saveList(file, &pharmacy->orderHistory, (void (*)(FILE*, const void*))saveOrder);
}

Employee** loadEmployees(FILE* file, int numEmployees) {
    if (numEmployees <= 0) {
        return NULL;
    }
    Employee** employees = (Employee**)malloc((unsigned long)numEmployees * sizeof(Employee*));
    CHECK_ALLOC_STRUCT(employees);

    for (int i = 0; i < numEmployees; i++) {
        employees[i] = (Employee*)malloc(sizeof(Employee));
        CHECK_ALLOC_STRUCT(employees[i]);
        employees[i] = loadEmployee(file);
    }

    return employees;
}

Employee** loadEmployeesFromBinary(FILE* file, int numEmployees) {
    if (numEmployees <= 0) {
        return NULL;
    }
    Employee** employees = (Employee**)malloc((unsigned long)numEmployees * sizeof(Employee*));
    CHECK_ALLOC_STRUCT(employees);

    for (int i = 0; i < numEmployees; i++) {
        employees[i] = (Employee*)malloc(sizeof(Employee));
        CHECK_ALLOC_STRUCT(employees[i]);
        loadEmployeeFromBinary(employees[i], file);
    }

    return employees;
}

Customer* loadCustomers(FILE* file, int numCustomers) {
    if (numCustomers <= 0) {
        return NULL;
    }
    Customer* customers = (Customer*)malloc(numCustomers * sizeof(Customer));
    CHECK_ALLOC_STRUCT(customers);

    for (int i = 0; i < numCustomers; i++) {
        customers[i] = *loadCustomer(file);
    }

    return customers;
}

Customer* loadCustomersFromBinary(FILE* file, int numCustomers) {
    if (numCustomers <= 0) {
        return NULL;
    }
    Customer* customers = (Customer*)malloc(numCustomers * sizeof(Customer));
    CHECK_ALLOC_STRUCT(customers);

    for (int i = 0; i < numCustomers; i++) {
        customers[i] = *loadCustomerFromBinary(file);
    }

    return customers;
}

Prescription* loadPrescriptions(FILE* file, int numPrescriptions,Customer* customers, int numCustomers,Stock* stock) {
    if (numPrescriptions <= 0) {
        return NULL;
    }
    Prescription* prescriptions = (Prescription*)malloc(numPrescriptions * sizeof(Prescription));
    CHECK_ALLOC_STRUCT(prescriptions);

    for (int i = 0; i < numPrescriptions; i++) {
        prescriptions[i] = *loadPrescription(file, customers, numCustomers, stock);
    }

    return prescriptions;
}

Prescription* loadPrescriptionsFromBinary(FILE* file, int numPrescriptions,Customer* customers, int numCustomers,Stock* stock) {
    if (numPrescriptions <= 0) {
        return NULL;
    }
    Prescription* prescriptions = (Prescription*)malloc(numPrescriptions * sizeof(Prescription));
    CHECK_ALLOC_STRUCT(prescriptions);

    for (int i = 0; i < numPrescriptions; i++) {
        if (!loadPrescriptionFromBinary(&prescriptions[i], file, customers, numCustomers, stock))
            return NULL;
    }

    return prescriptions;
}

void loadOrders(FILE* file, const Employee** employees, int numEmployees, LinkedList* orders) {
    initList(orders);
    
    int numOrders;
    fscanf(file, "%d\n", &numOrders);
    printf("Number of orders: %d\n", numOrders);
    if (numOrders <= 0) {
        return;
    }
    for (int i = 0; i < numOrders; i++) {
        Order* order = loadOrder(file, (Employee**)employees, numEmployees);
        addToList(orders, order);
    }
}

void loadOrdersFromBinary(FILE* file, const Employee** employees, int numEmployees, LinkedList* orders) {
    initList(orders);

    int numOrders;
    if (fread(&numOrders, sizeof(int), 1, file) != 1) {
        return;
    }
    for (int i = 0; i < numOrders; i++) {
        Order* order = loadOrderFromBinary(file, (Employee**)employees, numEmployees);
        addToList(orders, order);
    }
}

int loadPharmacyFromBinary(FILE* file, Pharmacy* pharmacy) {
    initPharmacy(pharmacy);
    // Read the pharmacy name from the file
    int length;
    if (fread(&length, sizeof(int), 1, file) != 1) {
        return 0;
    }
    pharmacy->name = (char*)malloc(length);
    CHECK_ALLOC_INT(pharmacy->name);
    if (fread(pharmacy->name, sizeof(char), length, file) != length) {
        return 0;
    }

    if (!loadAddressFromBinary(&pharmacy->address,file)) {
        return 0;
    }

    if (!loadStockFromBinary(file, &pharmacy->stock)) {
        printf("Failed to load stock.\n");
        return 0;
    }

    if (fread(&pharmacy->employeeCount, sizeof(int), 1, file) != 1) {
        printf("Failed to read employee count.\n");
        return 0;
    }
    if (pharmacy->employeeCount > 0)
        pharmacy->employees = loadEmployeesFromBinary(file, pharmacy->employeeCount);

    if (fread(&pharmacy->customerCount, sizeof(int), 1, file) != 1) {
        printf("Failed to read customer count.\n");
        return 0;
    }
    if (pharmacy->customerCount > 0)
        pharmacy->customers = loadCustomersFromBinary(file, pharmacy->customerCount);

    if (fread(&pharmacy->prescriptionCount, sizeof(int), 1, file) != 1) {
       printf("Failed to read prescription count.\n");
        return 0;
    }
    if (pharmacy->prescriptionCount > 0)
        pharmacy->prescriptions = loadPrescriptionsFromBinary(file, pharmacy->prescriptionCount, pharmacy->customers, pharmacy->customerCount, &pharmacy->stock);

    loadOrdersFromBinary(file, (const Employee**)pharmacy->employees, pharmacy->employeeCount, &pharmacy->orderHistory);
    printPharmacyDetails(pharmacy);
    return 1;
}
void loadPharmacyFromFile(FILE* file, Pharmacy* pharmacy) {
    initPharmacy(pharmacy);
    // Read the pharmacy name from the file
    readString(file, &pharmacy->name);
    loadAddress(&pharmacy->address, file);
    loadStock(file,&pharmacy->stock);
    fscanf(file, "%d\n", &pharmacy->employeeCount);
    if (pharmacy->employeeCount > 0)
        pharmacy->employees = loadEmployees(file, pharmacy->employeeCount);
    fscanf(file, "%d\n", &pharmacy->customerCount);
    if (pharmacy->customerCount > 0)
        pharmacy->customers = loadCustomers(file, pharmacy->customerCount);
    fscanf(file, "%d\n", &pharmacy->prescriptionCount);
    if (pharmacy->prescriptionCount > 0)
        pharmacy->prescriptions = loadPrescriptions(file, pharmacy->prescriptionCount, pharmacy->customers, pharmacy->customerCount, &pharmacy->stock);
    loadOrders(file, (const Employee**)pharmacy->employees, pharmacy->employeeCount, &pharmacy->orderHistory);
    printPharmacyDetails(pharmacy);
}

void saveDataToFile(char* filename, Pharmacy* pharmacy) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }
    savePharmacyToFile(file, pharmacy);
    fclose(file);
}

int saveDataToBinary(char* filename, Pharmacy* pharmacy) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return 0;
    }
    int result = savePharmacyToBinary(file, pharmacy);
    fclose(file);
    return result;
}

int loadDataFromFile(char* filename, Pharmacy* pharmacy) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return 0;
    }

    // Seek to the end of the file
    fseek(file, 0, SEEK_END);

    // If the position is 0, the file is empty
    if (ftell(file) == 0) {
        printf("File is empty.\n");
        fclose(file);
        return 0;
    }

    // Seek back to the start of the file
    fseek(file, 0, SEEK_SET);

    loadPharmacyFromFile(file, pharmacy);
    fclose(file);
    return 1;
}

int loadDataFromBinary(char* filename, Pharmacy* pharmacy) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return 0;
    }

    // Seek to the end of the file
    fseek(file, 0, SEEK_END);

    // If the position is 0, the file is empty
    if (ftell(file) == 0) {
        printf("File is empty.\n");
        fclose(file);
        return 0;
    }

    // Seek back to the start of the file
    fseek(file, 0, SEEK_SET);

    int result = loadPharmacyFromBinary(file, pharmacy);
    fclose(file);
    return result;
}

void freePharmacy(Pharmacy* pharmacy) {
    freeEmployees(pharmacy->employees, pharmacy->employeeCount);
    freeCustomers(pharmacy->customers, pharmacy->customerCount);
    freePrescriptions(pharmacy->prescriptions, pharmacy->prescriptionCount);
    freeStock(&pharmacy->stock);
    freeList(&pharmacy->orderHistory, &freeOrder);
}