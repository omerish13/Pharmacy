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

void traverseLinkedList(const LinkedList* list, void (*callback)(const void*)) {
    ListNode* node = list->head;
    while (node != NULL) {
        callback(node->item);
        node = node->next;
    }
}

void* traverseAndFind(const LinkedList* list, const void* target, int (*compFunc)(const void*, const void*)) {
    ListNode* node = list->head;
    while (node != NULL) {
        if (compFunc(node->item, target) == 0) {
            return node->item;
        }
        node = node->next;
    }
    return NULL;
}

void* binarySearchLinkedList(const LinkedList* list, const void* target, int (*compFunc)(const void*, const void*)) {
    return (void*)(bsearch(target,list,list->size,sizeof(target),compFunc));
}

void printList(const LinkedList* list, void (*printItem)(const void*)) {
    ListNode* node = list->head;

    while (node != NULL) {
        printItem(node->item);
        node = node->next;
    }
}

int saveListBinary(FILE* file, const LinkedList* list, int (*saveItem)(FILE*, const void*)) {
    ListNode* node = list->head;
    int size = list->size;
    if (fwrite(&size, sizeof(int), 1, file) != 1) {
        return 0;
    }

    while (node != NULL) {
        if (!saveItem(file, node->item))
            return 0;
        node = node->next;
    }

    return 1;
}

int loadListBinary(FILE* file, LinkedList* list, void* (*loadItem)(FILE*)) {
    int size;
    if (fread(&size, sizeof(int), 1, file) != 1) {
        return 0;
    }

    for (int i = 0; i < size; ++i) {
        void* item = loadItem(file);
        addToList(list, item);
    }

    return 1;
}

void saveList(FILE* file, const LinkedList* list, void (*saveItem)(FILE*, const void*)) {
    ListNode* node = list->head;
    fprintf(file, "%d\n", list->size);
    while (node != NULL) {
        saveItem(file, node->item);
        node = node->next;
    }
}

LinkedList* loadList(FILE* file, void* (*loadItem)(FILE*)) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    CHECK_ALLOC_STRUCT(list);

    initList(list);

    int size;
    fscanf(file, "%d", &size);

    for (int i = 0; i < size; ++i) {
        void* item = loadItem(file);
        addToList(list, item);
    }

    return list;
}

void freeList(LinkedList* list, void (*freeItem)(void*)) {

    ListNode* current = list->head;
    ListNode* next;

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

