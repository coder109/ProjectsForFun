#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* head;
} LinkedList;

LinkedList* CreateEmptyLinkedList();

LinkedListNode* CreateEmptyLinkedListNode();

LinkedListNode* CreateLinkedListNode(void* data);

bool isEmpty(LinkedList* list);

bool Append(void* data, LinkedList* list);

int CountNodeNumber(LinkedList* list);

bool Delete(void* data, LinkedList* list);

int DeleteAll(void* data, LinkedList* list);

int Index(void* data, LinkedList* list);

void FreeAll(LinkedList* list);

#endif