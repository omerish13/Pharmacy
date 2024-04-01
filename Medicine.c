#include "Medicine.h"
#include <string.h> 

void initMedicine(Medicine* medicine, const char* medicineID) {
    // Initialize the base product part of the medicine with isMedicine flag set to true
    initProduct(&medicine->product, 1);  // Pass 1 for isMedicine to skip product type setting

    // Copy the medicineID to the Medicine structure
    strncpy(medicine->medicineID, medicineID, 6);
    medicine->medicineID[6] = '\0';  // Ensure null termination

    // Set medicine-specific details
    setMedicineExpireDate(medicine);
    setMedicinePrescriptionRequired(medicine);
}

void setMedicineExpireDate(Medicine* medicine) {
    char buffer[BUFFER_SIZE];
    printf("Enter expiration date (e.g., YYYY-MM-DD): ");
    myGets(buffer);
    medicine->expireDate = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(medicine->expireDate);
    strcpy(medicine->expireDate, buffer);
}

void setMedicinePrescriptionRequired(Medicine* medicine) {
    char buffer[BUFFER_SIZE];
    printf("Is a prescription required? (0 = No, 1 = Yes): ");
    myGets(buffer);
    medicine->prescriptionRequired = atoi(buffer);
}

void printMedicineDetails(const Medicine* medicine) {
    // Print base product details
    printProductDetails(&medicine->product);

    // Print medicine-specific details
    printf("Expiration Date: %s\n", medicine->expireDate);
    printf("Prescription Required: %s\n", medicine->prescriptionRequired ? "Yes" : "No");
}
