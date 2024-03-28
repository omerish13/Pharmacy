#ifndef MEDICINE_H
#define MEDICINE_H

#include "Product.h"  // Make sure Product.h includes necessary headers like "general.h"

/**
 * Structure representing a medicine's information, extending the Product structure.
 */
typedef struct {
    Product product;            /**< Base Product structure */
    char* expireDate;           /**< Dynamically allocated expiration date string */
    int prescriptionRequired;   /**< Flag indicating if a prescription is required (0 = No, 1 = Yes) */
} Medicine;

/**
 * Initializes a Medicine structure with unique product code and other provided details.
 * @param medicine Pointer to the Medicine structure to initialize.
 */
void initMedicine(Medicine* medicine);

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
