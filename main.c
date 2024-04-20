#include "Pharmacy.h"
#include <stdio.h>
#include <stdlib.h>

void printMainMenu() {
    printf("\nPharmacy Management System Main Menu\n");
    printf("------------------------------------\n");
    printf("1. Add New Prescription\n");
    printf("2. Add New Product\n");
    printf("3. Add New Medicine\n");
    printf("4. Create New Order\n");
    printf("5. Add Employee\n");
    printf("6. Add Customer\n");
    printf("7. Remove Employee\n");
    printf("8. Show and Update Stock\n");
    printf("9. Show Pharmacy Details\n");
    printf("-1. Exit\n");
    printf("Enter your choice: ");
}

void printOrderManagementMenu() {
    printf("\nOrder Management Menu\n");
    printf("---------------------\n");
    printf("1. Add Product/Medicine to Order\n");
    printf("2. Remove Product from Order\n");
    printf("3. Update Quantity of Product in Order\n");
    printf("4. Replace Employee\n");
    printf("5. Purchase Order\n");
    printf("6. Cancel Order\n");
    printf("Enter your choice: ");
}

void manageOrder(Pharmacy* pharmacy, Order* order) {
    int choice;
    do {
        printOrderManagementMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addProductOrMedicineToOrder(pharmacy, order);  // Function to add products/medicines
                break;
            case 2:
                removeProductFromOrderClient(order);  // Function to remove products/medicines
                break;
            case 3:
                updateProductQuantityOrder(pharmacy,order);  // Function to update quantities
                break;
            case 4:
                replaceEmployeeInOrder(pharmacy, order);  // Function to replace employee
                break;
            case 5:
                purchaseOrder(pharmacy, order);
                return;  // Exit the mini menu after purchasing
            case 6:
                cancelOrder(pharmacy, order->orderNumber);
                return;  // Exit the mini menu after canceling
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (1);  // Loop until the order is either purchased or canceled
}


void showAndUpdateStock(Pharmacy* pharmacy) {
    if (pharmacy->stock.products == NULL && pharmacy->stock.medicines == NULL) {
        printf("No products or medicines available in stock.\n");
        return;
    }
    printStockDetails(&pharmacy->stock);

    int productCode, newQuantity;
    printf("Enter Product Code to update stock quantity: ");
    scanf("%d", &productCode);
    printf("Enter new stock quantity for Product Code %d: ", productCode);
    scanf("%d", &newQuantity);

    updateStock(&pharmacy->stock, productCode, newQuantity);
}

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

    
    int choice;
    do {
        printMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addNewPrescriptionToPharmacy(&pharmacy);
                break;
            case 2:
                addNewProductToStock(&pharmacy.stock);
                break;
            case 3:
                addNewMedicineToStock(&pharmacy.stock);
                break;
            case 4: {
                Order* newOrder = createNewOrderInteractive(&pharmacy);
                if (newOrder == NULL) {
                    printf("Error creating new order. Please try again.\n");
                    break;
                }
                addToList(&pharmacy.openOrders, newOrder);  
                manageOrder(&pharmacy, newOrder);
                break;
            }
            case 5:
                addEmployeeInteractive(&pharmacy);
                break;
            case 6:
                addCustomerInteractive(&pharmacy);
                break;
            case 7:
                removeEmployeeInteractive(&pharmacy);
                break;
            case 8:
                showAndUpdateStock(&pharmacy);
                break;
            case 9:
                printPharmacyDetails(&pharmacy);
                break;
            case -1:
                printf("Exiting Pharmacy Management System.\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != -1);

    saveDataToFile("pharmacy.txt",&pharmacy);  // Save all data to file before exiting
    saveDataToBinary("pharmacy.bin",&pharmacy);  // Save all data to binary file before exiting
    freePharmacy(&pharmacy);  // Clean up resources
    return 0;
}
