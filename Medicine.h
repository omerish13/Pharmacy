#ifndef MEDICINE_H
#define MEDICINE_H

#include "Product.h"  
#include "Date.h"     
#define ID_LENGTH 7

/**
 * Structure representing a medicine's information, extending the Product structure.
 * Includes a unique medicineID.
 */
typedef struct {
    Product product;            /**< Base Product structure */
    char medicineID[ID_LENGTH];         /**< Unique medicine ID, a 6-digit string */
    Date expireDate;           /**< Dynamically allocated expiration date string */
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

/**
 * Saves the details of a medicine to a file, including product details and medicine-specific information.
 * @param file Pointer to the file where the medicine details are to be saved.
 * @param medicine Pointer to the Medicine structure to save.
 */
void saveMedicine(FILE* file, const Medicine* medicine);

/**
 * Loads the details of a medicine from a file, including product details and medicine-specific information.
 * @param file Pointer to the file from which the medicine details are to be loaded.
 * @return Pointer to the loaded Medicine structure.
 */
Medicine* loadMedicine(FILE* file);

/**
 * Frees the dynamically allocated memory for the medicine's product details.
 * @param medicine Pointer to the Medicine structure to free.
 */
void freeMedicine(Medicine* medicine);



#endif // MEDICINE_H
