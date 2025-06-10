#include "DynamicTable.h"

int main(int argc, char **argv) {
    int x = 1, y = 2, z = 3;
    DynamicTable* table = CreateEmptyDynamicTable(DYNAMICTABLE_DEFAULT_SIZE);

    // Push into table
    PushIntoTable(&x, sizeof(int), table);
    PushIntoTable(&y, sizeof(int), table);
    PushIntoTable(&z, sizeof(int), table);

    // Test Deleting
    DeleteElementFirstOccur(table, &x);
    PrintDynamicTableAsInt(table);

    // Push into table once again
    PushIntoTable(&x, sizeof(int), table);
    PushIntoTable(&x, sizeof(int), table);
    PushIntoTable(&x, sizeof(int), table);

    // Test Deleting
    DeleteElementAllOccur(table, &x);
    PrintDynamicTableAsInt(table);

    // Test Modding
    ModElementByIndex(table, 0, &x, sizeof(int));
    PrintDynamicTableAsInt(table);

    // Free
    FreeDynamicTable(table);
    return 0;
}