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

bool DeleteElementByIndex(DynamicTable* table, int index);

DynamicTableElem* GetElementByIndex(DynamicTable* table, int index);

bool PushIntoTable(void* data, int data_size, DynamicTable* table);

void FreeDynamicTable(DynamicTable* table);

void PrintDynamicTableAsInt(DynamicTable* table);

#endif