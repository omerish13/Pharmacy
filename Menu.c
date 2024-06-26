#include "Menu.h"
#include <stdio.h>

void printMainMenu() {
    printf("\nMain Menu\n");
    printf("---------\n");
    printf("1. Prescription Management\n");
    printf("2. Stock Management\n");
    printf("3. Staff Management\n");
    printf("4. Order Management\n");
    printf("5. Show Menu\n");
    printf("-1. Exit\n");
    printf("Enter your choice: ");
}

void manageMainMenu(Pharmacy* pharmacy){
    int choice;
    do {
        printMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                managePrescriptions(pharmacy);  // Function to manage prescriptions
                break;
            case 2:
                menageStock(pharmacy);  // Function to manage stock
                break;
            case 3:
                manageStaff(pharmacy);  // Function to manage staff
                break;
            case 4:
                manageOrder(pharmacy);  // Function to manage the order
                break;
            case 5:
                showMenu(pharmacy);  // Function to show menu
                break;
            case -1:
                break;  // Exit the main menu
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != -1);  // Loop until the user exits the main menu
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

void manageOrder(Pharmacy* pharmacy) {
    Order* order = createNewOrderInteractive(pharmacy);  // Function to create a new order
    CHECK_ALLOC_VOID(order);

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
                break;  // Exit the mini menu after purchasing
            case 6:
                cancelOrder(order);
                break;  // Exit the mini menu after canceling
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5 && choice != 6);  // Loop until the order is either purchased or canceled
}

void printStockManagementMenu() {
    printf("\nStock Management Menu\n");
    printf("---------------------\n");
    printf("1. Add New Product\n");
    printf("2. Add New Medicine\n");
    printf("3. Show and Update Stock\n");
    printf("4. Sort Stock\n");
    printf("5. Find Product In Stock Using BSearch\n");
    printf("-1. Back to Main Menu\n");
    printf("Enter your choice: ");
}

void menageStock(Pharmacy* pharmacy) {
    int choice;
    do {
        printStockManagementMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addNewProductToStock(&pharmacy->stock);  // Function to add new products
                break;
            case 2:
                addNewMedicineToStock(&pharmacy->stock);  // Function to add new medicines
                break;
            case 3:
                showAndUpdateStock(pharmacy);  // Function to show and update stock
                break;
            case 4:
                sortProductInStock(&pharmacy->stock);  // Function to sort stock
                break;
            case 5:
                findProductInStockBSearch(&pharmacy->stock);  // Function to find product in stock using bsearch
                break;
            case -1:
                break;  // Exit the stock management menu
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != -1);  // Loop until the user exits the stock management menu
}


void printStaffManagementMenu() {
    printf("\nStaff Management Menu\n");
    printf("---------------------\n");
    printf("1. Add Employee\n");
    printf("2. Add Customer\n");
    printf("3. Remove Employee\n");
    printf("4. Raise Salary\n");
    printf("-1. Back to Main Menu\n");
    printf("Enter your choice: ");
}

void manageStaff(Pharmacy* pharmacy) {
    int choice;
    do {
        printStaffManagementMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addEmployeeInteractive(pharmacy);  // Function to add new employees
                break;
            case 2:
                addCustomerInteractive(pharmacy);  // Function to add new customers
                break;
            case 3:
                removeEmployeeInteractive(pharmacy);  // Function to remove employees
                break;
            case 4:
                raiseSalaryClient(pharmacy);  // Function to raise salary
                break;
            case -1:
                break;  // Exit the staff management menu
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != -1);  // Loop until the user exits the staff management menu
}


void printPrescriptionManagementMenu() {
    printf("\nPrescription Management Menu\n");
    printf("---------------------------\n");
    printf("1. Add New Prescription\n");
    printf("2. Show Prescriptions\n");
    printf("-1. Back to Main Menu\n");
    printf("Enter your choice: ");
}

void managePrescriptions(Pharmacy* pharmacy) {
    int choice;
    do {
        printPrescriptionManagementMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addNewPrescriptionToPharmacy(pharmacy);  // Function to add new prescriptions
                break;
            case 2:
                printPrescriptions(pharmacy->prescriptions, pharmacy->prescriptionCount);  // Function to show prescriptions
                break;
            case -1:
                break;  // Exit the prescription management menu
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != -1);  // Loop until the user exits the prescription management menu
}

void printShowMenu() {
    printf("\nShow Menu\n");
    printf("---------\n");
    printf("1. Show All Orders\n");
    printf("2. Show All Employees\n");
    printf("3. Show All Customers\n");
    printf("4. Show All Prescriptions\n");
    printf("5. Show All Stock\n");
    printf("6. Show Orders by Dates\n");
    printf("7. Show Orders by customer\n");
    printf("8. Show Pharmacy Information\n");
    printf("-1. Back to Main Menu\n");
    printf("Enter your choice: ");
}

void showMenu(Pharmacy* pharmacy) {
    int choice;
    do {
        printShowMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                printAllOrders(&pharmacy->orderHistory);  // Function to show all orders
                break;
            case 2:
                printAllEmployees(pharmacy);  // Function to show all employees
                break;
            case 3:
                printAllCustomers(pharmacy);  // Function to show all customers
                break;
            case 4:
                printPrescriptions(pharmacy->prescriptions, pharmacy->prescriptionCount);  // Function to show all prescriptions
                break;
            case 5:
                printStockDetails(&pharmacy->stock);  // Function to show all stock
                break;
            case 6:
                showOrdersHistoryByDate(&pharmacy->orderHistory);  // Function to show orders by dates
                break;
            case 7:
                showOrdersByCustomer(pharmacy);  // Function to show orders by customer
                break;
            case 8:
                printPharmacyDetails(pharmacy);  // Function to show pharmacy information
                break;
            case -1:
                break;  // Exit the show menu
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != -1);  // Loop until the user exits the show menu
}