#include "LinkedList.h"

LinkedListNode* CreateEmptyLinkedListNode() {
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node->data = NULL;
    node->next = NULL;
    return node;
}

LinkedList* CreateEmptyLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = CreateEmptyLinkedListNode();
    return list;
}

LinkedListNode* CreateLinkedListNode(void* data) {
    LinkedListNode* node = CreateEmptyLinkedListNode();
    node->data = data;
    return node;
}

bool isEmpty(LinkedList* list) {
    return list->head->next == NULL;
}

bool Append(void* data, LinkedList* list) {
    LinkedListNode* node = CreateLinkedListNode(data);
    if(node == NULL) {
        printf("Append failed.\n");
        return false;
    }
    if(isEmpty(list)) {
        list->head->next = node;
    } else {
        LinkedListNode* last = list->head->next;
        while(last->next != NULL) {
            last = last->next;
        }
        last->next = node;
    }
    return true;
}

int CountNodeNumber(LinkedList* list) {
    int count = 0;
    LinkedListNode* node = list->head->next;
    while(node != NULL) {
        count += 1;
        node = node->next;
    }
    return count;
}

bool Delete(void* data, LinkedList* list) {
    LinkedListNode* node = list->head->next;
    LinkedListNode* prev = list->head;
    while(node != NULL) {
        if(node->data == data) {
            prev->next = node->next;
            free(node);
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

int DeleteAll(void* data, LinkedList* list) {
    int delete_count = 0;
    LinkedListNode* node = list->head->next;
    LinkedListNode* prev = list->head;
    while(node != NULL) {
        if(node->data == data) {
            prev->next = node->next;
            free(node);
            node = prev->next;
            delete_count += 1;
        } else {
            prev = node;
            node = node->next;
        }
    }
    return delete_count;
}

int Index(void* data, LinkedList* list) {
    int index = 0;
    LinkedListNode* node = list->head->next;
    while(node != NULL) {
        if(node->data == data) {
            return index;
        }
        index += 1;
        node = node->next;
    }
    return -1;
}

void FreeAll(LinkedList* list) {
    LinkedListNode* node = list->head->next;
    while(node != NULL) {
        LinkedListNode* next = node->next;
        free(node);
        node = next;
    }
    free(list->head);
    free(list);
}