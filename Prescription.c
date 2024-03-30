#include "Prescription.h"
#include <string.h>
#include <time.h>

static int lastPrescriptionID = 0;  // For auto-incrementing the prescription ID

void initPrescription(Prescription* prescription, int customerID, const char* medicineID, Date expirationDate) {
    prescription->id = ++lastPrescriptionID;
    prescription->customerID = customerID;
    strncpy(prescription->medicineID, medicineID, 6);
    prescription->medicineID[6] = '\0';  // Ensure null-termination
    prescription->expirationDate = expirationDate;
    prescription->used = 0;  // The prescription is initially unused
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
