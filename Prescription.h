#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include "general.h"  // For general utilities like myGets
#include "Date.h"     // Include the Date struct definition

/**
 * Structure representing a prescription's information, including an expiration date.
 */
typedef struct {
    int id;              /**< Unique prescription ID, automatically incremented */
    char* medication;    /**< Dynamically allocated medication name */
    char* dosage;        /**< Dynamically allocated dosage information */
    char* instructions;  /**< Dynamically allocated instructions for use */
    Date expirationDate; /**< Expiration date using the Date struct */
} Prescription;

/**
 * Initializes a Prescription structure with a unique ID and prompts for other details.
 * @param prescription Pointer to the Prescription structure to initialize.
 */
void initPrescription(Prescription* prescription);

/**
 * Prompts for and sets the medication name.
 * @param prescription Pointer to the Prescription structure.
 */
void setPrescriptionMedication(Prescription* prescription);

/**
 * Prompts for and sets the dosage information.
 * @param prescription Pointer to the Prescription structure.
 */
void setPrescriptionDosage(Prescription* prescription);

/**
 * Prompts for and sets the instructions for use.
 * @param prescription Pointer to the Prescription structure.
 */
void setPrescriptionInstructions(Prescription* prescription);

/**
 * Prompts for and sets the expiration date from individual date components.
 * @param prescription Pointer to the Prescription structure.
 */
void setPrescriptionExpirationDate(Prescription* prescription);

/**
 * Prints the details of the prescription, including the expiration date.
 * @param prescription Pointer to the Prescription structure.
 */
void printPrescriptionDetails(const Prescription* prescription);

#endif // PRESCRIPTION_H
