#include "Medicine.h"
#include <string.h> 

void initMedicine(Medicine* medicine, const char* medicineID, int productCode) {
    // Initialize the base product part of the medicine with isMedicine flag set to true
    initProduct(&medicine->product, 1,productCode);  // Pass 1 for isMedicine to skip product type setting

    // Copy the medicineID to the Medicine structure
    strncpy(medicine->medicineID, medicineID, 6);
    medicine->medicineID[MEDICINE_ID_LENGTH] = '\0';  // Ensure null termination

    // Set medicine-specific details
    setMedicineExpireDate(medicine);
    setMedicinePrescriptionRequired(medicine);
}

void setMedicineExpireDate(Medicine* medicine) {
    printf("Enter expiration date (e.g., DD/MM/YYYY): ");
    initDate(&medicine->expireDate);
}

void setMedicinePrescriptionRequired(Medicine* medicine) {
    printf("Is a prescription required for this medicine? (0 = No, 1 = Yes): ");
    scanf("%d", &medicine->prescriptionRequired);
    clearInputBuffer();
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
    printf("Prescription Required: %s\n", med->prescriptionRequired ? "Yes" : "No");
}

int saveMedicineToBinary(FILE* file, const void* medicine) {
    const Medicine* med = (const Medicine*)medicine;
    // Save the base product details
    if (!saveProductToBinary(file, &med->product)) {
        return 0;
    }

    // Save medicine-specific details
    fwrite(med->medicineID, sizeof(char), MEDICINE_ID_LENGTH, file);
    saveDateToBinary(file, &med->expireDate);
    fwrite(&med->prescriptionRequired, sizeof(int), 1, file);

    return 1;
}

Medicine* loadMedicineFromBinary(FILE* file) {
    Medicine* medicine = (Medicine*)malloc(sizeof(Medicine));
    CHECK_ALLOC_STRUCT(medicine);

    // Load the base product details
    Product* product = loadProductFromBinary(file);
    if (product == NULL) {
        free(medicine);
        return NULL;
    }
    medicine->product = *product;

    // Load medicine-specific details
    if (fread(medicine->medicineID, sizeof(char), MEDICINE_ID_LENGTH, file) != MEDICINE_ID_LENGTH) {
        free(product);
        free(medicine);
        return NULL;
    }
    if (!loadDateFromBinary(&medicine->expireDate, file)) {
        free(product);
        free(medicine);
        return NULL;
    }
    if (fread(&medicine->prescriptionRequired, sizeof(int), 1, file) != 1) {
        free(product);
        free(medicine);
        return NULL;
    }

    return medicine;
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
