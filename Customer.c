#include "Customer.h"


void initCustomer(Customer* customer, int lastCustomerID) {
    initPerson(&customer->person);
    customer->id = lastCustomerID;  // Auto-increment the customer ID for each new customer
}

// Comparator for customers by ID
int compareCustomerByID(const void* a, const void* b) {
    const Customer* custA = (const Customer*)a;
    const Customer* custB = (const Customer*)b;
    return (custA->id - custB->id);
}

Customer* findCustomerByID(Customer* customers, int numCustomers, int customerID) {
    // Create a temporary Customer for the search
    Customer tmp;
    tmp.id = customerID;

    qsort(customers, numCustomers, sizeof(Customer), compareCustomerByID);

    // Search the array
    Customer* found = (Customer*)bsearch(&tmp, customers, numCustomers, sizeof(Customer), compareCustomerByID);

    // Return the found Customer, or NULL if not found
    return found;
}


void printCustomerDetails(const Customer* customer) {
    printPersonDetails(&customer->person);
    printf("Customer ID: %d\n", customer->id);
}

int saveCustomerToBinary(FILE* file, const Customer* customer) {
    return savePersonToBinary(file, &customer->person) && fwrite(&customer->id, sizeof(int), 1, file) == 1;
}

int loadCustomerFromBinary(Customer* customer, FILE* file) {
    return loadPersonFromBinary(&customer->person, file) && fread(&customer->id, sizeof(int), 1, file) == 1;
}

void saveCustomer(FILE* file, const Customer* customer) {
    savePerson(file,&customer->person);
    fprintf(file, "%d\n", customer->id);
}

Customer* loadCustomer(FILE* file) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    CHECK_ALLOC_STRUCT(customer);

    loadPerson(&customer->person, file);
    fscanf(file, "%d\n", &customer->id);
    return customer;
}

void freeCustomer(Customer* customer) {
    freePerson(&customer->person);
}

void freeCustomers(Customer* customers, int numCustomers) {
    for (int i = 0; i < numCustomers; i++) {
        freeCustomer(&customers[i]);
    }
    free(customers);
    customers = NULL;
}
