#include "Prescription.h"
#include <string.h>
#include <time.h>

static int lastPrescriptionID = 0;  // For auto-incrementing the prescription ID

void initPrescription(Prescription* prescription, int customerID, const char* medicineID, Date expirationDate, int quantity) {
    prescription->id = ++lastPrescriptionID;  // Auto-increment the prescription ID
    prescription->customerID = customerID;
    
    // Ensure the medicine ID is copied safely, assuming medicineID has a fixed size
    strncpy(prescription->medicineID, medicineID, sizeof(prescription->medicineID) - 1);
    prescription->medicineID[sizeof(prescription->medicineID) - 1] = '\0';  // Null-terminate
    
    prescription->expirationDate = expirationDate;  // Assign the expiration date
    prescription->quantity = quantity;  // Assign the allowed quantity of medication
    prescription->used = 0;  // Initially mark the prescription as unused
}

int customerHasValidPrescription(const Prescription* prescriptions, int numPrescriptions, int customerID, const char* medicineID) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date currentDate = {tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900};  // Current date

    for (int i = 0; i < numPrescriptions; ++i) {
        if (prescriptions[i].customerID == customerID &&
            strcmp(prescriptions[i].medicineID, medicineID) == 0 &&
            !prescriptions[i].used &&
            compareDates(&prescriptions[i].expirationDate, &currentDate) > 0) {  
            return 1;
        }
    }

    // No valid prescription found
    return 0;
}

void printPrescription(const Prescription* prescription, const Customer* customers, int numCustomers, const Stock* stock) {
    Customer* customer = findCustomerByID(customers, numCustomers, prescription->customerID);
    Medicine* medicine = findMedicineByID(stock, prescription->medicineID);

    if (customer && medicine) {
        printf("Prescription ID: %d\n", prescription->id);
        printf("Customer: %s (ID: %d)\n", customer->name, customer->id);
        printf("Medicine: %s (ID: %s)\n", medicine->product.name, medicine->medicineID);
        // Additional details can be printed here if needed
    } else {
        printf("Error: Customer or Medicine not found for the prescription.\n");
    }
}

void freePrescription(Prescription* prescription) {
    prescription->id = 0;
    prescription->customerID = 0;
    prescription->medicineID[0] = '\0';
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

