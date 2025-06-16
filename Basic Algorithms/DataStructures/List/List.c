#include "List.h"

List* CreateEmptyList() {
    List* list = (List*)malloc(sizeof(List));
    list->list = (ListNode**)malloc(sizeof(ListNode*) * 2);
    list->data_num = 0;
    list->max_size = 2;
    return list;
}

ListNode* CreateListNode(void* data, int data_size) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    node->data_size = data_size;
    return node;
}

static bool ExpandList(List* list) {
    list->max_size *= 2;
    list->list = (ListNode**)realloc(list->list, sizeof(ListNode*) * list->max_size);
    if(list->list == NULL) {
        printf("Expand failed.\n");
        return false;
    }
    return true;
}

bool Push(List* list, void* data, int data_size) {
    ListNode* node = CreateListNode(data, data_size);
    if(list->data_num == list->max_size) {
        if(!ExpandList(list)) {
            return false;
        }
    }
    list->list[list->data_num] = node;
    list->data_num += 1;
    return true;
}

void* Pop(List* list) {
    // Get the value
    void* data = list->list[list->data_num - 1]->data;
    free(list->list[list->data_num - 1]);
    list->data_num -= 1;
    return data;
}

bool Extend(List* original, List* new_content) {
    if(original == NULL || new_content == NULL) {
        printf("Extend failed.\n");
        return false;
    }
    if(original == new_content) {
        printf("Extend failed.\n");
        return false;
    }
    for(int i = 0; i < new_content->data_num; i++) {
        if(!Push(original, new_content->list[i]->data, new_content->list[i]->data_size)) {
            printf("Extend failed.\n");
            return false;
        }
    }
    return true;
}

bool Insert(List* list, int index, void* data, int data_size) {
    if(index > list->data_num) {
        printf("Insert failed.\n");
        return false;
    }

    ListNode* node = CreateListNode(data, data_size);
    if(list->data_num == list->max_size) {
        if(!ExpandList(list)) {
            return false;
        }
    }

    list->data_num += 1;
    for(int i = list->data_num; i > index; i--) {
        list->list[i] = list->list[i - 1];
    }
    list->list[index] = node;
    return true;
}

bool Remove(List* list, void* data, int data_size) {
    for(int i = 0; i < list->data_num; i++) {
        if(list->list[i]->data == data && list->list[i]->data_size == data_size) {
            free(list->list[i]);
            for(int j = i; j < list->data_num - 1; j++) {
                list->list[j] = list->list[j + 1];
            }
            list->data_num -= 1;
            return true;
        }
    }
    return false;
}

void FreeList(List* list) {
    for(int i = 0; i < list->data_num; i++) {
        free(list->list[i]);
    }
    free(list->list);
    free(list);
}

void Clear(List* list) {
    for(int i = 0; i < list->data_num; i++) {
        free(list->list[i]);
    }
    list->data_num = 0;
}

int Index(List* list, void* data, int data_size) {
    for(int i = 0; i < list->data_num; i++) {
        if(list->list[i]->data == data && list->list[i]->data_size == data_size) {
            return i;
        }
    }
    return -1;
}

int Count(List* list, void* data, int data_size) {
    int count = 0;
    for(int i = 0; i < list->data_num; i++) {
        if(list->list[i]->data == data && list->list[i]->data_size == data_size) {
            count += 1;
        }
    }
    return count;
}

bool Reverse(List* list) {
    for(int i = 0; i < list->data_num / 2; i++) {
        ListNode* temp = list->list[i];
        list->list[i] = list->list[list->data_num - i - 1];
        list->list[list->data_num - i - 1] = temp;
    }
    return true;
}