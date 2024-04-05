#include "Customer.h"

static int lastCustomerID = 0;  // Static variable to keep track of the last used customer ID

void initCustomer(Customer* customer) {
    initPerson(&customer->person);
    customer->id = ++lastCustomerID;  // Auto-increment the customer ID for each new customer
}

Customer* findCustomerByID(Customer* customers, int numCustomers, int customerID) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == customerID) {
            return &customers[i];
        }
    }
    return NULL;  // Customer not found
}


void printCustomerDetails(const Customer* customer) {
    printPersonDetails(&customer->person);
    printf("Customer ID: %d\n", customer->id);
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
