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
    myGets(buffer);
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
    myGets(buffer);
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
    myGets(buffer);
    product->price = atof(buffer);
}

void setProductStockQuantity(Product* product) {
    char buffer[BUFFER_SIZE];
    printf("Enter stock quantity: ");
    myGets(buffer);
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
    printf("Product Code: %d", product->code);
    printf("Name: %s", product->name);
    printf("Type: %s", ProductTypeNames[product->type]);
    printf("Price: $%.2f", product->price);
    printf("Stock Quantity: %d\n", product->stockQuantity);
}

void saveProduct(FILE* file, const Product* product) {
    fprintf(file, "%d\n", product->code);
    fprintf(file, "%s\n", product->name);
    fprintf(file, "%d\n", product->type);
    fprintf(file, "%.2f\n", product->price);
    fprintf(file, "%d\n", product->stockQuantity);
}

Product* loadProduct(FILE* file) {
    Product* product = (Product*)malloc(sizeof(Product));
    fscanf(file, "%d\n", &product->code);
    char buffer[BUFFER_SIZE];
    fscanf(file, "%s\n", buffer);
    product->name = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(product->name);
    strcpy(product->name, buffer);
    fscanf(file, "%d\n", (int*)&product->type);
    fscanf(file, "%lf\n", &product->price);
    fscanf(file, "%d\n", &product->stockQuantity);

    return product;
}

void freeProduct(Product* product) {
    free(product->name);
    product->name = NULL;
}
