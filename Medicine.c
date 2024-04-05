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
    printf("Enter expiration date (e.g., YYYY-MM-DD): ");
    initDate(&medicine->expireDate);
}

void setMedicinePrescriptionRequired(Medicine* medicine) {
    char buffer[BUFFER_SIZE];
    printf("Is a prescription required? (0 = No, 1 = Yes): ");
    myGets(buffer);
    medicine->prescriptionRequired = atoi(buffer);
}

void printMedicineInStock(const void* item) {
    const Medicine* medicine = (const Medicine*)item;
    if (medicine->product.stockQuantity > 0) {
        printMedicineDetails(medicine);
    }
}

void printMedicineDetails(const void* medicine) {
    const Medicine* med = (const Medicine*)medicine;
    // Print base product details
    printProductDetails(&med->product);

    // Print medicine-specific details
    printDate(&med->expireDate);
    printf("\nPrescription Required: %s\n", med->prescriptionRequired ? "Yes" : "No");
}

void saveMedicine(FILE* file, const void* medicine) {
    const Medicine* med = (const Medicine*)medicine;
    // Save the base product details
    saveProduct(file, &med->product);

    // Save medicine-specific details
    fprintf(file, "%s\n", med->medicineID);
    saveDate(file, &med->expireDate);
    fprintf(file, "%d\n", med->prescriptionRequired);
}

Medicine* loadMedicine(FILE* file) {
    Medicine* medicine = (Medicine*)malloc(sizeof(Medicine));
    CHECK_ALLOC_STRUCT(medicine);

    // Load the base product details
    medicine->product = *loadProduct(file);

    // Load medicine-specific details
    fscanf(file, "%s", medicine->medicineID);
    loadDate(file, &medicine->expireDate);
    fscanf(file, "%d", &medicine->prescriptionRequired);

    return medicine;
}

void freeMedicine(void* medicine) {
    Medicine* med = (Medicine*)medicine;
    freeProduct(med);
}
