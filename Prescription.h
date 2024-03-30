#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include "general.h"  // For general utilities like myGets
#include "Date.h"     // Include the Date struct definition
#include "Medicine.h"

/**
 * Structure representing a prescription's information.
 * 
 * Attributes:
 *  - id: Unique identifier for the prescription, automatically incremented.
 *  - customerID: Identifier for the customer to whom the prescription is issued.
 *  - medicineID: A string representing the unique ID associated with the medicine prescribed.
 *  - expirationDate: The date after which the prescription is no longer valid.
 *  - used: A flag indicating whether the prescription has been used (1) or not (0).
 */
typedef struct {
    int id;                  /**< Unique prescription ID, automatically incremented */
    int customerID;          /**< ID of the customer to whom the prescription is assigned */
    char medicineID[ID_LENGTH];      /**< Unique ID for the medicine, expected to be a 6-digit string */
    Date expirationDate;     /**< Expiration date of the prescription */
    int used;                /**< Flag indicating whether the prescription has been used (0 = No, 1 = Yes) */
} Prescription;


/**
 * Initializes a Prescription structure with provided details.
 * 
 * @param prescription Pointer to the Prescription structure to initialize.
 * @param customerID ID of the customer to whom the prescription will be issued.
 * @param medicineID String representing the unique ID of the prescribed medicine.
 * @param expirationDate Date structure representing the expiration date of the prescription.
 */
void initPrescription(Prescription* prescription, int customerID, const char* medicineID, Date expirationDate);

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


#endif // PRESCRIPTION_H
