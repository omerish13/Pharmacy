#ifndef MEDICINE_H
#define MEDICINE_H

#include "Product.h"  // Assuming Product structure is defined
#define ID_LENGTH 7

/**
 * Structure representing a medicine's information, extending the Product structure.
 * Includes a unique medicineID.
 */
typedef struct {
    Product product;            /**< Base Product structure */
    char medicineID[ID_LENGTH];         /**< Unique medicine ID, a 6-digit string */
    char* expireDate;           /**< Dynamically allocated expiration date string */
    int prescriptionRequired;   /**< Flag indicating if a prescription is required (0 = No, 1 = Yes) */
} Medicine;

/**
 * Initializes a Medicine structure with unique product code, medicineID, and other provided details.
 * @param medicine Pointer to the Medicine structure to initialize.
 * @param medicineID Unique ID for the medicine, expected to be a 6-digit string.
 */
void initMedicine(Medicine* medicine, const char* medicineID);

/**
 * Sets the expiration date of a medicine after dynamically allocating memory for it.
 * @param medicine Pointer to the Medicine structure whose expiration date is being set.
 */
void setMedicineExpireDate(Medicine* medicine);

/**
 * Sets whether a prescription is required for the medicine based on the user's input.
 * @param medicine Pointer to the Medicine structure to set the prescription requirement flag.
 */
void setMedicinePrescriptionRequired(Medicine* medicine);

/**
 * Prints the details of the medicine in a formatted manner, including product details and medicine-specific information.
 * @param medicine Pointer to the Medicine structure whose details are being printed.
 */
void printMedicineDetails(const Medicine* medicine);

#endif // MEDICINE_H
