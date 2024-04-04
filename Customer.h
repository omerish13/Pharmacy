#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "general.h"  // Include for CHECK_ALLOC and myGets
#include "Person.h"   // Include the Person struct definition

/**
 * Structure representing a customer's basic information.
 */
typedef struct {
    Person person; /**< Base Person structure */
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
 * Finds a customer by their unique ID.
 *
 * @param customers Array of Customer structures.
 * @param numCustomers Total number of customers in the array.
 * @param customerID The unique ID of the customer to find.
 * @return Pointer to the Customer structure if found, NULL otherwise.
 */
Customer* findCustomerByID(const Customer* customers, int numCustomers, int customerID);

/**
 * Prints the details of a customer in a formatted manner.
 * @param customer Pointer to the Customer structure whose details are being printed.
 */
void printCustomerDetails(const Customer* customer);

/**
 * Frees the dynamically allocated memory for the customer's name.
 * @param customer Pointer to the Customer structure to free.
 */
void freeCustomer(Customer* customer);

/**
 * Frees the dynamically allocated memory for an array of customers.
 * @param customers Array of Customer structures to free.
 * @param numCustomers Number of customers in the array.
 */
void freeCustomers(Customer* customers, int numCustomers);

#endif // CUSTOMER_H
