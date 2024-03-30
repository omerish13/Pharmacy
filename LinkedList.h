#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

// Node structure for the linked list
typedef struct ListNode {
    void* item;               // Pointer to the item stored in this node
    struct ListNode* next;    // Pointer to the next node in the list
} ListNode;

// Linked list structure
typedef struct {
    ListNode* head;           // Pointer to the first node in the list
    int size;                 // Number of items in the list
} LinkedList;

// Function prototypes
void initList(LinkedList* list);
void addToList(LinkedList* list, void* item);
void* removeFromList(LinkedList* list, int (*compare)(void*, void*), void* item);
void clearList(LinkedList* list, void (*freeItem)(void*));
void printList(const LinkedList* list, void (*printItem)(void*));

#endif // LINKEDLIST_H
