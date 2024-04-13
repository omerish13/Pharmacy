#include "Product.h"

// Corresponding names for the ProductType enum values
static const char* ProductTypeNames[PRODUCT_TYPE_COUNT] = {
    "Medicine", 
    "Healthcare",  
    "Equipment"
};

void initProduct(Product* product, int isMedicine, int productCode) {
    product->code = productCode;  // Auto-increment the product code
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
    CHECK_ALLOC_VOID(product->name);
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

void printProduct(const void* item) {
    const Product* product = (const Product*)item;
    printProductDetails(product);
}

void printProductInStock(const void* item) {
    const Product* product = (const Product*)item;
    if (product->stockQuantity > 0) {
        printProductDetails(product);
    }
}

void printProductDetails(const Product* product) {
    printf("Product Code: %d ", product->code);
    printf("Name: %s ", product->name);
    printf("Type: %s ", ProductTypeNames[product->type]);
    printf("Price: $%.2f ", product->price);
    printf("Stock Quantity: %d\n", product->stockQuantity);
}

int saveProductToBinary(FILE* file, const void* prod) {
    const Product* product = (const Product*)prod;
    if (fwrite(&product->code, sizeof(int), 1, file) != 1) {
        return 0;
    }
    int nameLength = (int)strlen(product->name) + 1;
    if (fwrite(&nameLength, sizeof(int), 1, file) != 1 || fwrite(product->name, sizeof(char), nameLength, file) != nameLength) {
        return 0;
    }
    if (fwrite(&product->type, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(&product->price, sizeof(double), 1, file) != 1) {
        return 0;
    }
    return fwrite(&product->stockQuantity, sizeof(int), 1, file) == 1;
}

void* loadProductFromBinary(FILE* file) {
    Product* product = (Product*)malloc(sizeof(Product));
    if (product == NULL) {
        return NULL;
    }
    if (fread(&product->code, sizeof(int), 1, file) != 1) {
        free(product);
        return NULL;
    }
    int nameLength;
    if (fread(&nameLength, sizeof(int), 1, file) != 1) {
        free(product);
        return NULL;
    }
    product->name = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(product->name);
    if (fread(product->name, sizeof(char), nameLength, file) != nameLength) {
        free(product->name);
        free(product);
        return NULL;
    }
    int productType;
    if (fread(&productType, sizeof(int), 1, file) != 1) {
        free(product->name);
        free(product);
        return NULL;
    }
    product->type = (ProductType)productType;
    if (fread(&product->price, sizeof(double), 1, file) != 1) {
        free(product->name);
        free(product);
        return NULL;
    }
    if (fread(&product->stockQuantity, sizeof(int), 1, file) != 1) {
        free(product->name);
        free(product);
        return NULL;
    }
    return product;
}

void saveProduct(FILE* file, const void* product) {
    const Product* prod = (const Product*)product;
    fprintf(file, "%d\n", prod->code);
    fprintf(file, "%s\n", prod->name);
    fprintf(file, "%d\n", prod->type);
    fprintf(file, "%.2f\n", prod->price);
    fprintf(file, "%d\n", prod->stockQuantity);
}

Product* loadProduct(FILE* file) {
    Product* product = (Product*)malloc(sizeof(Product));
    fscanf(file, "%d\n", &product->code);
    readString(file, &product->name);
    fscanf(file, "%d\n", (int*)&product->type);
    fscanf(file, "%lf\n", &product->price);
    fscanf(file, "%d\n", &product->stockQuantity);
    return product;
}

void freeProduct(void* product) {
    Product* prod = (Product*)product;
    free(prod);
    prod->name = NULL;
}
