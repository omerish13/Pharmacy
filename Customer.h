#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "general.h"  // Include for CHECK_ALLOC and myGets

/**
 * Structure representing a customer's basic information.
 */
typedef struct {
    int id;        /**< Unique customer ID, automatically incremented */
    char* name;    /**< Dynamically allocated customer name */
} Customer;

/**
 * Initializes a Customer structure with a unique ID and other provided details.
 * @param customer Pointer to the Customer structure to initialize.
 */
void initCustomer(Customer* customer);

/**
 * Sets the name of a customer after dynamically allocating memory for it.
 * @param customer Pointer to the Customer structure whose name is being set.
 */
void setCustomerName(Customer* customer);

/**
 * Prints the details of a customer in a formatted manner.
 * @param customer Pointer to the Customer structure whose details are being printed.
 */
void printCustomerDetails(const Customer* customer);

#endif // CUSTOMER_H