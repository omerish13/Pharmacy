#include "Customer.h"

static int lastCustomerID = 0;  // Static variable to keep track of the last used customer ID

void initCustomer(Customer* customer) {
    customer->id = ++lastCustomerID;  // Auto-increment the customer ID for each new customer
    setCustomerName(customer);
}

void setCustomerName(Customer* customer) {
    char buffer[BUFFER_SIZE];
    printf("Enter customer name: ");
    myGets(buffer);
    customer->name = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(customer->name);
    strcpy(customer->name, buffer);
}

Customer* findCustomerByID(const Customer* customers, int numCustomers, int customerID) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == customerID) {
            return &customers[i];
        }
    }
    return NULL;  // Customer not found
}


void printCustomerDetails(const Customer* customer) {
    printf("Customer ID: %d\n", customer->id);
    printf("Name: %s\n", customer->name);
}
