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