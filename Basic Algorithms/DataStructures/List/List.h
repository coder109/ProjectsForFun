#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct {
    void* data;
    int data_size;
} ListNode;

typedef struct {
    ListNode** list;
    int data_num;
    int max_size;
} List;

List* CreateEmptyList();

ListNode* CreateListNode(void* data, int data_size);

bool Push(List* list, void* data, int data_size);

void* Pop(List* list);

bool Extend(List* original, List* new_content);

bool Insert(List* list, int index, void* data, int data_size);

bool Remove(List* list, void* data, int data_size);

void Clear(List* list);

void FreeList(List* list);

int Index(List* list, void* data, int data_size);

int Count(List* list, void* data, int data_size);

bool Reverse(List* list);
#endif