#include "LinkedList.h"

void PrintAsInt(LinkedList* list) {
    LinkedListNode* node = list->head->next;
    while(node != NULL) {
        printf("%d\n", *(int*)node->data);
        node = node->next;
    }
}

int main(int argc, char **argv) {
    int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    LinkedList* list = CreateEmptyLinkedList();
    
    // Test Append
    for(int i = 0; i < 20; i++) {
        Append(&arr[i], list);
    }
    //PrintAsInt(list);

    // Test CountNodeNumber
    printf("CountNodeNumber: %d\n", CountNodeNumber(list));

    // Test Delete
    Delete(&arr[9], list);
    Delete(&arr[1], list);
    Delete(&arr[0], list);
    Delete(&arr[0], list);
    PrintAsInt(list);

    // Test DeleteAll
    for(int i = 0; i < 10; i++) {
        Append(&arr[0], list);
    }
    printf("Delete &arr[0]: %d\n", DeleteAll(&arr[0], list));
    PrintAsInt(list);

    // Test Index
    printf("Index of &arr[0]: %d\n", Index(&arr[0], list));
    printf("Index of &arr[10]: %d\n", Index(&arr[10], list));

    FreeAll(list);
    return 0;
}
