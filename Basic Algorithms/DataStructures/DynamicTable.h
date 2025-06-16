#ifndef DYNAMICTABLE_H
#define DYNAMICTABLE_H

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define DYNAMICTABLE_DEFAULT_SIZE 2

typedef struct{
    void* data;
    int size;
} DynamicTableElem;

typedef struct {
    DynamicTableElem* table;
    int max_size;
    int elem_num;
} DynamicTable;

DynamicTable* CreateEmptyDynamicTable(int size);

DynamicTableElem* CreateDynamicTableElem(void* data, int data_size);

DynamicTable* ExpandDynamicTable(DynamicTable* table);

bool MoveElement(DynamicTable* old_table, DynamicTable* new_table);

bool PushIntoTable(void* data, int data_size, DynamicTable* table);

void FreeDynamicTable(DynamicTable* table);

void PrintDynamicTableAsInt(DynamicTable* table);

bool IsElementInTable(DynamicTable* table, void* data);

bool ModElementByIndex(DynamicTable* table, int index, void* data, int data_size);

int GetElementFirstIndex(DynamicTable* table, void* data);

bool DeleteElementFirstOccur(DynamicTable* table, void* data);

bool DeleteElementAllOccur(DynamicTable* table, void* data);

#endif