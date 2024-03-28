#include "Prescription.h"

static int lastPrescriptionID = 0;

void initPrescription(Prescription* prescription) {
    prescription->id = ++lastPrescriptionID;  // Auto-increment ID
    setPrescriptionMedication(prescription);
    setPrescriptionDosage(prescription);
    setPrescriptionInstructions(prescription);
    setPrescriptionExpirationDate(prescription);
}

void setPrescriptionMedication(Prescription* prescription) {
    char buffer[BUFFER_SIZE];
    printf("Enter medication name: ");
    myGets(buffer, BUFFER_SIZE);
    prescription->medication = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(prescription->medication);
    strcpy(prescription->medication, buffer);
}

void setPrescriptionDosage(Prescription* prescription) {
    char buffer[BUFFER_SIZE];
    printf("Enter dosage information: ");
    myGets(buffer, BUFFER_SIZE);
    prescription->dosage = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(prescription->dosage);
    strcpy(prescription->dosage, buffer);
}

void setPrescriptionInstructions(Prescription* prescription) {
    char buffer[BUFFER_SIZE];
    printf("Enter instructions for use: ");
    myGets(buffer, BUFFER_SIZE);
    prescription->instructions = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(prescription->instructions);
    strcpy(prescription->instructions, buffer);
}

void setPrescriptionExpirationDate(Prescription* prescription) {
    printf("Setting expiration date:\n");
    initDate(&prescription->expirationDate);  // This function needs to prompt for day, month, and year
}

void printPrescriptionDetails(const Prescription* prescription) {
    printf("Prescription ID: %d\n", prescription->id);
    printf("Medication: %s\n", prescription->medication);
    printf("Dosage: %s\n", prescription->dosage);
    printf("Instructions: %s\n", prescription->instructions);
    // Assuming printDate function exists to print Date in a formatted manner
    printf("Expiration Date: ");
    printDate(&prescription->expirationDate);
}
