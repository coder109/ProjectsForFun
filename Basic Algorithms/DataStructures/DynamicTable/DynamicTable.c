#include "DynamicTable.h"

DynamicTable* CreateEmptyDynamicTable(int size) {
    DynamicTable* table = (DynamicTable*)malloc(sizeof(DynamicTable) * size);
    if(table == NULL) {
        return NULL;
    }
    table->max_size = size;
    table->table = (DynamicTableElem*)malloc(sizeof(DynamicTableElem) * size);
    table->elem_num = 0;
    return table;
}

DynamicTable* ExpandDynamicTable(DynamicTable* table) {
    if(table == NULL) {
        printf("Cannot expand Table NULL.\n");
        return NULL;
    }
    table->max_size *= 2;
    table->table = (DynamicTableElem*)realloc(table->table, sizeof(DynamicTableElem) * table->max_size);
    return table;
}

bool MoveElement(DynamicTable* old_table, DynamicTable* new_table) {
    if(old_table == NULL || new_table == NULL) {
        printf("Check the tables you want to move is not NULL.\n");
        return false;
    }
    for(int i = 0; i < old_table->elem_num; i++) {
        printf("%d", old_table->table[i]);
        new_table->table[i] = old_table->table[i];
        new_table->elem_num += 1;
    }
    return true;
}

bool PushIntoTable(void* data, int data_size, DynamicTable* table) {
    if(table == NULL) {
        printf("Cannot push elements into Table NULL.\n");
        return false;
    }
    if(table->elem_num == table->max_size) {
        table = ExpandDynamicTable(table);
    }
    table->table[table->elem_num].data = data;
    table->table[table->elem_num].size = data_size;
    table->elem_num += 1;
    return true;
}

bool IsElementInTable(DynamicTable* table, void* data) {
    for(int i = 0; i < table->elem_num; i++) {
        if(table->table[i].data == data) {
            return true;
        }
    }
    return false;
}

void FreeDynamicTable(DynamicTable* table) {
    if(table == NULL) {
        printf("Cannot free Table NULL.\n");
        return;
    }
    free(table->table);
    free(table);
}

void PrintDynamicTableAsInt(DynamicTable* table) {
    printf("Table Size: %d\n", table->elem_num);
    for(int i = 0; i < table->elem_num; i++) {
        void* data = table->table[i].data;
        printf("Element: %d\n", *(int*)data);
    }
}

int GetElementFirstIndex(DynamicTable* table, void* data) {
    for(int i = 0; i < table->elem_num; i++) {
        if(table->table[i].data == data) {
            return i;
        }
    }
    return -1;
}

bool DeleteElementFirstOccur(DynamicTable* table, void* data) {
    int index = GetElementFirstIndex(table, data);
    if(index == -1) {
        return false;
    }
    for(int i = index; i < table->elem_num - 1; i++) {
        table->table[i] = table->table[i + 1];
    }
    table->elem_num -= 1;
    return true;
}

bool DeleteElementAllOccur(DynamicTable* table, void* data) {
    int index = GetElementFirstIndex(table, data);
    while(index != -1) {
        DeleteElementFirstOccur(table, data);
        index = GetElementFirstIndex(table, data);
    }
    return true;
}

bool ModElementByIndex(DynamicTable* table, int index, void* data, int data_size) {
    if(index >= table->elem_num) {
        return false;
    }
    table->table[index].data = data;
    table->table[index].size = data_size;
    return true;
}