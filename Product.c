#include "Product.h"

static int lastProductCode = 0;  // Static variable to keep track of the last used product code

// Corresponding names for the ProductType enum values
static const char* ProductTypeNames[PRODUCT_TYPE_COUNT] = {
    "Medicine", 
    "Healthcare",  
    "Equipment"
};

void initProduct(Product* product, int isMedicine) {
    product->code = ++lastProductCode;  // Auto-increment the product code
    setProductName(product);

    if (!isMedicine) {  // Only set product type if not a medicine
        setProductType(product);
    } else {
        product->type = MEDICINE;  // Automatically set to MEDICINE for medicine products
    }

    setProductPrice(product);
    setProductStockQuantity(product);
}

void setProductName(Product* product) {
    char buffer[BUFFER_SIZE];
    printf("Enter product name: ");
    myGets(buffer, BUFFER_SIZE);
    product->name = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(product->name);
    strcpy(product->name, buffer);
}

void setProductType(Product* product) {
    printf("Select product type:\n");
    for (int i = 1; i < PRODUCT_TYPE_COUNT; ++i) {
        printf("%d. %s\n", i + 1, ProductTypeNames[i]);
    }
    
    char buffer[BUFFER_SIZE];
    myGets(buffer, BUFFER_SIZE);
    int typeIndex = atoi(buffer) - 1;  // Adjust for 0-based index

    if (typeIndex >= 0 && typeIndex < PRODUCT_TYPE_COUNT) {
        product->type = (ProductType)typeIndex;
    } else {
        printf("Error: Invalid product type selection.\n");
    }
}

void setProductPrice(Product* product) {
    char buffer[BUFFER_SIZE];
    printf("Enter product price: ");
    myGets(buffer, BUFFER_SIZE);
    product->price = atof(buffer);
}

void setProductStockQuantity(Product* product) {
    char buffer[BUFFER_SIZE];
    printf("Enter stock quantity: ");
    myGets(buffer, BUFFER_SIZE);
    product->stockQuantity = atoi(buffer);
}

int compareProducts(void* a, void* b) {
    Product* productA = (Product*)a;
    Product* productB = (Product*)b;
    return productA->code - productB->code;  // 0 if codes are equal
}

void printProduct(void* item) {
    printProductDetails((Product*)item);
}

void printProductDetails(const Product* product) {
    printf("Product Code: %d\n", product->code);
    printf("Name: %s\n", product->name);
    printf("Type: %s\n", ProductTypeNames[product->type]);
    printf("Price: $%.2f\n", product->price);
    printf("Stock Quantity: %d\n", product->stockQuantity);
}
