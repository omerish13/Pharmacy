#include "Stock.h"
#include <stdio.h>
#include <stdlib.h>

void initStock(Stock* stock) {
    stock->capacity = 10;  // Initial capacity, can be resized later
    stock->productCount = 0;
    stock->products = (Product*)malloc(sizeof(Product) * stock->capacity);
    if (!stock->products) {
        perror("Failed to allocate initial stock");
        exit(EXIT_FAILURE);
    }
}

void showAvailableProducts(const Stock* stock) {
    printf("Available Products:\n");
    for (int i = 0; i < stock->productCount; ++i) {
        printf("%d. ", i + 1);
        printProductDetails(&stock->products[i]);  // Use printProductDetails for each product
    }
}

Product* findProduct(const Stock* stock, int code) {
    for (int i = 0; i < stock->productCount; ++i) {
        if (stock->products[i].code == code) {
            return &stock->products[i];  // Product found
        }
    }
    return NULL;  // Product not found
}

void printStockDetails(const Stock* stock) {
    for (int i = 0; i < stock->productCount; ++i) {
        printProductDetails(&stock->products[i]);
        printf("\n");  // For readability
    }
}