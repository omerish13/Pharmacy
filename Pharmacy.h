#ifndef PHARMACY_H
#define PHARMACY_H

#include "Address.h"
#include "Stock.h"
#include "Employee.h"
#include "Customer.h"
#include "Order.h"
#include "Prescription.h"
#include "LinkedList.h"

typedef struct Pharmacy {
    char* name;                        /**< Name of the pharmacy. */
    Address address;                   /**< Address of the pharmacy. */
    Stock stock;                       /**< Stock of products in the pharmacy. */
    Employee** employees;               /**< Dynamically allocated array of employees. */
    int employeeCount;                 /**< Number of employees in the pharmacy. */
    int employeeCapacity;              /**< Capacity of the employee array. */
    Customer* customers;               /**< Dynamically allocated array of customers. */
    int customerCount;                 /**< Number of customers in the pharmacy. */
    int customerCapacity;              /**< Capacity of the customer array. */
    LinkedList orderHistory;           /**< Linked list of completed orders. */
    Prescription* prescriptions;       /**< Dynamically allocated array of prescriptions. */
    int prescriptionCount;             /**< Number of prescriptions in the pharmacy. */
    int prescriptionCapacity;          /**< Capacity of the prescription array. */
} Pharmacy;

/**
 * Initializes a Pharmacy structure with dynamic allocation. Sets initial capacity and allocates memory
 * for the employee, customer, and prescription arrays, preparing the pharmacy for use.
 * 
 * @param pharmacy Pointer to the Pharmacy structure to be initialized.
 */
void initPharmacy(Pharmacy* pharmacy);

/**
 * Initializes a Pharmacy structure with dynamic allocation. Sets initial capacity and allocates memory
 * for the employee, customer, and prescription arrays, preparing the pharmacy for use. Getting data from user.
 * 
 * @param pharmacy Pointer to the Pharmacy structure to be initialized.
 */
void initPharmacyClient(Pharmacy* pharmacy);

/**
 * Sets the name of the pharmacy after dynamically allocating memory for it.
 * 
 * @param pharmacy Pointer to the Pharmacy structure whose name is being set.
 */
void setPharmacyName(char *name);

/**
 * Creates and initializes a new order for a specified customer and employee, and adds it to the open orders.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param customerID The unique identifier of the customer placing the order.
 * @param employeeID The unique identifier of the employee handling the order.
 */
Order* createNewOrder(Pharmacy* pharmacy, int customerID, int employeeID);

/**
* Creates and initializes a new order for a specified customer and employee, and adds it to the open orders.
* 
* @param pharmacy Pointer to the Pharmacy structure.
*/
Order* createNewOrderInteractive(Pharmacy* pharmacy);

/**
 * Adds a new employee to the pharmacy's list of employees.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param employee Pointer to the Employee structure to be added.
 */
void addEmployee(Pharmacy* pharmacy, const Employee* employee);

/**
 * Adds a new employee to the pharmacy's list of employees interactively.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 */
void addEmployeeInteractive(Pharmacy* pharmacy);

/**
 * Adds a new customer to the pharmacy's list of customers interactively.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 */
void addCustomerInteractive(Pharmacy* pharmacy);

/**
 * Adds a new customer to the pharmacy's list of customers.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param customer Pointer to the Customer structure to be added.
 */
void addCustomer(Pharmacy* pharmacy, const Customer* customer);

/**
 * Removes a customer from the pharmacy's list of customers based on their unique identifier.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param customerID The unique identifier of the customer to be removed.
 */
void removeEmployeeInteractive(Pharmacy* pharmacy);
/**
 * Removes an employee from the pharmacy's list of employees based on their unique identifier.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param employeeID The unique identifier of the employee to be removed.
 */
void removeEmployee(Pharmacy* pharmacy, int employeeID);

/**
 * Compare order numbers.
 * 
 * @param order Pointer to the Order structure.
 * @param orderNumber The unique number of the order to be compared.
 * @return 1 if order are the same, 0 otherwise.
 */
int compareOrderNumber(void* order, void* orderNumber); 


/**
 * Cancels an order.
 *
 * This function cancels the specified order by removing it from the system.
 *
 * @param order A pointer to the Order structure representing the order to be canceled.
 */
void cancelOrder(Order* order);

/**
 * Completes an order, moving it from the list of open orders to the order history, and updates stock availability.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param orderNumber The unique number of the order to be completed.
 */
void purchaseOrder(Pharmacy* pharmacy,Order* order);

/**
 * Adds a new prescription to the pharmacy's list of prescriptions.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param prescription Pointer to the Prescription structure to be added.
 */
void addNewPrescriptionToPharmacy(Pharmacy* pharmacy);

/**
 * Adds a new product to the pharmacy's stock.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 */
void addProductOrMedicineToOrder(Pharmacy* pharmacy, Order* order);

/**
 * Updates the stock of the pharmacy based on the products in the order.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param order Pointer to the Order structure.
 */
void updateProductQuantityOrder(Pharmacy* pharmacy, Order* order);


/**
 * Displays the current stock of the pharmacy and allows for updating the stock.
 *
 * @param pharmacy A pointer to the Pharmacy struct.
 */
void showAndUpdateStock(Pharmacy* pharmacy);

/**
 * Raises the salary of an employee by a specified percentage.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 */
void raiseSalaryClient(Pharmacy* pharmacy);

/**
 * Replaces the employee in the given order with a new employee in the pharmacy.
 *
 * @param pharmacy A pointer to the Pharmacy struct.
 * @param order A pointer to the Order struct.
 */
void replaceEmployeeInOrder(Pharmacy* pharmacy, Order* order);

/**
 * Prints the details of a pharmacy, including its name, address, and employee information.
 * 
 * @param pharmacy Pointer to the Pharmacy structure to be printed.
 */
void printPharmacyDetails(const Pharmacy* pharmacy);

/**
 * Prints the details of a pharmacy, including its name, address, and employee information.
 * 
 * @param pharmacy Pointer to the Pharmacy structure to be printed.
 */
void printAllEmployees(const Pharmacy* pharmacy);

/**
 * Prints the details of a pharmacy, including its name, address, and employee information.
 * 
 * @param pharmacy Pointer to the Pharmacy structure to be printed.
 */
void printAllCustomers(const Pharmacy* pharmacy);

/**
 * Saves data from the Pharmacy structure to a binary file.
 *
 * @param filename The name of the binary file to save the data to.
 * @param pharmacy A pointer to the Pharmacy structure containing the data to be saved.
 * @return Returns an integer indicating the success or failure of the operation.
 */
int saveDataToBinary(char* filename, Pharmacy* pharmacy);

/**
 * Loads the data of a Pharmacy object from a file.
 *
 * @param pharmacy A pointer to the Pharmacy object to populate with the data.
 * @param file A pointer to the file to load the data from.
 */
int loadDataFromBinary(char* filename, Pharmacy* pharmacy);

/**
 * Saves the data of a Pharmacy object to a file.
 *
 * @param filename The name of the file to save the data to.
 * @param pharmacy A pointer to the Pharmacy object containing the data to be saved.
 */
void saveDataToFile(char* filename, Pharmacy* pharmacy);

/**
 * Loads data from a file into a Pharmacy object.
 *
 * This function reads data from the specified file and populates the given Pharmacy object with the data.
 *
 * @param filename The name of the file to load data from.
 * @param pharmacy A pointer to the Pharmacy object to populate with the data.
 */
int loadDataFromFile(char* filename, Pharmacy* pharmacy);

/**
 * Frees the memory allocated for a Pharmacy structure.
 * 
 * @param pharmacy Pointer to the Pharmacy structure to free.
 */
void freePharmacy(Pharmacy* pharmacy);

#endif // PHARMACY_H
