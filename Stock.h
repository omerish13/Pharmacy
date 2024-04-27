#ifndef STOCK_H
#define STOCK_H

#include "Product.h"  // Include the Product structure for use in the Stock
#include "Medicine.h"
#include "LinkedList.h"

/**
 * Represents the inventory of a pharmacy, including both general products and medicines.
 */
typedef struct Stock {
    int lastProductCode;  /**< Last product code used, for auto-incrementing product codes. */
    Product* products;   /**< Array of products in the stock. */
    int productCount;    /**< Number of products in the stock. */

    Medicine* medicines;   /**< Array of medicines in the stock. */
    int medicineCount;    /**< Number of medicines in the stock. */

} Stock;

/**
 * Initializes a Stock structure with dynamic allocation. Allocates memory
 * for the product array, preparing the stock for use.
 * 
 * @param stock Pointer to the Stock structure to be initialized.
 */
void initStock(Stock* stock);

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

/**
 * Adds a new product to the stock. The function prompts the user to enter the product details
 * such as name, price, and quantity, and then adds the product to the stock array.
 * 
 * @param stock Pointer to the Stock structure where the product is to be added.
 */
void decreaseStockQuantity(Stock* stock, int productCode, int quantity);

/**
 * Updates the stock quantity of a specific product based on a product code and quantity adjustment.
 * If the product is found in the stock and there is sufficient quantity, the stock is reduced by the specified quantity.
 * If the stock is insufficient, a warning is printed indicating the available and required quantities.
 * If the product is not found in the stock, a message is printed to indicate this.
 * 
 * @param stock Pointer to the Stock structure containing the array of products.
 * @param productCode The unique code of the product for which the stock quantity needs to be updated.
 * @param quantity The quantity by which the stock needs to be adjusted (reduced).
 */
void updateStock(Stock* stock, int productCode, int quantity);


/**
 * Finds a medicine in the stock based on its code.
 *
 * @param stock The stock to search in.
 * @param code The code of the medicine to find.
 * @return A pointer to the found Medicine object, or NULL if not found.
 */
Medicine* findMedicine(const Stock* stock, int code);


/**
 * Finds a medicine in the stock by its ID.
 *
 * @param stock The stock to search in.
 * @param medicineID The ID of the medicine to find.
 * @return A pointer to the Medicine struct if found, NULL otherwise.
 */
Medicine* findMedicineByID(Stock* stock, const char* medicineID);

/**
 * Adds a new product to the stock.
 *
 * @param stock The stock to add the product to.
 */
void addNewProductToStock(Stock* stock);

/**
 * Adds a new medicine to the stock.
 *
 * @param stock A pointer to the Stock structure.
 */
void addNewMedicineToStock(Stock* stock);

/**
 * Compares two medicines by their ID.
 *
 * This function is used to compare two medicines based on their ID values.
 * It is typically used as a comparison function for sorting or searching algorithms.
 *
 * @param a Pointer to the first medicine.
 * @param b Pointer to the second medicine.
 * @return An integer value indicating the comparison result:
 *         - Negative value if the ID of `a` is less than the ID of `b`.
 *         - Zero if the ID of `a` is equal to the ID of `b`.
 *         - Positive value if the ID of `a` is greater than the ID of `b`.
 */
int compareMedicineByID(const void* a, const void* b);

/**
 * @brief Compares two products by their code.
 *
 * This function is used as a comparison function for sorting or searching algorithms.
 * It compares two products based on their code.
 *
 * @param a Pointer to the first product.
 * @param b Pointer to the second product.
 * @return An integer value less than, equal to, or greater than zero if the code of the first product is less than, equal to, or greater than the code of the second product, respectively.
 */
int compareProductByID(const void* a, const void* b);

/**
 * @brief Compares two products by name.
 *
 * This function is used as a comparison function for sorting or searching
 * operations on an array of products. It compares the names of two products
 * and returns an integer value indicating their relative order.
 *
 * @param a Pointer to the first product.
 * @param b Pointer to the second product.
 * @return An integer value less than, equal to, or greater than zero if the
 *         name of the first product is considered to be less than, equal to,
 *         or greater than the name of the second product, respectively.
 */
int compareProductByName(const void* a, const void* b);

/**
 * @brief Compares two products by their price.
 *
 * This function is used as a comparison function for sorting products by price.
 * It takes two pointers to products and compares their prices.
 * The function returns a negative value if the price of the first product is lower than the price of the second product,
 * a positive value if the price of the first product is higher than the price of the second product,
 * and zero if the prices are equal.
 *
 * @param a Pointer to the first product.
 * @param b Pointer to the second product.
 * @return Negative value if the price of the first product is lower than the price of the second product,
 *         positive value if the price of the first product is higher than the price of the second product,
 *         zero if the prices are equal.
 */
int compareProductByPrice(const void* a, const void* b);

/**
 * Sorts the products in the stock.
 *
 * This function sorts the products in the stock in ascending order based on a certain criteria.
 *
 * @param stock A pointer to the Stock structure.
 */
void sortProductInStock(Stock* stock);

/**
 * @brief Finds a product in the stock using binary search.
 * 
 * This function searches for a given product in the stock using binary search algorithm.
 * It takes a pointer to the stock and a pointer to the product as parameters.
 * 
 * @param stock A pointer to the stock.
 * @param product A pointer to the product to be found.
 * @return A pointer to the found product if it exists in the stock, NULL otherwise.
 */
void findProductInStockBSearch(Stock* stock);

/**
 * Saves the stock details to a binary file, including the products and medicines.
 *
 * @param stock Pointer to the Stock structure to save.
 * @param file Pointer to the file where the stock details are to be saved.
 * @return 1 if the stock is saved successfully, 0 otherwise.
 */
int saveStockToBinary(const Stock *stock, FILE *file);

/**
 * Loads the stock details from a binary file, including the products and medicines.
 *
 * @param file Pointer to the file from which the stock details are to be loaded.
 * @param stock Pointer to the Stock structure to load the details into.
 * @return 1 if the stock is loaded successfully, 0 otherwise.
 */
int loadStockFromBinary(FILE* file, Stock* stock);

/**
 * Saves the stock details to a file, including the products and medicines.
 *
 * @param stock Pointer to the Stock structure to save.
 * @param file Pointer to the file where the stock details are to be saved.
 */
void saveStock(const Stock* stock, FILE* file);

/**
 * Loads the stock details from a file, including the products and medicines.
 *
 * @param file Pointer to the file from which the stock details are to be loaded.
 * @param stock Pointer to the Stock structure to load the details into.
 * @return Pointer to the loaded Stock structure.
 */
void loadStock(FILE* file, Stock* stock);

/**
 * Frees the memory allocated for the Stock structure.
 *
 * @param stock The Stock structure to free.
 */
void freeStock(Stock* stock);


#endif // STOCK_H
