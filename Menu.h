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
 * Manages the main menu of the pharmacy system.
 *
 * This function is responsible for displaying the main menu options and handling user input.
 * It takes a pointer to a Pharmacy object as a parameter, which represents the pharmacy system.
 * The function allows the user to perform various operations on the pharmacy system, such as adding,
 * updating, or deleting medications, as well as generating reports.
 *
 * @param pharmacy A pointer to the Pharmacy object representing the pharmacy system.
 */
void manageMainMenu(Pharmacy* pharmacy);

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
 */
void manageOrder(Pharmacy* pharmacy);


/**
 * Manages prescriptions for a pharmacy.
 *
 * This function allows the user to manage prescriptions for a given pharmacy.
 * It takes a pointer to a Pharmacy object as a parameter.
 *
 * @param pharmacy A pointer to the Pharmacy object.
 */
void managePrescriptions(Pharmacy* pharmacy);

/**
 * @brief Manages the stock of a pharmacy.
 * 
 * This function is responsible for managing the stock of a pharmacy. It takes a pointer to a Pharmacy object as a parameter.
 * 
 * @param pharmacy A pointer to the Pharmacy object.
 */
void menageStock(Pharmacy* pharmacy);

/**
 * Manages the staff of the pharmacy.
 *
 * This function allows the user to manage the staff of the pharmacy by performing various operations
 * such as adding new staff members, removing existing staff members, and updating staff information.
 *
 * @param pharmacy A pointer to the Pharmacy object representing the pharmacy.
 */
void manageStaff(Pharmacy* pharmacy);

/**
 *
 * This function displays the show menu of the pharmacy system, which includes options for printing prescriptions,
 * stock, staff, orders, and displaying the menu.
 *
 * @param pharmacy A pointer to the Pharmacy object representing the pharmacy system.
 */
void showMenu(Pharmacy* pharmacy);


#endif // MENU_H
