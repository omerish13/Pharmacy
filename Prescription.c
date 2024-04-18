#include "Prescription.h"
#include <string.h>
#include <time.h>

void initPrescription(Prescription* prescription, Customer* customers, int numCustomers, int customerID, const char* medicineID,Stock* stock, Date expirationDate, int quantity, int prescriptionID) {
    prescription->id = prescriptionID;  // Auto-increment the prescription ID
    prescription->customer = findCustomerByID(customers, numCustomers, customerID);
    
    prescription->medicine = findMedicineByID(stock, medicineID);
    
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
            strcmp(prescriptions[i].medicine->medicineID, medicineID) == 0 &&
            !prescriptions[i].used &&
            compareDates(&prescriptions[i].expirationDate, &currentDate) > 0) {  
            return 1;
        }
    }

    // No valid prescription found
    return 0;
}

void printPrescription(const Prescription* prescription) {

    printf("Prescription ID: %d", prescription->id);
    printf("Customer: %s (ID: %d)", prescription->customer->person.name, prescription->customer->id);
    printf("Medicine: %s (ID: %s)\n", prescription->medicine->product.name, prescription->medicine->medicineID);
    // Additional details can be printed here if needed
}

void printPrescriptions(const Prescription* prescriptions, int numPrescriptions) {
    for (int i = 0; i < numPrescriptions; i++) {
        printPrescription(&prescriptions[i]);
    }
}

int savePrescriptionToBinary(const Prescription* prescription, FILE* file) {
    if (fwrite(&prescription->id, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(&prescription->customer->id, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(prescription->medicine->medicineID, sizeof(char), ID_LENGTH, file) != ID_LENGTH) {
        return 0;
    }
    if (fwrite(&prescription->quantity, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(&prescription->used, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (!saveDateToBinary(file, &prescription->expirationDate)) {
        return 0;
    }
    return 1;
}

int loadPrescriptionFromBinary(Prescription* prescription, FILE* file, Customer* customers, int numCustomers, Stock* stock) {
    if (fread(&prescription->id, sizeof(int), 1, file) != 1) {
        return 0;
    }
    int customerID;
    if (fread(&customerID, sizeof(int), 1, file) != 1) {
        return 0;
    }
    char medicineID[ID_LENGTH];
    if (fread(medicineID, sizeof(char), ID_LENGTH, file) != ID_LENGTH) {
        return 0;
    }
    if (fread(&prescription->quantity, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fread(&prescription->used, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (!loadDateFromBinary(&prescription->expirationDate, file)) {
        return 0;
    }
    prescription->customer = findCustomerByID(customers, numCustomers, customerID);
    prescription->medicine = findMedicineByID(stock, medicineID);

    return 1;
}

void savePrescription(const Prescription* prescription, FILE* file) {
    fprintf(file, "%d %d %s %d %d ", prescription->id, prescription->customer->id, prescription->medicine->medicineID,
            prescription->quantity, prescription->used);
    saveDate(file,&prescription->expirationDate);
    fprintf(file, "\n");
}

Prescription* loadPrescription(FILE* file,Customer* customers, int numCustomers,Stock* stock) {
    Prescription* prescription = (Prescription*)malloc(sizeof(Prescription));
    CHECK_ALLOC_STRUCT(prescription);

    fscanf(file, "%d %d %s %d %d ", &prescription->id, &prescription->customer->id, prescription->medicine->medicineID,
           &prescription->quantity, &prescription->used);
    loadDate(file, &prescription->expirationDate);

    prescription->customer = findCustomerByID(customers, numCustomers, prescription->customer->id);
    prescription->medicine = findMedicineByID(stock, prescription->medicine->medicineID);

    return prescription;
}


    

void freePrescription(Prescription* prescription) {
    prescription->id = 0;
    freeCustomer(prescription->customer);
    freeMedicine(prescription->medicine);
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

