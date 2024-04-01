#include "Stock.h"
#include <stdio.h>
#include <stdlib.h>

void initStock(Stock* stock) {
    initList(&stock->products);
    initList(&stock->medicines);
}

void showAvailableProducts(const Stock* stock) {
    /**
     * Displays all available products in the stock, including medicines.
     */
    printf("Available Products:\n");
    traverseLinkedList(&stock->products, printProduct);  // printProduct is a callback function
    printf("Available Medicines:\n");
    traverseLinkedList(&stock->medicines, printMedicineDetails);  // printMedicine is a callback function
}


// Comparator for medicines by ID
int compareMedicineByID(const void* a, const void* b) {
    const Medicine* medA = *(const Medicine**)a;
    const Medicine* medB = *(const Medicine**)b;
    return strcmp(medA->medicineID, medB->medicineID);
}


Product* findProduct(const Stock* stock, int code) {
    ListNode* node = stock->products.head->next;
    Product* tmp;
    for (int i = 0; i < stock->products.size; ++i) {
        tmp = (Product*)(node->item);
        if (code == tmp->code)
            return tmp;
        node = node->next;
    }
    return NULL;  // Product not found
}

Medicine* findMedicineByID(const Stock* stock, const char* medicineID)
{
    Medicine* temp = (Medicine*)malloc(sizeof(Medicine));
    CHECK_ALLOC(temp);
    *temp->medicineID = strdup(medicineID);

    qsort(&stock->medicines,stock->medicines.size,sizeof(Medicine*),compareMedicineByID);
    return (Medicine*)bsearch(temp,&stock->medicines,stock->medicines.size,sizeof(Medicine),compareMedicineByID);
}

void addNewProductToStock(Stock* stock) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    if (newProduct == NULL) {
        printf("Memory allocation failed for new product.\n");
        return;
    }
    
    initProduct(newProduct, 0);  // 0 indicating this is not a medicine

    // Add the new product to the products list
    addToList(&stock->products, newProduct);
}

void addNewMedicineToStock(Stock* stock) {
    Medicine* existingMedicine = NULL;
    char medicineID[ID_LENGTH];

    do {
        printf("Enter unique Medicine ID: ");
        scanf("%6s", medicineID);  // Get medicine ID from user

        // Use findMedicineByID to check if a medicine with the given ID already exists
        existingMedicine = findMedicineByID(stock, medicineID);

        if (existingMedicine != NULL) {
            printf("A medicine with the ID %s already exists in stock. Please enter a different ID.\n", medicineID);
        }
    } while (existingMedicine != NULL);  // Repeat until a unique ID is provided

    // Proceed to add new medicine if no existing medicine with the same ID is found
    Medicine* newMedicine = (Medicine*)malloc(sizeof(Medicine));
    if (newMedicine == NULL) {
        printf("Memory allocation failed for new medicine.\n");
        return;
    }

    // Initialize new medicine with the provided ID
    initMedicine(newMedicine, medicineID);

    // Add the new medicine to the medicines list
    addToList(&stock->medicines, newMedicine);
}


void printStockDetails(const Stock* stock) {
    printf("Available Products:\n");
    traverseLinkedList(&stock->products, printProduct);
    printf("Available Medicines:\n");
    traverseLinkedList(&stock->medicines, printMedicineDetails);
}

void updateStock(Stock* stock, int productCode, int quantity) {
    // Find the product in the stock
    Product* stockProduct = findProduct(stock, productCode);

    if (stockProduct != NULL) {
        // Update the quantity available in the stock
        if (stockProduct->stockQuantity >= quantity) {
            stockProduct->stockQuantity -= quantity;
        } else {
            // Handle the case where there's not enough stock
            printf("Insufficient stock for product code %d. Available: %d, Required: %d\n", productCode, stockProduct->stockQuantity, quantity);
        }
    } else {
        // Handle the case where the product is not found in the stock
        printf("Product code %d not found in stock.\n", productCode);
    }
}

void updateMedicineStock(Stock* stock, char* medicineID, int quantity) {
    // Find the product in the stock
    Medicine* stockMedicine = findMedicineByID(stock, medicineID);

    if (stockMedicine != NULL) {
        // Update the quantity available in the stock
        if (stockMedicine->product.stockQuantity >= quantity) {
            stockMedicine->product.stockQuantity -= quantity;
        } else {
            // Handle the case where there's not enough stock
            printf("Insufficient stock for medicine with ID %s. Available: %d, Required: %d\n", medicineID, stockMedicine->product.stockQuantity, quantity);
        }
    } else {
        // Handle the case where the product is not found in the stock
        printf("Medicine with the ID %s not found in stock.\n", medicineID);
    }
}
