#include "LinkedList.h"

void initList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

void addToList(LinkedList* list, void* item) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->item = item;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void* removeFromList(LinkedList* list, int (*compare)(void*, void*), void* item) {
    ListNode **node = &list->head, *temp = NULL;
    void* removedItem = NULL;

    while (*node != NULL) {
        if (compare((*node)->item, item) == 0) {
            temp = *node;
            *node = (*node)->next;
            removedItem = temp->item;
            free(temp);
            list->size--;
            break;
        }
        node = &(*node)->next;
    }

    return removedItem;
}

void clearList(LinkedList* list, void (*freeItem)(void*)) {
    ListNode *current = list->head, *next;

    while (current != NULL) {
        next = current->next;
        if (freeItem != NULL) {
            freeItem(current->item);
        }
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;
}

void printList(const LinkedList* list, void (*printItem)(void*)) {
    ListNode* node = list->head;

    while (node != NULL) {
        printItem(node->item);
        node = node->next;
    }
}

