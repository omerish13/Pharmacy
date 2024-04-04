#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include "general.h"  // For general utilities like myGets
#include "Date.h"     // Include the Date struct definition
#include "Medicine.h"
#include "Customer.h"
#include "Stock.h"

/**
 * Structure representing a prescription's information.
 * 
 * Attributes:
 *  - id: Unique identifier for the prescription, automatically incremented.
 *  - customerID: Identifier for the customer to whom the prescription is issued.
 *  - medicineID: A string representing the unique ID associated with the medicine prescribed.
 *  - expirationDate: The date after which the prescription is no longer valid.
 *  - quantity: The amount of medications the customer can buy.
 *  - used: A flag indicating whether the prescription has been used (1) or not (0).
 */
typedef struct {
    int id;                            /**< Unique prescription ID, automatically incremented. */
    Customer* customer;                    /**< ID of the customer to whom the prescription is assigned. */
    Medicine* medicine;        /**< Unique ID for the medicine, expected to be a 6-digit string. */
    Date expirationDate;               /**< Expiration date of the prescription. */
    int quantity;                      /**< Quantity of medication allowed for purchase with this prescription. */
    int used;                          /**< Flag indicating whether the prescription has been used (0 = No, 1 = Yes). */
} Prescription;



/**
 * Initializes a Prescription structure with the provided details.
 * Sets up a new prescription with a unique ID, customer ID, medicine ID, expiration date, and allowed medication quantity.
 *
 * @param prescription Pointer to the Prescription structure to be initialized.
 * @param customerID The ID of the customer for whom the prescription is issued.
 * @param medicineID The unique identifier for the medicine prescribed.
 * @param expirationDate The expiration date of the prescription.
 * @param quantity The quantity of medication the customer is allowed to purchase with this prescription.
 */
void initPrescription(Prescription* prescription, Customer* customers,int numCustomers, int customerID, const char* medicineID,Stock* stock, Date expirationDate, int quantity);

/**
 * Determines if a given customer has a valid (unused and unexpired) prescription
 * for a specified medicine, based on an array of prescriptions.
 * 
 * @param prescriptions Array of Prescription structures to search through.
 * @param numPrescriptions Number of prescriptions in the array.
 * @param customerID The ID of the customer to check for a valid prescription.
 * @param medicineID The unique ID of the medicine to check in the prescription.
 * @return 1 if a valid prescription is found, 0 otherwise.
 */
int customerHasValidPrescription(const Prescription* prescriptions, int numPrescriptions, int customerID, const char* medicineID);

/**
 * Prints the details of a prescription, including information about the customer and the medicine prescribed.
 *
 * @param prescription Pointer to the Prescription structure to be printed.
 * @param customers Array of Customer structures.
 * @param numCustomers Total number of customers in the array.
 * @param stock Pointer to the Stock structure containing an array of products.
 */

void printPrescription(const Prescription* prescription, const Customer* customers, int numCustomers, const Stock* stock);

/**
 * Saves the details of a prescription to a file, including the customer ID, medicine ID, expiration date, quantity, and usage status.
 *
 * @param prescription Pointer to the Prescription structure to save.
 * @param file Pointer to the file where the prescription details are to be saved.
 */
void savePrescription(const Prescription* prescription, FILE* file);

/**
 * Loads the details of a prescription from a file, including the customer ID, medicine ID, expiration date, quantity, and usage status.
 *
 * @param file Pointer to the file from which the prescription details are to be loaded.
 * @param customers Array of Customer structures.
 * @param numCustomers Total number of customers in the array.
 * @param stock Pointer to the Stock structure containing an array of products.
 * @return Pointer to the loaded Prescription structure.
 */
Prescription* loadPrescription(FILE* file, const Customer* customers, int numCustomers, const Stock* stock);

/**
 * Frees the memory allocated for a Prescription object.
 *
 * @param prescription The Prescription object to free.
 */
void freePrescription(Prescription* prescription);

/**
 * Frees the memory allocated for an array of Prescription objects.
 *
 * @param prescriptions Array of Prescription objects to free.
 * @param numPrescriptions Number of Prescription objects in the array.
 */
void freePrescriptions(Prescription* prescriptions, int numPrescriptions);

#endif // PRESCRIPTION_H
