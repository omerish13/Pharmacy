#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    Pharmacy pharmacy;
    int option;
    printf("Do you want to load data from file or binary file? (1 for Yes, 2 for binary): ");
    scanf("%d", &option);
    clearInputBuffer();
    if (option == 1) {
        if (!loadDataFromFile("pharmacy.txt", &pharmacy)) {
            printf("Error loading data from file. Initialize from client.\n");
            initPharmacyClient(&pharmacy);
        }
    } else if (option == 2) {
        if (!loadDataFromBinary("pharmacy.bin", &pharmacy)) {
            printf("Error loading data from binary file. Initialize from client.\n");
            initPharmacyClient(&pharmacy);
        }
    } else {
        printf("Invalid choice. Initialize from client.\n");
        initPharmacyClient(&pharmacy);
    }

    
    manageMainMenu(&pharmacy);  // Start the main menu

    saveDataToFile("pharmacy.txt",&pharmacy);  // Save all data to file before exiting
    saveDataToBinary("pharmacy.bin",&pharmacy);  // Save all data to binary file before exiting
    freePharmacy(&pharmacy);  // Clean up resources
    return 0;
}
