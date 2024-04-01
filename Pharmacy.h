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
    Employee* employees;               /**< Dynamically allocated array of employees. */
    int employeeCount;                 /**< Number of employees in the pharmacy. */
    int employeeCapacity;              /**< Capacity of the employee array. */
    Customer* customers;               /**< Dynamically allocated array of customers. */
    int customerCount;                 /**< Number of customers in the pharmacy. */
    int customerCapacity;              /**< Capacity of the customer array. */
    LinkedList openOrders;             /**< Linked list of open (incomplete) orders. */
    LinkedList orderHistory;           /**< Linked list of completed orders. */
    Prescription* prescriptions;       /**< Dynamically allocated array of prescriptions. */
    int prescriptionCount;             /**< Number of prescriptions in the pharmacy. */
    int prescriptionCapacity;          /**< Capacity of the prescription array. */
} Pharmacy;

/**
 * Creates and initializes a new order for a specified customer and employee, and adds it to the open orders.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param customerID The unique identifier of the customer placing the order.
 * @param employeeID The unique identifier of the employee handling the order.
 */
void createNewOrder(Pharmacy* pharmacy, int customerID, int employeeID);

/**
 * Adds a new employee to the pharmacy's list of employees.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param employee Pointer to the Employee structure to be added.
 */
void addEmployee(Pharmacy* pharmacy, const Employee* employee);

/**
 * Adds a new customer to the pharmacy's list of customers.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param customer Pointer to the Customer structure to be added.
 */
void addCustomer(Pharmacy* pharmacy, const Customer* customer);

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
 * Cancels an order and removes it from the list of open orders.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param orderNumber The unique number of the order to be canceled.
 */
void cancelOrder(Pharmacy* pharmacy, int orderNumber);

/**
 * Completes an order, moving it from the list of open orders to the order history, and updates stock availability.
 * 
 * @param pharmacy Pointer to the Pharmacy structure.
 * @param orderNumber The unique number of the order to be completed.
 */
void purchaseOrder(Pharmacy* pharmacy, int orderNumber);

void addNewPrescriptionToPharmacy(Pharmacy* pharmacy);

#endif // PHARMACY_H
