#include "Prescription.h"
#include <string.h>
#include <time.h>

static int lastPrescriptionID = 0;  // For auto-incrementing the prescription ID

void initPrescription(Prescription* prescription, Customer* customers, int numCustomers, int customerID, const char* medicineID,Stock* stock, Date expirationDate, int quantity) {
    prescription->id = ++lastPrescriptionID;  // Auto-increment the prescription ID
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

void savePrescription(const Prescription* prescription, FILE* file) {
    fprintf(file, "%d %d %s %d %d ", prescription->id, prescription->customer->id, prescription->medicine->medicineID,
            prescription->quantity, prescription->used);
    saveDate(file,&prescription->expirationDate);
    fprintf(file, "\n");
}

Prescription* loadPrescription(FILE* file,Customer* customers, int numCustomers,Stock* stock) {
    Prescription* prescription = (Prescription*)malloc(sizeof(Prescription));
    CHECK_ALLOC(prescription);

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

