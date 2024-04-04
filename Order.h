#ifndef ORDER_H
#define ORDER_H

#include "Product.h"
#include "Medicine.h"
#include "Date.h"
#include "Stock.h"
#include "Prescription.h"
#include <time.h>

/**
 * Node in the linked list of order products, storing product details and quantity.
 */
typedef struct OrderProductNode {
    Product* product;                /**< Pointer to the product in the order. */
    int quantity;                    /**< Quantity of this product in the order. */
    struct OrderProductNode* next;   /**< Pointer to the next product node in the order. */
} OrderProductNode;

/**
 * Represents an entire order, including customer details, products ordered,
 * total cost, and modification date.
 */
typedef struct {
    int orderNumber;                  /**< Unique identifier for each order. */
    int customerID;                   /**< Identifier for the customer who made the order. */
    OrderProductNode* orderProducts;  /**< Head of the linked list of products in the order. */
    int totalAmount;                  /**< Total cost of the order. */
    Date lastModified;                /**< Date when the order was last modified. */
    int employeeID;                   /**< ID of the employee managing the order. */
} Order;

/**
 * Initializes an order with the specified customer ID.
 * 
 * @param order Pointer to the Order structure to initialize.
 * @param customerID The customer's unique identifier.
 */
void initOrder(Order* order, int customerID,int employeeID);

/**
 * Displays the details of an order, including each product and the total cost.
 * 
 * @param order Pointer to the Order to display.
 */
void showOrder(const Order* order);

/**
 * Adds a product to an order by product code and quantity.
 * 
 * @param order Pointer to the Order to add the product to.
 * @param stock Pointer to the Stock for product availability verification.
 * @param productCode The unique code of the product to add.
 * @param quantity The quantity of the product to add to the order.
 * @return Integer indicating success (1) or failure (0) of the operation.
 */
int addProductToOrder(Order* order, Stock* stock, int productCode, int quantity);

/**
 * Adds a medicine to an order by medicine code and quantity, verifying that the customer has a valid prescription.
 * This function checks the stock for the availability of the medicine and verifies that the customer has a valid,
 * unused prescription for the medicine before adding it to the order. If the medicine is successfully added, the
 * total amount of the order is updated accordingly.
 * 
 * @param order Pointer to the Order to add the medicine to.
 * @param prescriptions Pointer to list of prescriptions that need to be checked.
 * @param numOfPrescriptions Number of prescription in prescriptions list.
 * @param stock Pointer to the Stock for medicine availability verification.
 * @param medicineCode The unique code of the medicine to add.
 * @param customerID The ID of the customer making the order, used for prescription verification.
 * @return Integer indicating success (1) or failure (0) of the operation. Failure can occur if the stock is
 * insufficient, the medicine is not found, or the customer does not have a valid prescription.
 */
int addMedicineToOrder(Order* order, Prescription* prescriptions, int numOfPrescriptions, Stock* stock, int medicineCode, int customerID);

/**
 * Updates the quantity of a product already in the order.
 * 
 * @param stock Pointer to the Stock for product availability verification.
 * @param order Pointer to the Order to update.
 * @param productCode The unique code of the product whose quantity needs updating.
 * @param newQuantity The new quantity for the product.
 * @return Integer indicating success (1) or failure (0) of the operation.
 */
int updateProductQuantityInOrder(Stock* stock, Order* order, int productCode, int newQuantity);

/**
 * Removes a product from an order by product code.
 * 
 * @param order Pointer to the Order to remove the product from.
 * @param productCode The unique code of the product to remove.
 * @return Integer indicating success (1) or failure (0) of the operation.
 */
int removeProductFromOrder(Order* order, int productCode);

/**
 * Updates the 'lastModified' date of the order to the current date.
 * 
 * @param order Pointer to the Order to update.
 */
void updateLastModified(Order* order);

/**
 * Updates the employee ID associated with an order.
 * 
 * @param order Pointer to the Order to update.
 * @param newEmployeeID The new employee ID to be associated with the order.
 */
void updateEmployeeInOrder(Order* order, int newEmployeeID);

/**
 * Prints the products in an order.
 * 
 * @param order Pointer to the Order to print products from.
 */
void printOrderProducts(Order* order);

/**
* Removes all products from an order.
* 
* @param order Pointer to the Order to clear.
*/
void removeProductFromOrderClient(Order* order);


/**
 * Frees the memory allocated for an order.
 * 
 * @param order Pointer to the Order to free.
 */
void freeOrder(Order* order);



#endif // ORDER_H
