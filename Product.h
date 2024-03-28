#ifndef PRODUCT_H
#define PRODUCT_H

#include "general.h"

#define PRODUCT_TYPE_COUNT 2  // Update this count when adding new types
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
 * Initializes a Product structure with a unique code and other provided details.
 * Optionally skips setting the product type if isMedicine is true.
 * @param product Pointer to the Product structure to initialize.
 * @param isMedicine Flag to indicate if the product is a medicine, which skips type selection.
 */
void initProduct(Product* product, int isMedicine);

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

#endif // PRODUCT_H