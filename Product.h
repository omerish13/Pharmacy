#ifndef PRODUCT_H
#define PRODUCT_H

#include "general.h"

#define PRODUCT_TYPE_COUNT 3  // Update this count when adding new types
/**
 * Enum for ProductType.
 */
typedef enum {
    MEDICINE,
    HEALTHCARE, /**< Index 0: Healthcare product */
    EQUIPMENT   /**< Index 1: Equipment product */
    // Add new product types here
} ProductType;

/**
 * Structure representing a product's basic information.
 */
typedef struct {
    int code;           /**< Unique product code, automatically incremented */
    char* name;         /**< Dynamically allocated product name */
    ProductType type;   /**< Product type, represented by an enum */
    double price;       /**< Product price */
    int stockQuantity;  /**< Quantity of the product in stock */
} Product;

/**
 * Initializes a product with the specified product code.
 * 
 * @param product Pointer to the Product structure to initialize.
 * @param isMedicine Flag indicating if the product is a medicine.
 * @param productCode The product code to assign to the product.
 */
void initProduct(Product* product, int isMedicine, int productCode);

/**
 * Sets the name of a product after dynamically allocating memory for it.
 * @param product Pointer to the Product structure whose name is being set.
 */
void setProductName(Product* product);

/**
 * Sets the type of a product based on the user's numerical input, excluding MEDICINE.
 * @param product Pointer to the Product structure whose type is being set.
 */
void setProductType(Product* product);

/**
 * Sets the price of a product based on the user's input.
 * @param product Pointer to the Product structure whose price is being set.
 */
void setProductPrice(Product* product);

/**
 * Sets the stock quantity for a product based on the user's input.
 * @param product Pointer to the Product structure whose stock quantity is being set.
 */
void setProductStockQuantity(Product* product);

/**
 * Prints the details of the product in a formatted manner.
 * @param product Pointer to the Product structure whose details are being printed.
 */
void printProductDetails(const Product* product);

/**
 * Prints the product's name and code in a formatted manner.
 * @param item Pointer to the Product structure to print.
 */
void printProduct(const void* item);

/**
 * Prints the product's name and stock quantity in a formatted manner.
 * @param item Pointer to the Product structure to print.
 */
void printProductInStock(const void* item);

/**
 * Compares two Product structures based on their code.
 * @param a Pointer to the first Product structure.
 * @param b Pointer to the second Product structure.
 * @return Integer value representing the comparison result.
 */
int compareProducts(void* a, void* b);

/**
 * Save product details to a binary file, including name, type, price, and stock quantity.
 * @param file Pointer to the binary file to save the product details to.
 * @param product Pointer to the Product structure to save.
 * @return 1 if the product is successfully saved, 0 otherwise.
 */
int saveProductToBinary(FILE* file, const void* prod);

/**
 * Load product details from a binary file, including name, type, price, and stock quantity.
 * @param file Pointer to the binary file to read the product details from.
 * @return Pointer to the loaded Product structure.
 */
Product* loadProductFromBinary(FILE* file);

/**
 * Save product details to a file, including name, type, price, and stock quantity.
 * @param file Pointer to the file to save the product details to.
 * @param product Pointer to the Product structure to save.
 */
void saveProduct(FILE* file, const void* product);

/**
 * Reads product details from a file, including name, type, price, and stock quantity.
 * @param product Pointer to the Product structure to store the details.
 * @param file Pointer to the file to read the product details from.
 */
Product* loadProduct(FILE* file);

/**
 * Frees the dynamically allocated memory for the product's name.
 * @param product Pointer to the Product structure to free.
 */
void freeProduct(void* product);





#endif // PRODUCT_H
