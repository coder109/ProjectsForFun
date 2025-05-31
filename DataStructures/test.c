#include "DynamicTable.h"

int main(int argc, char **argv) {
    int x = 1, y = 2, z = 3;
    DynamicTable* table = CreateEmptyDynamicTable(DYNAMICTABLE_DEFAULT_SIZE);
    PushIntoTable(&x, sizeof(int), table);
    PushIntoTable(&y, sizeof(int), table);
    PrintDynamicTableAsInt(table);
    PushIntoTable(&z, sizeof(int), table);
    PrintDynamicTableAsInt(table);
    FreeDynamicTable(table);
    return 0;
}