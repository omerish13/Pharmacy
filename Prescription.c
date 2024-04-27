#include "Prescription.h"
#include <string.h>
#include <time.h>

void initPrescription(Prescription* prescription, Customer* customers, int numCustomers, int customerID, const char* medicineID,Stock* stock, Date expirationDate, int quantity, int prescriptionID) {
    prescription->id = prescriptionID;  // Auto-increment the prescription ID
    prescription->customer = findCustomerByID(customers, numCustomers, customerID);
    strncpy(prescription->medicineID, medicineID, MEDICINE_ID_LENGTH);  // Copy the medicine ID
    prescription->expirationDate = expirationDate;  // Assign the expiration date
    prescription->quantity = quantity;  // Assign the allowed quantity of medication
    prescription->used = 0;  // Initially mark the prescription as unused
}

int customerHasValidPrescription(const Prescription* prescriptions, int numPrescriptions, int customerID, const char* medicineID) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date currentDate = {tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900};  // Current date

    for (int i = 0; i < numPrescriptions; ++i) {
        if (prescriptions[i].customer->id == customerID &&
            strcmp(prescriptions[i].medicineID, medicineID) == 0 &&
            !prescriptions[i].used &&
            compareDates(&prescriptions[i].expirationDate, &currentDate) > 0) {  
            return 1;
        }
    }

    // No valid prescription found
    return 0;
}

void printPrescription(const Prescription* prescription) {

    printf("Prescription ID: %d ", prescription->id);
    printCustomerDetails(prescription->customer);
    printf("Medicine ID: %s\n",prescription->medicineID);
    printf("Expiration Date: ");
    printDate(&prescription->expirationDate);
    printf("Quantity: %d, ", prescription->quantity);
    printf("Used: %s\n", prescription->used ? "Yes" : "No");
}

void printPrescriptions(const Prescription* prescriptions, int numPrescriptions) {
    for (int i = 0; i < numPrescriptions; i++) {
        printPrescription(&prescriptions[i]);
    }
}

int savePrescriptionToBinary(const Prescription* prescription, FILE* file) {
    return fwrite(&prescription->id, sizeof(int), 1, file) == 1 &&
           fwrite(&prescription->customer->id, sizeof(int), 1, file) == 1 &&
           fwrite(prescription->medicineID, sizeof(char), MEDICINE_ID_LENGTH, file) == MEDICINE_ID_LENGTH &&
           fwrite(&prescription->quantity, sizeof(int), 1, file) == 1 &&
           fwrite(&prescription->used, sizeof(int), 1, file) == 1 &&
           saveDateToBinary(file,&prescription->expirationDate);
}

int loadPrescriptionFromBinary(Prescription* prescription, FILE* file, Customer* customers, int numCustomers, Stock* stock) {
    if (fread(&prescription->id, sizeof(int), 1, file) != 1) {
        return 0;
    }
    int customerID;
    if (fread(&customerID, sizeof(int), 1, file) != 1) {
        return 0;
    }
    prescription->customer = findCustomerByID(customers, numCustomers, customerID);
    if (fread(prescription->medicineID, sizeof(char), MEDICINE_ID_LENGTH, file) != MEDICINE_ID_LENGTH) {
        return 0;
    }
    if (fread(&prescription->quantity, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fread(&prescription->used, sizeof(int), 1, file) != 1) {
        return 0;
    }
    loadDateFromBinary(&prescription->expirationDate, file);
    return 1;
}

void savePrescription(const Prescription* prescription, FILE* file) {
    fprintf(file, "%d %d\n", prescription->id, prescription->customer->id);
    fprintf(file, "%s\n", prescription->medicineID);
    fprintf(file, "%d %d\n", prescription->quantity, prescription->used);
    saveDate(file,&prescription->expirationDate);
}

Prescription* loadPrescription(FILE* file,Customer* customers, int numCustomers,Stock* stock) {
    Prescription* prescription = (Prescription*)malloc(sizeof(Prescription));
    CHECK_ALLOC_STRUCT(prescription);

    int customerID;
    fscanf(file, "%d %d\n", &prescription->id, &customerID);
    printf("Customer ID: %d\n", customerID);
    fscanf(file, "%s\n", prescription->medicineID);
    fscanf(file, "%d %d\n", &prescription->quantity, &prescription->used);
    loadDate(file,&prescription->expirationDate);
    prescription->customer = findCustomerByID(customers, numCustomers, customerID);
    return prescription;
}
    
void freePrescription(Prescription* prescription) {
    prescription->id = 0;
    freeCustomer(prescription->customer);
    freeMedicine(prescription->medicineID);
    prescription->expirationDate.day = 0;
    prescription->expirationDate.month = 0;
    prescription->expirationDate.year = 0;
    prescription->quantity = 0;
    prescription->used = 0;
}

void freePrescriptions(Prescription* prescriptions, int numPrescriptions) {
    for (int i = 0; i < numPrescriptions; i++) {
        freePrescription(&prescriptions[i]);
    }
    free(prescriptions);
    prescriptions = NULL;
}

