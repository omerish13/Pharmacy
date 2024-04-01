#include "Order.h"
#include <stdio.h>

static int lastOrderNumber = 0;  // For auto-incrementing the order number

void initOrder(Order* order, int customerID, int employeeID) {
    order->orderNumber = ++lastOrderNumber;
    order->customerID = customerID;
    initList(&order->orderProducts);  // Assuming initList initializes the linked list
    order->totalAmount = 0;
    // Set the current date to lastModified, assuming setDate sets the date
    setDate(&order->lastModified);
    order->employeeID = employeeID;
}

void updateEmployeeInOrder(Order* order, int newEmployeeID) {
    order->employeeID = newEmployeeID;
    // Optionally, update the lastModified date here as well
    setDate(&order->lastModified);
}

int addProductToOrder(Order* order, Stock* stock, int productCode, int quantity) {
    // Find the product in stock
    Product* product = findProduct(stock, productCode);
    if (!product || quantity > product->stockQuantity) {
        printf("Error: Invalid Product ID or insufficient stock quantity.\n");
        return 0;  // Indicate failure
    }

    // Check if product already in order and adjust quantity if so
    for (OrderProductNode* node = order->orderProducts; node != NULL; node = node->next) {
        if (node->product->code == productCode) {
            printf("Error: Product Already in order, you can update it's quantity through the menu.\n");
            return 0; // Indicate failure
        }
    }

    // If product not in order, add it
    OrderProductNode* newNode = (OrderProductNode*)malloc(sizeof(OrderProductNode));
    newNode->product = product;
    newNode->quantity = quantity;
    newNode->next = order->orderProducts;
    order->orderProducts = newNode;
    order->totalAmount += product->price * quantity;
    updateLastModified(order);
    return 1;  // Indicate success
}

int addMedicineToOrder(Order* order, Prescription* prescriptions, int numOfPrescriptions, Stock* stock, int medicineCode, int customerID) {
    Medicine* medicine = (Medicine*)findProduct(stock, medicineCode);
    if (!medicine) {
        printf("Error: Invalid Medicine ID.\n");
        return 0;  // Indicate failure
    }

    int validPrescriptionIndex = -1;
    for (int i = 0; i < numOfPrescriptions; i++) {
        if (prescriptions[i].customerID == customerID &&
            strcmp(prescriptions[i].medicineID, medicine->medicineID) == 0 &&
            !prescriptions[i].used) {
            validPrescriptionIndex = i;
            break;
        }
    }

    if (validPrescriptionIndex == -1) {
        printf("Error: No valid prescription for this medicine.\n");
        return 0;  // Indicate failure
    }

    int prescribedQuantity = prescriptions[validPrescriptionIndex].quantity;
    if (medicine->product.stockQuantity < prescribedQuantity) {
        char choice;
        printf("Insufficient stock. Available: %d, Required: %d\n", medicine->product.stockQuantity, prescribedQuantity);
        printf("Do you want to take the available amount? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            prescribedQuantity = medicine->product.stockQuantity;
        } else {
            return 0;  // Indicate failure
        }
    }

    // Add the medicine to the order with the prescribed quantity
    OrderProductNode* newNode = (OrderProductNode*)malloc(sizeof(OrderProductNode));
    if (!newNode) {
        printf("Error: Memory allocation failed.\n");
        return 0;  // Indicate failure
    }
    newNode->product = (Product*)medicine;
    newNode->quantity = prescribedQuantity;
    newNode->next = order->orderProducts;
    order->orderProducts = newNode;
    order->totalAmount += medicine->product.price * prescribedQuantity;
    prescriptions[validPrescriptionIndex].used = 1;  // Mark the prescription as used
    updateLastModified(order);
    return 1;  // Indicate success
}



// Modify this function signature to return an int indicating success/failure
int removeProductFromOrder(Order* order, int productCode) {
    OrderProductNode **node = &order->orderProducts, *temp = NULL;

    while (*node != NULL) {
        if ((*node)->product->code == productCode) {
            temp = *node;
            *node = (*node)->next;
            order->totalAmount -= temp->product->price * temp->quantity;
            free(temp);
            updateLastModified(order);
            return 1;  // Indicate success
        }
        node = &(*node)->next;
    }

    printf("Error: Product not found in the order.\n");
    return 0;  // Indicate failure
}

int updateProductQuantityInOrder(Stock* stock, Order* order, int productCode, int newQuantity) {
    Product* productInStock = findProduct(stock, productCode);
    Medicine* medicineInStock = NULL;
    if (!productInStock) {
        // If it's not found as a Product, try finding it as a Medicine
        medicineInStock = findMedicineByID(stock, productCode);
    }

    int availableQuantity = productInStock ? productInStock->stockQuantity : (medicineInStock ? medicineInStock->product.stockQuantity : -1);
    if (availableQuantity < 0) {
        printf("Error: Product/Medicine with code %d not found in stock.\n", productCode);
        return 0;  // Indicate failure
    }

    if (availableQuantity < newQuantity) {
        printf("Error: Insufficient stock for product/medicine code %d. Available: %d, Requested: %d\n", productCode, availableQuantity, newQuantity);
        return 0;  // Indicate failure due to insufficient stock
    }

    // Update product/medicine quantity in the order if stock is sufficient
    for (OrderProductNode* node = order->orderProducts; node != NULL; node = node->next) {
        if (node->product->code == productCode) {
            order->totalAmount += node->product->price * (newQuantity - node->quantity);
            node->quantity = newQuantity;
            updateLastModified(order);
            return 1;  // Indicate success
        }
    }

    printf("Error: Product/Medicine not found in the order.\n");
    return 0;  // Indicate failure
}


void showOrder(const Order* order) {
    printf("Order Number: %d\n", order->orderNumber);
    printf("Customer ID: %d\n", order->customerID);
    printf("Employee ID: %d\n", order->employeeID);
    printf("Total Amount: $%d\n", order->totalAmount);
    printList(&order->orderProducts, printProduct);
    printf("Last Modified: ");
    printDate(&order->lastModified);
}

void updateLastModified(Order* order) {
    // Update the lastModified field to the current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    order->lastModified.year = tm.tm_year + 1900;
    order->lastModified.month = tm.tm_mon + 1;
    order->lastModified.day = tm.tm_mday;
}

void printOrderProducts(Order* order){
    printList(&order->orderProducts, printProduct);
}
void removeProductFromOrderClient(Order* order) {
    int productCode, quantity;
    printOrderProducts(order);
    printf("Enter Product Code to remove from order: ");
    scanf("%d", &productCode);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    removeProductFromOrder(order,productCode);
}
