#include "Order.h"
#include <stdio.h>


void initOrder(Order* order, int customerID, Employee* employee, int orderNumber) {
    order->orderNumber = orderNumber;
    order->customerID = customerID;
    order->orderProducts = (LinkedList*)malloc(sizeof(LinkedList));
    initList(order->orderProducts);
    order->orderMedicines = (LinkedList*)malloc(sizeof(LinkedList));
    initList(order->orderMedicines);
    order->totalAmount = 0;
    currentDate(&order->lastModified);
    order->employee = employee;
}

void updateEmployeeInOrder(Order* order, Employee* newEmployee) {
    order->employee = newEmployee;
    // Optionally, update the lastModified date here as well
    currentDate(&order->lastModified);
}

int isProductInOrder(Order* order, int productCode) {
    ListNode* node = order->orderProducts->head;
    while (node != NULL) {
        OrderProductNode* productNode = (OrderProductNode*)node->item;
        if (productNode->productCode == productCode) {
            return 1;  // Product found in order
        }
        node = node->next;
    }
    return 0;  // Product not found in order
}

int isMedicineInOrder(Order* order, int medicineCode) {
    ListNode* node = order->orderMedicines->head;
    while (node != NULL) {
        OrderMedicineNode* medicineNode = (OrderMedicineNode*)node->item;
        if (medicineNode->medicineCode == medicineCode) {
            return 1;  // Medicine found in order
        }
        node = node->next;
    }
    return 0;  // Medicine not found in order
}

void showAvailableProducts(Stock* stock, Order* order) {
    printf("Available Products:\n");
    for (int i = 0; i < stock->productCount; i++) {
        if (!isProductInOrder(order, stock->products[i].code)) {
            printProduct(&stock->products[i]);
        }
    }
    printf("Available Medicines:\n");
    for (int i = 0; i < stock->medicineCount; i++) {
        if (!isMedicineInOrder(order, stock->medicines[i].product.code)) {
            printMedicineInStock(&stock->medicines[i]);
        }
    }
}
int addProductToOrder(Order* order, Stock* stock, Product* product, int quantity) {
    if (!product) {
        printf("Error: Invalid Product Code.\n");
        return 0;  // Indicate failure
    }

    int availableQuantity = product->stockQuantity;
    if (availableQuantity <= 0) {
        printf("Error: Product with code %d not found in stock.\n", product->code);
        return 0;  // Indicate failure
    }

    if (availableQuantity < quantity) {
        printf("Error: Insufficient stock for product code %d. Available: %d, Requested: %d\n", product->code, availableQuantity, quantity);
        return 0;  // Indicate failure due to insufficient stock
    }

    // Check if product already in order
    ListNode* node = (ListNode*)order->orderProducts->head;
    while (node != NULL) {
        OrderProductNode* productNode = (OrderProductNode*)node->item;
        if (productNode->productCode == product->code) {
            printf("Error: Product already in order.\n");
            return 0;  // Indicate failure
        }
        node = node->next;
    }

    // Add the product to the order with the specified quantity
    OrderProductNode* newNode = (OrderProductNode*)malloc(sizeof(OrderProductNode));
    CHECK_ALLOC_INT(newNode);
    newNode->productCode = product->code;
    newNode->productName = strdup(product->name);
    newNode->quantity = quantity;
    newNode->price = product->price;
    addToList(order->orderProducts, newNode);
    order->totalAmount += product->price * quantity;
    updateLastModified(order);
    return 1;  // Indicate success
}

int addMedicineToOrder(Order* order, Prescription* prescriptions, int numOfPrescriptions, Stock* stock, Medicine* medicine, int customerID) {
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

    if (validPrescriptionIndex == -1 && medicine->prescriptionRequired) {
        printf("Error: No valid prescription for this medicine.\n");
        return 0;  // Indicate failure
    }

    // Check if medication already in order
    ListNode* node = order->orderMedicines->head;
    while (node != NULL) {
        OrderMedicineNode* medicineNode = (OrderMedicineNode*)node->item;
        if (medicineNode->medicineCode == medicine->product.code) {
            printf("Error: Medicine already in order.\n");
            return 0;  // Indicate failure
        }
        node = node->next;
    }
    // Check if stock is sufficient for the prescribed quantity

    int prescribedQuantity;
    if (medicine->prescriptionRequired)
        prescribedQuantity = prescriptions[validPrescriptionIndex].quantity;
    else{
        printf("Enter quantity: ");
        scanf("%d", &prescribedQuantity);
    }
    if (medicine->product.stockQuantity < prescribedQuantity) {
        char choice;
        printf("Insufficient stock. Available: %d, Required: %d\n", medicine->product.stockQuantity, prescribedQuantity);
        printf("Do you want to take the available amount? (y/n): ");
        scanf(" %c", &choice);
        clearInputBuffer();
        if (choice == 'y' || choice == 'Y') {
            prescribedQuantity = medicine->product.stockQuantity;
            if (medicine->prescriptionRequired)
                prescriptions[validPrescriptionIndex].used = 1;  // Mark the prescription as used
        } else {
            return 0;  // Indicate failure
        }
    }
    else if (medicine->prescriptionRequired)
        prescriptions[validPrescriptionIndex].used = 1;  // Mark the prescription as used

    // Add the medicine to the order with the prescribed quantity
    OrderMedicineNode* newNode = (OrderMedicineNode*)malloc(sizeof(OrderMedicineNode));
    CHECK_ALLOC_INT(newNode);
    newNode->medicineCode = medicine->product.code;
    newNode->medicineName = strdup(medicine->product.name);
    newNode->quantity = prescribedQuantity;
    newNode->price = medicine->product.price;
    addToList(order->orderMedicines, newNode);
    order->totalAmount += medicine->product.price * prescribedQuantity;
    decreaseStockQuantity(stock, medicine->product.code, prescribedQuantity);
    updateLastModified(order);
    return 1;  // Indicate success
}

int compareOrderProductNodes(void* a, void* b) {
    const OrderProductNode* nodeA = (const OrderProductNode*)a;
    const OrderProductNode* nodeB = (const OrderProductNode*)b;
    return nodeA->productCode - nodeB->productCode;
}

int removeProductFromOrder(Order* order, int productCode) {
    
    OrderProductNode* product = (OrderProductNode*)removeFromList(order->orderProducts,&compareOrderProductNodes, &productCode);
    if (product == NULL) {
        printf("Error: Product not found in order.\n");
        return 0;  // Indicate failure
    }

    order->totalAmount -= product->price * product->quantity;
    updateLastModified(order);
    return 1;  // Indicate success

}

int updateProductQuantityInOrder(Stock* stock, Order* order, int productCode, int newQuantity) {
    Product* productInStock = findProduct(stock, productCode);
    if (!productInStock) {
        // If it's not found as a Product, try finding it as a Medicine
        printf("Product not found in stock.\n");
        return 0;
    }

    int availableQuantity = productInStock->stockQuantity;
    if (availableQuantity < 0) {
        printf("Error: Product with code %d not found in stock.\n", productCode);
        return 0;  // Indicate failure
    }

    if (availableQuantity < newQuantity) {
        printf("Error: Insufficient stock for product code %d. Available: %d, Requested: %d\n", productCode, availableQuantity, newQuantity);
        return 0;  // Indicate failure due to insufficient stock
    }

    // Update product/medicine quantity in the order if stock is sufficient
    ListNode* node = order->orderProducts->head;
    while (node != NULL)
    {
        OrderProductNode* productNode = (OrderProductNode*)node->item;
        if (productNode->productCode == productCode) {
            order->totalAmount += productInStock->price * (newQuantity - productNode->quantity);
            productNode->quantity = newQuantity;
            updateLastModified(order);
            return 1;  // Indicate success
        }
        node = node->next;
    }

    printf("Error: Product/Medicine not found in the order.\n");
    return 0;  // Indicate failure
}

void showOrder(const void* data) {
    const Order* order = (const Order*)data;
    printf("Order Number: %d\n", order->orderNumber);
    printf("Customer ID: %d\n", order->customerID);
    printEmployeeDetails(order->employee);
    printf("Total Amount: ₪%d\n", order->totalAmount);
    printf("Order Products:\n");
    printList(order->orderProducts, printOrderProductNode);
    printf("Order Medicines:\n");
    printList(order->orderMedicines, printOrderMedicineNode);
    printf("Last Modified: ");
    printDate(&order->lastModified);
}

void showOrdersHistoryByDate(const LinkedList* orders) {
    if (orders->size == 0) {
        printf("No orders found.\n");
        return;
    }
    ListNode* node = orders->head;
    Date start, end;
    printf("Enter Start Date (DD/MM/YYYY):\n");
    initDate(&start);
    printf("Enter End Date (DD/MM/YYYY):\n");
    initDate(&end);

    if (compareDates(&start, &end) > 0) {
        printf("Error: Start date is after end date.\n");
        return;
    }

    while (node != NULL) {
        Order* order = (Order*)node->item;
        if (compareDates(&order->lastModified, &start) >= 0 && compareDates(&order->lastModified, &end) <= 0) {
            showOrder(order);
        }
        node = node->next;
    }
}
    

void updateLastModified(Order* order) {
    // Update the lastModified field to the current date
    currentDate(&order->lastModified);
}

void printOrderProductNode(const void* data) {
    const OrderProductNode* node = (const OrderProductNode*)data;
    printf("Product Code: %d, Name: %s, Quantity: %d\n", node->productCode, node->productName, node->quantity);
}

void printOrderMedicineNode(const void* data) {
    const OrderMedicineNode* node = (const OrderMedicineNode*)data;
    printf("Medicine Code: %d, Name: %s, Quantity: %d\n", node->medicineCode, node->medicineName, node->quantity);
}

void removeProductFromOrderClient(Order* order) {
    int productCode;
    printList(order->orderProducts, printOrderProductNode);
    if (order->orderProducts->size == 0) {
        printf("No products in order.\n");
        return;
    }
    printf("Enter Product Code to remove from order: ");
    scanf("%d", &productCode);

    removeProductFromOrder(order,productCode);
}

int saveOrderProductToBinary(FILE* file, const void* item) {
    const OrderProductNode* node = (const OrderProductNode*)item;
    if (fwrite(&node->productCode, sizeof(int), 1, file) != 1) {
        return 0;
    }
    int nameLength = (int)strlen(node->productName) + 1;
    if (fwrite(&nameLength, sizeof(int), 1, file) != 1 || fwrite(node->productName, sizeof(char), nameLength, file) != nameLength) {
        return 0;
    }
    if (fwrite(&node->price, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(&node->quantity, sizeof(int), 1, file) != 1) {
        return 0;
    }
    return 1;
}

int saveOrderMedicineNodeToBinary(FILE* file, const void* item) {
    const OrderMedicineNode* node = (const OrderMedicineNode*)item;
    if (fwrite(&node->medicineCode, sizeof(int), 1, file) != 1) {
        return 0;
    }
    int nameLength = (int)strlen(node->medicineName) + 1;
    if (fwrite(&nameLength, sizeof(int), 1, file) != 1 || fwrite(node->medicineName, sizeof(char), nameLength, file) != nameLength) {
        return 0;
    }
    if (fwrite(&node->price, sizeof(int), 1, file) != 1) {
        return 0;
    }
    if (fwrite(&node->quantity, sizeof(int), 1, file) != 1) {
        return 0;
    }
    return 1;
}

void* loadOrderMedicineNodeFromBinary(FILE* file) {
    OrderMedicineNode* node = (OrderMedicineNode*)malloc(sizeof(OrderMedicineNode));
    CHECK_ALLOC_STRUCT(node);
    if (fread(&node->medicineCode, sizeof(int), 1, file) != 1) {
        free(node);
        return NULL;
    }
    int nameLength;
    if (fread(&nameLength, sizeof(int), 1, file) != 1) {
        free(node);
        return NULL;
    }
    node->medicineName = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(node->medicineName);
    if (fread(node->medicineName, sizeof(char), nameLength, file) != nameLength) {
        free(node->medicineName);
        free(node);
        return NULL;
    }
    if (fread(&node->price, sizeof(int), 1, file) != 1) {
        free(node->medicineName);
        free(node);
        return NULL;
    }
    if (fread(&node->quantity, sizeof(int), 1, file) != 1) {
        free(node->medicineName);
        free(node);
        return NULL;
    }
    return node;
}

void* loadOrderProductNodeFromBinary(FILE* file) {
    OrderProductNode* node = (OrderProductNode*)malloc(sizeof(OrderProductNode));
    CHECK_ALLOC_STRUCT(node);
    if (fread(&node->productCode, sizeof(int), 1, file) != 1) {
        free(node);
        return NULL;
    }
    int nameLength;
    if (fread(&nameLength, sizeof(int), 1, file) != 1) {
        free(node);
        return NULL;
    }
    node->productName = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(node->productName);
    if (fread(node->productName, sizeof(char), nameLength, file) != nameLength) {
        free(node->productName);
        free(node);
        return NULL;
    }
    if (fread(&node->price, sizeof(int), 1, file) != 1) {
        free(node->productName);
        free(node);
        return NULL;
    }
    if (fread(&node->quantity, sizeof(int), 1, file) != 1) {
        free(node->productName);
        free(node);
        return NULL;
    }
    return node;
}

int saveOrderToBinary(FILE* file, const void* data) {
    const Order* order = (const Order*)data;
    if (!saveDateToBinary(file, &order->lastModified) ||
        !saveListBinary(file, order->orderProducts, &saveOrderProductToBinary) ||
        !saveListBinary(file, order->orderMedicines, &saveOrderMedicineNodeToBinary) ||
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
    printf("Loading order\n");
    int employeeID;
    if (!order)
        return NULL;
    if (!loadDateFromBinary(&order->lastModified, file)){
        free(order);
        return NULL;
    }
    printf("Date loaded\n");
    order->orderProducts = (LinkedList*)malloc(sizeof(LinkedList));
    CHECK_ALLOC_STRUCT(order->orderProducts);
    initList(order->orderProducts);
    order->orderMedicines = (LinkedList*)malloc(sizeof(LinkedList));
    CHECK_ALLOC_STRUCT(order->orderMedicines);
    initList(order->orderMedicines);

    if (!loadListBinary(file, order->orderProducts, loadOrderProductNodeFromBinary)) {
        free(order);
        return NULL;
    }

    if (!loadListBinary(file, order->orderMedicines, loadOrderMedicineNodeFromBinary)) {
        free(order);
        return NULL;
    }

    if (fread(&order->orderNumber, sizeof(int), 1, file) != 1) {
        free(order);
        return NULL;
    }

    if (fread(&order->customerID, sizeof(int), 1, file) != 1) {
        free(order);
        return NULL;
    }

    if (fread(&employeeID, sizeof(int), 1, file) != 1) {
        free(order);
        return NULL;
    }

    order->employee = findEmployee(employees, numEmployees, employeeID);

    return order;
}

void saveOrder(FILE* file, const void* data) {
    Order* order = (Order*)data;
    saveDate(file, &order->lastModified);
    saveList(file, order->orderProducts, &saveOrderProductNode);
    saveList(file, order->orderMedicines, &saveOrderMedicineNode);
    fprintf(file, "%d %d %d %d\n", order->orderNumber, order->customerID, order->employee->id, order->totalAmount);
}

void saveOrderProductNode(FILE* file, const void* data) {
    OrderProductNode* node = (OrderProductNode*)data;
    fprintf(file, "%d\n", node->productCode);
    int nameLength = (int)strlen(node->productName) + 1;
    fprintf(file, "%d\n", nameLength);
    fprintf(file, "%s\n", node->productName);
    fprintf(file, "%d\n", node->price);
    fprintf(file, "%d\n", node->quantity);
}

void saveOrderMedicineNode(FILE* file, const void* data) {
    OrderMedicineNode* node = (OrderMedicineNode*)data;
    fprintf(file, "%d\n", node->medicineCode);
    int nameLength = (int)strlen(node->medicineName) + 1;
    fprintf(file, "%d\n", nameLength);
    fprintf(file, "%s\n", node->medicineName);
    fprintf(file, "%d\n", node->price);
    fprintf(file, "%d\n", node->quantity);
}

Order* loadOrder(FILE* file, Employee** employees, int numEmployees) {
    Order* order = (Order*)malloc(sizeof(Order));
    CHECK_ALLOC_STRUCT(order);
    loadDate(file, &order->lastModified);
    order->orderProducts = loadList(file, loadOrderProductNode);
    order->orderMedicines = loadList(file, loadOrderMedicineNode);
    int employeeID;
    fscanf(file, "%d %d %d %d", &order->orderNumber, &order->customerID, &employeeID, &order->totalAmount);
    order->employee = findEmployee(employees, numEmployees, employeeID);
    return order;
}

void*  loadOrderProductNode(FILE* file) {
    OrderProductNode* node = (OrderProductNode*)malloc(sizeof(OrderProductNode));
    fscanf(file, "%d", &node->productCode);
    int nameLength;
    fscanf(file, "%d", &nameLength);
    node->productName = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(node->productName);
    fscanf(file, "%s", node->productName);
    fscanf(file, "%d", &node->price);
    fscanf(file, "%d", &node->quantity);
    return node;
}

void* loadOrderMedicineNode(FILE* file) {
    OrderMedicineNode* node = (OrderMedicineNode*)malloc(sizeof(OrderMedicineNode));
    fscanf(file, "%d", &node->medicineCode);
    int nameLength;
    fscanf(file, "%d", &nameLength);
    node->medicineName = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(node->medicineName);
    fscanf(file, "%s", node->medicineName);
    fscanf(file, "%d", &node->price);
    fscanf(file, "%d", &node->quantity);
    return node;
}

void freeOrderProductNode(void* data) {
    OrderProductNode* node = (OrderProductNode*)data;
    free(node->productName);
}

void freeOrderMedicineNode(void* data) {
    OrderMedicineNode* node = (OrderMedicineNode*)data;
    free(node->medicineName);
}

void freeOrder(void* data) {
    Order* order = (Order*)data;
    freeList(order->orderProducts, freeOrderProductNode);
    freeList(order->orderMedicines, freeOrderMedicineNode);
}
