#ifndef STOCK_H
#define STOCK_H

#include "Product.h"  // Include the Product structure for use in the Stock

/**
 * Structure representing the stock of products, supporting dynamic allocation to allow
 * flexibility in the number of products it can hold.
 */
typedef struct {
    Product* products;   /**< Dynamically allocated array of Product structures. */
    int productCount;    /**< Number of products currently in stock. */
    int capacity;        /**< Current capacity of the product array, used to manage dynamic allocation. */
} Stock;

/**
 * Initializes a Stock structure with dynamic allocation. Sets initial capacity and allocates memory
 * for the product array, preparing the stock for use.
 * 
 * @param stock Pointer to the Stock structure to be initialized.
 */
void initStock(Stock* stock);

/**
 * Displays all available products in the stock by printing detailed information for each product.
 * This function iterates over the array of products in the stock and uses printProductDetails
 * to show each product's details.
 * 
 * @param stock Pointer to the Stock structure whose products are to be displayed.
 */
void showAvailableProducts(const Stock* stock);

/**
 * Searches for a product in the stock by its unique code. Iterates through the array of products
 * and returns a pointer to the Product structure if found. If the product is not found, returns NULL.
 * 
 * @param stock Pointer to the Stock structure where the product is to be searched.
 * @param code The unique code of the product to find.
 * @return Pointer to the found Product structure, or NULL if the product is not found.
 */
Product* findProduct(const Stock* stock, int code);

/**
 * Prints the details of all products currently in the stock. Iterates over the array of products
 * and uses printProductDetails to print the details of each product in a formatted manner.
 * 
 * @param stock Pointer to the Stock structure whose product details are to be printed.
 */
void printStockDetails(const Stock* stock);

#endif // STOCK_H
