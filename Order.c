#include "Order.h"
#include <stdio.h>


void initOrder(Order* order, int customerID, Employee* employee, int orderNumber) {
    order->orderNumber = orderNumber;
    order->customerID = customerID;
    initList(order->orderProducts);
    initList(order->orderMedicines);
    order->totalAmount = 0;
    initDate(&order->lastModified);
    order->employee = employee;
}

void updateEmployeeInOrder(Order* order, Employee* newEmployee) {
    order->employee = newEmployee;
    // Optionally, update the lastModified date here as well
    initDate(&order->lastModified);
}

int addProductToOrder(Order* order, Stock* stock, int productCode, int quantity) {
    // Find the product in stock
    Product* product = findProduct(stock, productCode);
    if (!product || quantity > product->stockQuantity) {
        printf("Error: Invalid Product ID or insufficient stock quantity.\n");
        return 0;  // Indicate failure
    }

    // Check if product already in order and adjust quantity if so
    OrderProductNode* node =  (OrderProductNode*)(OrderProductNode*)order->orderProducts->head;
    while (node != NULL)
    {
        if (node->product.code == productCode) {
            printf("Error: Product Already in order, you can update it's quantity through the menu.\n");
            return 0; // Indicate failure
        }
        node = node->next;
    }
    
    // If product not in order, add it
    OrderProductNode* newNode = (OrderProductNode*)malloc(sizeof(OrderProductNode));
    newNode->product = *product;
    newNode->quantity = quantity;
    newNode->next = NULL;
    node->next = newNode;
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
        if (prescriptions[i].customer->id == customerID &&
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

    // Check if medication already in order
    OrderMedicineNode* node = (OrderMedicineNode*)order->orderMedicines->head;
    while (node != NULL) {
        if (node->medicine.product.code == medicineCode) {
            printf("Error: Medicine already in order.\n");
            return 0;  // Indicate failure
        }
        node = node->next;
    }
    // Check if stock is sufficient for the prescribed quantity

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
    OrderMedicineNode* newNode = (OrderMedicineNode*)malloc(sizeof(OrderMedicineNode));
    CHECK_ALLOC_INT(newNode);
    newNode->medicine = *medicine;
    newNode->quantity = prescribedQuantity;
    newNode->next = NULL;
    node->next = newNode;
    order->totalAmount += medicine->product.price * prescribedQuantity;
    prescriptions[validPrescriptionIndex].used = 1;  // Mark the prescription as used
    updateLastModified(order);
    return 1;  // Indicate success
}

int removeProductFromOrder(Order* order, int productCode) {
    OrderProductNode *node = (OrderProductNode*)order->orderProducts->head, *temp = NULL;

    while (node != NULL) {
        if (node->product.code == productCode) {
            temp = node;
            node = node->next;
            order->totalAmount -= temp->product.price * temp->quantity;
            free(temp);
            updateLastModified(order);
            return 1;  // Indicate success
        }
        node = node->next;
    }

    printf("Error: Product not found in the order.\n");
    return 0;  // Indicate failure
}

int updateProductQuantityInOrder(Stock* stock, Order* order, int productCode, int newQuantity) {
    Product* productInStock = findProduct(stock, productCode);
    Medicine* medicineInStock = NULL;
    if (!productInStock) {
        // If it's not found as a Product, try finding it as a Medicine
        medicineInStock = findMedicine(stock, productCode);
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
    OrderProductNode* node = (OrderProductNode*)order->orderProducts->head;
    while (node != NULL)
    {
        if (node->product.code == productCode) {
            order->totalAmount += node->product.price * (newQuantity - node->quantity);
            node->quantity = newQuantity;
            updateLastModified(order);
            return 1;  // Indicate success
        }
        node = node->next;
    }

    printf("Error: Product/Medicine not found in the order.\n");
    return 0;  // Indicate failure
}

void showOrder(const Order* order) {
    printf("Order Number: %d\n", order->orderNumber);
    printf("Customer ID: %d\n", order->customerID);
    printEmployeeDetails(order->employee);
    printf("Total Amount: $%d\n", order->totalAmount);
    printList(order->orderProducts, printProduct);
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
    printList(order->orderProducts, printProduct);
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

int saveOrderProductToBinary(FILE* file, const void* item) {
    const OrderProductNode* node = (const OrderProductNode*)item;
    if (fwrite(&node->product.code, sizeof(int), 1, file) != 1 ||
        fwrite(&node->quantity, sizeof(int), 1, file) != 1) {
        return 0;
    }
    return 1;
}

int saveOrderMedicineNodeToBinary(FILE* file, const void* item) {
    const OrderMedicineNode* node = (const OrderMedicineNode*)item;
    if (fwrite(&node->medicine.product.code, sizeof(int), 1, file) != 1 ||
        fwrite(&node->quantity, sizeof(int), 1, file) != 1) {
        return 0;
    }
    return 1;
}

OrderMedicineNode* loadOrderMedicineNodeFromBinary(FILE* file) {
    OrderMedicineNode* node = (OrderMedicineNode*)malloc(sizeof(OrderMedicineNode));
    CHECK_ALLOC_STRUCT(node);
    if (fread(&node->medicine.product.code, sizeof(int), 1, file) != 1 ||
        fread(&node->quantity, sizeof(int), 1, file) != 1) {
        free(node);
        return NULL;
    }
    return node;
}

OrderProductNode* loadOrderProductFromBinary(FILE* file) {
    OrderProductNode* node = (OrderProductNode*)malloc(sizeof(OrderProductNode));
    CHECK_ALLOC_STRUCT(node);
    if (fread(&node->product.code, sizeof(int), 1, file) != 1 ||
        fread(&node->quantity, sizeof(int), 1, file) != 1) {
        free(node);
        return NULL;
    }
    return node;
}

int saveOrderToBinary(const Order* order, FILE* file) {
    if (!saveDateToBinary(file, &order->lastModified) ||
        !saveListBinary(file, order->orderProducts, saveOrderProductToBinary) ||
        !saveListBinary(file, order->orderMedicines, saveOrderMedicineNodeToBinary) ||
        fwrite(&order->orderNumber, sizeof(int), 1, file) != 1 ||
        fwrite(&order->customerID, sizeof(int), 1, file) != 1 ||
        fwrite(&order->employee->id, sizeof(int), 1, file) != 1) {
        return 0;
    }
    return 1;
}

Order* loadOrderFromBinary(FILE* file, Employee** employees, int numEmployees) {
    Order* order = (Order*)malloc(sizeof(Order));
    CHECK_ALLOC_STRUCT(order);
    if (!loadDateFromBinary(&order->lastModified,file) ||
        !(loadListBinary(file,order->orderProducts, (void* (*)(FILE*))loadOrderProductFromBinary)) ||
        !(loadListBinary(file, order->orderMedicines,(void* (*)(FILE*))loadOrderMedicineNodeFromBinary)) ||
        fread(&order->orderNumber, sizeof(int), 1, file) != 1 ||
        fread(&order->customerID, sizeof(int), 1, file) != 1 ||
        fread(&order->employee->id, sizeof(int), 1, file) != 1) {
        free(order);
        return NULL;
    }
    order->employee = findEmployee(employees, numEmployees, order->employee->id);
    return order;
}

void saveOrder(const Order* order, FILE* file) {
    saveDate(file, &order->lastModified);
    saveList(file, order->orderProducts, (void (*)(FILE*, const void*))saveOrderProductNode);
    saveList(file, order->orderMedicines, (void (*)(FILE*, const void*))saveOrderMedicineNode);
    fprintf(file, "%d %d %d %d\n", order->orderNumber, order->customerID, order->employee->id, order->totalAmount);
}

void saveOrderProductNode(FILE* file, void* data) {
    OrderProductNode* node = (OrderProductNode*)data;
    fprintf(file, "%d %d ", node->product.code, node->quantity);
}

void saveOrderMedicineNode(FILE* file, void* data) {
    OrderMedicineNode* node = (OrderMedicineNode*)data;
    fprintf(file, "%d %d ", node->medicine.product.code, node->quantity);
}

Order* loadOrder(FILE* file, Employee** employees, int numEmployees) {
    Order* order = (Order*)malloc(sizeof(Order));
    CHECK_ALLOC_STRUCT(order);
    loadDate(file, &order->lastModified);
    order->orderProducts = loadList(file, (void* (*)(FILE*))loadOrderProductNode);
    order->orderMedicines = loadList(file, (void* (*)(FILE*))loadOrderMedicineNode);
    fscanf(file, "%d %d %d %d", &order->orderNumber, &order->customerID, &order->employee->id, &order->totalAmount);
    order->employee = findEmployee(employees, numEmployees, order->employee->id);
    return order;
}

void*  loadOrderProductNode(FILE* file, void* data) {
    OrderProductNode* node = (OrderProductNode*)data;
    fscanf(file, "%d %d", &node->product.code, &node->quantity);
    return node;
}

void* loadOrderMedicineNode(FILE* file, void* data) {
    OrderMedicineNode* node = (OrderMedicineNode*)data;
    fscanf(file, "%d %d", &node->medicine.product.code, &node->quantity);
    return node;
}

void freeOrderProductNode(void* data) {
    free(data);
}

void freeOrder(Order* order) {
    freeList(order->orderProducts, freeOrderProductNode);
}
