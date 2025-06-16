#include "List.h"

void PrintAsInt(List* list) {
    for(int i = 0; i < list->data_num; i++) {
        printf("%d\n", *(int*)list->list[i]->data);
    }
}

int main() {
    int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    List* list_a = CreateEmptyList();
    List* list_b = CreateEmptyList();

    // Test Push
    for(int i = 0; i < 20; i++) {
        Push(list_a, &arr[i], sizeof(int));
    }
    for(int i = 0; i < 10; i++) {
        Push(list_b, &arr[i], sizeof(int));
    }
    //PrintAsInt(list);

    // Test Extend
    Extend(list_a, list_b);
    //PrintAsInt(list_a);

    // Test Pop
    for(int i = 0; i < 10; i++) {
        void* data = Pop(list_a);
        //printf("%d\n", *(int*)data);
    }
    //PrintAsInt(list_a);

    // Test Insert
    for(int i = 0; i < 20; i++) {
        Insert(list_a, i, &arr[0], sizeof(int));
    }
    //PrintAsInt(list_a);

    // Test Remove
    for(int i = 0; i < 20; i++) {
        Remove(list_a, &arr[0], sizeof(int));
    }
    //PrintAsInt(list_a);

    // Test Index
    for(int i = 0; i < 20; i++) {
        //printf("%d\n", Index(list_a, &arr[i], sizeof(int)));
    }

    // Test Count
    //Extend(list_a, list_b);
    for(int i = 0; i < 20; i++) {
        //printf("%d\n", Count(list_a, &arr[i], sizeof(int)));
    }

    // Test Reverse
    Reverse(list_a);
    PrintAsInt(list_a);

    // Test Clear
    Clear(list_a);
    //PrintAsInt(list_a);

    FreeList(list_a);
    FreeList(list_b);

    return 0;
}