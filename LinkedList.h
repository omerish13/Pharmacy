#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "general.h"

/**
 * Node in a linked list, containing a generic pointer to any type of item and a pointer to the next node.
 */
typedef struct ListNode {
    void* item;               /**< Pointer to the item stored in the node. */
    struct ListNode* next;    /**< Pointer to the next node in the list. */
} ListNode;

/**
 * Linked list structure, containing the head node and the size of the list.
 */
typedef struct {
    ListNode* head;           /**< Pointer to the first node in the list. */
    int size;                 /**< Number of elements in the list. */
} LinkedList;

/**
 * Initializes a linked list to be empty, with no elements.
 * 
 * @param list Pointer to the LinkedList structure to initialize.
 */
void initList(LinkedList* list);

/**
 * Adds a new item to the beginning of the list.
 * 
 * @param list Pointer to the LinkedList structure.
 * @param item Pointer to the item to add to the list.
 */
void addToList(LinkedList* list, void* item);

/**
 * Removes the first occurrence of an item from the list that matches the target, based on a comparison function.
 * 
 * @param list Pointer to the LinkedList structure.
 * @param compare Function used to compare two list items.
 * @param item Pointer to the target item to remove from the list.
 * @return Pointer to the removed item, or NULL if the item was not found.
 */
void* removeFromList(LinkedList* list, int (*compare)(void*, void*), void* item);

/**
 * Iterates over each item in the list and applies a given function, such as printing or modifying items.
 * 
 * @param list Pointer to the LinkedList structure.
 * @param printItem Function applied to each item in the list.
 */
void printList(const LinkedList* list, void (*printItem)(const void*));

/**
 * Saves the contents of a linked list to a binary file, using a given function to save each item.
 * 
 * @param file Pointer to the file to save the list to.
 * @param list Pointer to the LinkedList structure to save.
 * @param saveItem Function used to save each item in the list.
 * @return 1 if the list is successfully saved, 0 otherwise.
 */
int saveListBinary(FILE* file, const LinkedList* list, int (*saveItem)(FILE*, const void*));

/**
 * Loads a linked list from a binary file, using a given function to load each item.
 * 
 * @param list Pointer to the LinkedList structure to load into.
 * @param file Pointer to the file to load the list from.
 * @param loadItem Function used to load each item from the file.
 * @return 1 if the list is successfully loaded, 0 otherwise.
 */
int loadListBinary(FILE* file, LinkedList* list, void* (*loadItem)(FILE*));

/**
 * Saves the contents of a linked list to a file, using a given function to save each item.
 * 
 * @param file Pointer to the file to save the list to.
 * @param list Pointer to the LinkedList structure to save.
 * @param saveItem Function used to save each item in the list.
 */
void saveList(FILE* file, const LinkedList* list, void (*saveItem)(FILE*, const void*));

/**
 * Loads a linked list from a file, using a given function to load each item.
 * 
 * @param file Pointer to the file to load the list from.
 * @param loadItem Function used to load each item from the file.
 * @return Pointer to the loaded LinkedList structure.
 */
LinkedList* loadList(FILE* file, void* (*loadItem)(FILE*));
/**
 * Frees the memory allocated for a linked list and its items.
 * 
 * @param node Pointer to the first node in the list.
 * @param freeItem Function used to free the memory allocated for an item, if necessary. Can be NULL.
 */
void freeList(LinkedList* list, void (*freeItem)(void*));

#endif // LINKEDLIST_H
