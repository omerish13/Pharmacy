#include "Stock.h"
#include <stdio.h>
#include <stdlib.h>

void initStock(Stock* stock) {
    stock->lastProductCode = 0;
    stock->products = NULL;
    stock->productCount = 0;
    stock->medicines = NULL;
    stock->medicineCount = 0;
}

void showAvailableProducts(const Stock* stock) {
    printf("Available Products:\n");
    for (int i = 0; i < stock->productCount; i++) {
        printProductDetails(&stock->products[i]);
    }
    printf("Available Medicines:\n");
    for (int i = 0; i < stock->medicineCount; i++) {
        printMedicineDetails(&stock->medicines[i]);
    }
}

void sortProductInStock(Stock* stock) {
    int option;
    if (stock->productCount == 0) {
        printf("No products to sort.\n");
        return;
    }
    
    printf("Enter sort option (1 - by code, 2 - by name, 3 - by price): ");
    scanf("%d", &option);
    switch (option) {
    case 1:
        qsort(stock->products, stock->productCount, sizeof(Product), compareProductById);
        printf("Available Products After Sorting By Id:\n");
        for (int i = 0; i < stock->productCount; i++) 
            printProductDetails(&stock->products[i]);
        break;
    case 2:
        qsort(stock->products, stock->productCount, sizeof(Product), compareProductByName);
        printf("Available Products After Sorting By Name:\n");
        for (int i = 0; i < stock->productCount; i++) 
            printProductDetails(&stock->products[i]);
        break;
    case 3:
        qsort(stock->products, stock->productCount, sizeof(Product), compareProductByPrice);
        printf("Available Products After Sorting By Price:\n");
        for (int i = 0; i < stock->productCount; i++) 
            printProductDetails(&stock->products[i]);
        break;
    default:
        printf("Invalid sort type.\n");
    }
}

void findProductInStockBSearch(Stock* stock) {
    int option;
    Product* product = (Product*)malloc(sizeof(Product));
    if (product == NULL) {
        printf("Memory allocation failed for product.\n");
        return;
    }

    if (stock->productCount == 0) {
        printf("No products to search.\n");
        return;
    }

    printf("Enter search option (1 - by code, 2 - by name, 3 - by price): ");
    scanf("%d", &option);
    switch (option) {
        case 1:
            printf("Enter product code to search: ");
            scanf("%d", &product->code);
            qsort(stock->products, stock->productCount, sizeof(Product), compareProductById);
            printProductDetails((Product*)bsearch(product, stock->products, stock->productCount, sizeof(Product), compareProductByCode));
            break;
        case 2:
            printf("Enter product name to search: ");
            myGets(product->name);
            qsort(stock->products, stock->productCount, sizeof(Product), compareProductByName);
            printProductDetails((Product*)bsearch(product, stock->products, stock->productCount, sizeof(Product), compareProductByName));
            break;
        case 3:
            printf("Enter product price to search: ");
            scanf("%lf", &product->price);
            qsort(stock->products, stock->productCount, sizeof(Product), compareProductByPrice);
            printProductDetails((Product*)bsearch(product, stock->products, stock->productCount, sizeof(Product), compareProductByPrice));
            break;
        default:
            printf("Invalid search type.\n");
            break;
    }
}

// Comparator for medicines by ID
int compareMedicineByID(const void* a, const void* b) {
    const Medicine* medA = (const Medicine*)a;
    const Medicine* medB = (const Medicine*)b;
    return strcmp(medA->medicineID, medB->medicineID);
}

// Comparator for products by code
int compareProductById(const void* a, const void* b) {
    const Product* productA = (const Product*)a;
    const Product* productB = (const Product*)b;
    return productA->code - productB->code;
}

// Comparator for products by name
int compareProductByName(const void* a, const void* b) {
    const Product* productA = (const Product*)a;
    const Product* productB = (const Product*)b;
    return strcmp(productA->name, productB->name);
}

// Comparator for products by price
int compareProductByPrice(const void* a, const void* b) {
    const Product* productA = (const Product*)a;
    const Product* productB = (const Product*)b;
    return productA->price - productB->price;
}

Product* findProduct(const Stock* stock, int code) {
    // Use Binary Search to find the product with the given code
    Product tmp;
    tmp.code = code;
    Product* found = (Product*)bsearch(&tmp, stock->products, stock->productCount, sizeof(Product), compareProductByCode);
    return found;
}

int compareMedicineByCode(const void* a, const void* b) {
    const Medicine* medA = (const Medicine*)a;
    const Medicine* medB = (const Medicine*)b;
    return medA->product.code - medB->product.code;
}

Medicine* findMedicine(const Stock* stock, int code) {
    // Use Binary Search to find the medicine with the given code
    Medicine tmp;
    tmp.product.code = code;
    Medicine* found = (Medicine*)bsearch(&tmp, stock->medicines, stock->medicineCount, sizeof(Medicine), compareMedicineByCode);
    return found;
}

Medicine* findMedicineByID(Stock* stock, const char* medicineID){
    // Use Binary Search to find the medicine with the given ID
    Medicine tmp;
    strcpy(tmp.medicineID, medicineID);
    Medicine* found = (Medicine*)bsearch(&tmp, stock->medicines, stock->medicineCount, sizeof(Medicine), compareMedicineByID);
    return found;
}

void addNewProductToStock(Stock* stock) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    if (newProduct == NULL) {
        printf("Memory allocation failed for new product.\n");
        return;
    }
    
    initProduct(newProduct, 0,++stock->lastProductCode);  // 0 indicating this is not a medicine
    // Add the new product to the products array
    stock->products = (Product*)realloc(stock->products, (stock->productCount + 1) * sizeof(Product));
    CHECK_ALLOC_VOID(stock->products);
    stock->products[stock->productCount] = *newProduct;
    stock->productCount++;
    
}

void addNewMedicineToStock(Stock* stock) {
    Medicine* existingMedicine = NULL;
    char medicineID[ID_LENGTH];

    do {
        printf("Enter unique Medicine ID (6 digits): ");
        myGets(medicineID);

        // Use findMedicineByID to check if a medicine with the given ID already exists
        existingMedicine = findMedicineByID(stock, medicineID);

        if (existingMedicine != NULL) {
            printf("A medicine with the ID %s already exists in stock. Please enter a different ID.\n", medicineID);
        }
    } while (existingMedicine != NULL);  // Repeat until a unique ID is provided

    // Proceed to add new medicine if no existing medicine with the same ID is found
    Medicine* newMedicine = (Medicine*)malloc(sizeof(Medicine));
    CHECK_ALLOC_VOID(newMedicine);

    // Initialize new medicine with the provided ID
    initMedicine(newMedicine, medicineID,++stock->lastProductCode);

    // Add the new medicine to the medicines array
    stock->medicines = (Medicine*)realloc(stock->medicines, (stock->medicineCount + 1) * sizeof(Medicine));
    CHECK_ALLOC_VOID(stock->medicines);
    stock->medicines[stock->medicineCount] = *newMedicine;
    stock->medicineCount++;
}

void printStockDetails(const Stock* stock) {
    printf("Available Products:\n");
    for (int i = 0; i < stock->productCount; i++) {
        printProductDetails(&stock->products[i]);
    }
    printf("Available Medicines:\n");
    for (int i = 0; i < stock->medicineCount; i++) {
        printMedicineDetails(&stock->medicines[i]);
    }
}

void decreaseStockQuantity(Stock* stock, int productCode, int quantity) {
    // Find the product in the stock
    Product* stockProduct = findProduct(stock, productCode);

    if (stockProduct != NULL) {
        // Update the quantity available in the stock
        stockProduct->stockQuantity -= quantity;
    } else {
        // Handle the case where the product is not found in the stock
        printf("Product code %d not found in stock.\n", productCode);
    }
}

void updateStock(Stock* stock, int productCode, int quantity) {
    // Find the product in the stock
    Product* stockProduct = findProduct(stock, productCode);

    if (stockProduct != NULL) {
        // Update the quantity available in the stock
        stockProduct->stockQuantity = quantity;
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

int saveProductsToBinary(FILE* file, const Product* products, int productCount) {
    if (fwrite(&productCount, sizeof(int), 1, file) != 1) {
        return 0;
    }

    for (int i = 0; i < productCount; i++) {
        if (!saveProductToBinary(file, &products[i])) {
            return 0;
        }
    }

    return 1;
}

int saveMedicinesToBinary(FILE* file, const Medicine* medicines, int medicineCount) {
    if (fwrite(&medicineCount, sizeof(int), 1, file) != 1) {
        return 0;
    }

    for (int i = 0; i < medicineCount; i++) {
        if (!saveMedicineToBinary(file, &medicines[i])) {
            return 0;
        }
    }

    return 1;
}

int saveStockToBinary(const Stock* stock, FILE* file) {
    if (fwrite(&stock->lastProductCode, sizeof(int), 1, file) != 1) {
        return 0;
    }

    // Save the products
    if (!saveProductsToBinary(file, stock->products, stock->productCount)) {
        return 0;
    }

    // Save the medicines
    if (!saveMedicinesToBinary(file, stock->medicines, stock->medicineCount)) {
        return 0;
    }

    return 1;
}


int loadProductsFromBinary(FILE* file, Stock* stock) {
    if (fread(&stock->productCount, sizeof(int), 1, file) != 1) {
        printf("Error reading product count from file.\n");
        return 0;
    }

    stock->products = (Product*)malloc(stock->productCount * sizeof(Product));
    CHECK_ALLOC_INT(stock->products);

    for (int i = 0; i < stock->productCount; i++) {
        stock->products[i] = *(loadProductFromBinary(file));
    }

    return 1;
    
}

int loadMedicinesFromBinary(FILE* file, Stock* stock) {
    if (fread(&stock->medicineCount, sizeof(int), 1, file) != 1) {
        printf("Error reading medicine count from file.\n");
        return 0;
    }

    stock->medicines = (Medicine*)malloc(stock->medicineCount * sizeof(Medicine));
    CHECK_ALLOC_INT(stock->medicines);

    for (int i = 0; i < stock->medicineCount; i++) {
        stock->medicines[i] = *(loadMedicineFromBinary(file));
    }

    return 1;
}

int loadStockFromBinary(FILE* file, Stock* stock) {
    initStock(stock);

    // Load the last product code
    if (fread(&stock->lastProductCode, sizeof(int), 1, file) != 1) {
        printf("Error reading last product code from file.\n");
        return 0;
    }

    // Load the products
    if (!loadProductsFromBinary(file, stock))
        return 0;

    // Load the medicines
    if(!loadMedicinesFromBinary(file, stock))
        return 0;

    return 1;
}

void saveProducts(FILE* file, const Product* products, int productCount) {
    fprintf(file, "%d\n", productCount);
    for (int i = 0; i < productCount; i++) {
        saveProduct(file, &products[i]);
    }
}

void saveMedicines(FILE* file, const Medicine* medicines, int medicineCount) {
    fprintf(file, "%d\n", medicineCount);
    for (int i = 0; i < medicineCount; i++) {
        saveMedicine(file, &medicines[i]);
    }
}

void saveStock(const Stock* stock, FILE* file) {

    fprintf(file,"%d\n",stock->lastProductCode);
    // Save the products
    saveProducts(file, stock->products, stock->productCount);

    // Save the medicines
    saveMedicines(file, stock->medicines, stock->medicineCount);
}

void loadProducts(FILE* file, Stock* stock) {
    fscanf(file,"%d\n",&stock->productCount);

    stock->products = (Product*)malloc(stock->productCount * sizeof(Product));
    CHECK_ALLOC_VOID(stock->products);

    for (int i = 0; i < stock->productCount; i++) {
        stock->products[i] = *loadProduct(file);
    }
    
}

void loadMedicines(FILE* file, Stock* stock) {
    fscanf(file,"%d\n",&stock->medicineCount);

    stock->medicines = (Medicine*)malloc(stock->medicineCount * sizeof(Medicine));
    CHECK_ALLOC_VOID(stock->medicines);

    for (int i = 0; i < stock->medicineCount; i++) {
        stock->medicines[i] = *loadMedicine(file);
    }
}

void loadStock(FILE* file, Stock* stock) {
    initStock(stock);
    
    fscanf(file,"%d\n",&stock->lastProductCode);
    
    // Load the products
    loadProducts(file, stock);

    // Load the medicines
    loadMedicines(file, stock);
}


void freeStockProducts(Stock* stock) {
    free(stock->products);
    stock->products = NULL;
    stock->productCount = 0;
}

void freeStockMedicines(Stock* stock) {
    free(stock->medicines);
    stock->medicines = NULL;
    stock->medicineCount = 0;
}

void freeStock(Stock* stock) {
    
    freeStockProducts(stock);
    freeStockMedicines(stock);
}
