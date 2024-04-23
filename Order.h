#ifndef ORDER_H
#define ORDER_H

#include "Product.h"
#include "Medicine.h"
#include "Date.h"
#include "Stock.h"
#include "Prescription.h"
#include "Employee.h"
#include <time.h>

/**
 * Node in the linked list of order products, storing product details and quantity.
 */
typedef struct OrderProductNode {
    int productCode;                /**<  Product Code in order. */
    char* productName;              /**< Product Name in order. */
    int price;                      /**< Price of this product in the order. */
    int quantity;                    /**< Quantity of this product in the order. */
} OrderProductNode;

/**
 * Node in the linked list of order medicines, storing medicine details and quantity.
 */
typedef struct OrderMedicineNode {
    int medicineCode;                /**< Medicine Code in order. */
    char* medicineName;              /**< Medicine Name in order. */
    int price;                      /**< Price of this medicine in the order. */
    int quantity;                    /**< Quantity of this medicine in the order. */
} OrderMedicineNode;



/**
 * Represents an entire order, including customer details, products ordered,
 * total cost, and modification date.
 */
typedef struct {
    int orderNumber;                  /**< Unique identifier for each order. */
    int customerID;                   /**< Identifier for the customer who made the order. */
    LinkedList* orderProducts;  /**< Head of the linked list of products in the order. */
    LinkedList* orderMedicines;  /**< Head of the linked list of medicines in the order. */
    int totalAmount;                  /**< Total cost of the order. */
    Date lastModified;                /**< Date when the order was last modified. */
    Employee* employee;                   /**< ID of the employee managing the order. */
} Order;

/**
 * Initializes an order with the specified customer ID.
 * 
 * @param order Pointer to the Order structure to initialize.
 * @param customerID The customer's unique identifier.
 */
void initOrder(Order* order, int customerID, Employee* employee, int orderNumber);

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
 * @param product Pointer to the Product to add.
 * @param quantity The quantity of the product to add to the order.
 * @return Integer indicating success (1) or failure (0) of the operation.
 */
int addProductToOrder(Order* order, Stock* stock, Product* product, int quantity);

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
 * @param medicine Pointer to the Medicine to add.
 * @param customerID The ID of the customer making the order, used for prescription verification.
 * @return Integer indicating success (1) or failure (0) of the operation. Failure can occur if the stock is
 * insufficient, the medicine is not found, or the customer does not have a valid prescription.
 */
int addMedicineToOrder(Order* order, Prescription* prescriptions, int numOfPrescriptions, Stock* stock, Medicine* medicine, int customerID);

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
void updateEmployeeInOrder(Order* order, Employee* newEmployee);

/**
 * Prints the details of an order product node.
 * 
 * @param data Pointer to the OrderProductNode to print.
 */
void printOrderProductNode(const void* data);

/**
 * Prints the details of an order medicine node.
 * 
 * @param data Pointer to the OrderMedicineNode to print.
 */
void printOrderMedicineNode(const void* data);

/**
 * Prints the medicines in an order.
 * 
 * @param order Pointer to the Order to print medicines from.
 */
int compareOrderProductNodes(void* order, void* orderNumber);

/**
* Removes all products from an order.
* 
* @param order Pointer to the Order to clear.
*/
void removeProductFromOrderClient(Order* order);

/**
 * Saves an order to a binary file.
 * 
 * @param file Pointer to the file to save the order to.
 * @param data Pointer to the Order to save.
 * @return Integer indicating success (1) or failure (0) of the operation.
 */
int saveOrderToBinary(FILE* file, const void* data);

/**
 * Saves an order product node to a binary file.
 * 
 * @param file Pointer to the file to save the order product node to.
 * @param data Pointer to the OrderProductNode to save.
 */
void saveOrderProductNode(FILE* file, const void* data);

/**
 * Saves an order medicine node to a binary file.
 * 
 * @param file Pointer to the file to save the order medicine node to.
 * @param data Pointer to the OrderMedicineNode to save.
 */
void saveOrderMedicineNode(FILE* file, const void* data);

/**
 * Saves an order product node to a binary file.
 * 
 * @param file Pointer to the file to save the order product node to.
 * @param item Pointer to the OrderProductNode to save.
 * @return Returns 0 if the item was successfully saved, otherwise returns a non-zero value.
 */
int saveOrderMedicineNodeToBinary(FILE* file, const void* item);

/**
 * Saves an order product to a binary file.
 *
 * This function writes the given order product item to the specified binary file.
 *
 * @param file The file pointer to the binary file.
 * @param item The pointer to the order product item to be saved.
 * @return Returns 0 if the item was successfully saved, otherwise returns a non-zero value.
 */
int saveOrderProductToBinary(FILE* file, const void* item);

/**
 * Loads an order product node from a binary file.
 * 
 * @param file Pointer to the file to read the order product node from.
 * @return Pointer to the loaded OrderProductNode.
 */
void* loadOrderProductNode(FILE* file);

/**
 * Loads an order medicine node from a binary file.
 * 
 * @param file Pointer to the file to read the order medicine node from.
 * @return Pointer to the loaded OrderMedicineNode.
 */
void* loadOrderMedicineNode(FILE* file);

/**
 * Loads an order medicine from a binary file.
 * 
 * @param file Pointer to the file to read the order medicine from.
 * @return Pointer to the loaded OrderMedicineNode.
 */
void* loadOrderProductNodeFromBinary(FILE* file);

/**
 * Loads an order medicine from a binary file.
 * 
 * @param file Pointer to the file to read the order medicine from.
 * @return Pointer to the loaded OrderMedicineNode.
 */
void* loadOrderMedicineNodeFromBinary(FILE* file);

/**
 * Loads an order from a binary file.
 * 
 * @param file Pointer to the file to read the order from.
 * @param employees Array of Employee structures.
 * @param numEmployees Total number of employees in the array.
 * @return Pointer to the loaded Order.
 */
Order* loadOrderFromBinary(FILE* file, Employee** employees, int numEmployees);

/**
 * Saves an order to a file.
 * 
 * @param file Pointer to the file to save the order to.
 * @param data Pointer to the Order to save.
 */
void saveOrder(FILE* file, const void* data);

/**
 * Loads an order from a file.
 * 
 * @param file Pointer to the file to read the order from.
 * @param employees Array of Employee structures.
 * @param numEmployees Total number of employees in the array.
 * @return Pointer to the loaded Order.
 */
Order* loadOrder(FILE* file, Employee** employees, int numEmployees);


/**
 * Frees the memory allocated for an order product node.
 *
 * @param data A pointer to the data stored in the node.
 */
void freeOrderProductNode(void* data);

/**
 * Frees the memory allocated for an order medicine node.
 *
 * @param data A pointer to the data stored in the node.
 */
void freeOrderMedicineNode(void* data);

/**
 * Frees the memory allocated for an order.
 * 
 * @param order Pointer to the Order to free.
 */
void freeOrder(void* order);



#endif // ORDER_H
