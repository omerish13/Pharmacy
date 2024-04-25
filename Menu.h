#ifndef MENU_H
#define MENU_H

#include "Pharmacy.h"
#include "Order.h"
#include "Stock.h"
#include "Employee.h"
#include "Customer.h"
#include "Prescription.h"
#include "Date.h"
#include "LinkedList.h"
#include <stdio.h>

/**
 * Prints the main menu of the pharmacy management system.
 */
void printMainMenu();

/**
 * Prints the order management menu for a specific order.
 */
void printOrderManagementMenu();


/**
 * Manages an order in the pharmacy.
 *
 * This function is responsible for managing an order in the pharmacy. It takes a Pharmacy object and an Order object as parameters.
 * The function performs various operations on the order, such as updating the order status, calculating the total cost, and updating the inventory.
 *
 * @param pharmacy A pointer to the Pharmacy object.
 * @param order A pointer to the Order object.
 */
void manageOrder(Pharmacy* pharmacy, Order* order);


#endif // MENU_H
