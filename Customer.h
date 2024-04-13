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
} Customer;

/**
 * Initializes a Customer object with the given last customer ID.
 *
 * @param customer A pointer to the Customer object to be initialized.
 * @param lastCustomerID The last customer ID to be assigned to the Customer.
 */
void initCustomer(Customer* customer, int lastCustomerID);

/**
 * Finds a customer by their unique ID.
 *
 * @param customers Array of Customer structures.
 * @param numCustomers Total number of customers in the array.
 * @param customerID The unique ID of the customer to find.
 * @return Pointer to the Customer structure if found, NULL otherwise.
 */
Customer* findCustomerByID(Customer* customers, int numCustomers, int customerID);

/**
 * Prints the details of a customer in a formatted manner.
 * @param customer Pointer to the Customer structure whose details are being printed.
 */
void printCustomerDetails(const Customer* customer);

/**
 * Saves a customer's details to a binary file.
 * @param file Pointer to the file to save the customer details to.
 * @param customer Pointer to the Customer structure to save.
 * @return 1 if the save was successful, 0 otherwise.
 */
int saveCustomerToBinary(FILE* file, const Customer* customer);

/**
 * Loads a customer's details from a binary file.
 * @param customer Pointer to the Customer structure to load the details into.
 * @param file Pointer to the file to load the customer details from.
 * @return 1 if the load was successful, 0 otherwise.
 */
int loadCustomerFromBinary(Customer* customer, FILE* file);
/**
 * Save customer details from the user, including name and age.
 * @param customer Pointer to the Customer structure to store the details.
 */
void saveCustomer(FILE* file, const Customer* customer);

/**
 * Reads customer details from a file, including name and age.
 * @param customer Pointer to the Customer structure to store the details.
 */
Customer* loadCustomer(FILE* file);

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
