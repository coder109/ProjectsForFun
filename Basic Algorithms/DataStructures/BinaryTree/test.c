#include "BinaryTree.h"

int main() {
    int arr[11] = {1,3,5,7,9,2,4,6,8,10,0};
    BinaryTree* tree = CreateTree(arr[0]);

    // Test Insert
    for(int i = 1; i < 11; i++) {
        InsertIntoTree(arr[i], tree);
    }
    // Basic Check
    printf("Check:\n");
    printf("Data: %d\n", tree->data);
    printf("Data: %d\n", tree->left->data);
    printf("Data: %d\n", tree->right->data);
    printf("Data: %d\n", tree->right->left->data);
    printf("Data: %d\n", tree->right->right->data);
    printf("Data: %d\n", tree->right->right->left->data);
    printf("Data: %d\n", tree->right->right->right->data);
    printf("Data: %d\n", tree->right->right->right->left->data);
    printf("Data: %d\n", tree->right->right->right->right->data);
    printf("Data: %d\n", tree->right->right->right->right->left->data);
    printf("Data: %d\n", tree->right->right->right->right->right->data);
    // Traverse Check
    printf("Traverse:\n");
    PreOrderTraverse(tree);
    printf("\n");
    InOrderTraverse(tree);
    printf("\n");
    PostOrderTraverse(tree);
    printf("\n");

    // Test Delete
    tree = DeleteFromTree(0, tree);
    printf("Traverse 0:\n");
    InOrderTraverse(tree);
    printf("\n");
    tree = DeleteFromTree(10, tree);
    printf("Traverse 10:\n");
    InOrderTraverse(tree);
    printf("\n");
    tree = DeleteFromTree(2, tree);
    printf("Traverse 2:\n");
    InOrderTraverse(tree);
    printf("\n");
    tree = DeleteFromTree(1, tree);
    printf("Traverse 1:\n");
    InOrderTraverse(tree);
    printf("\n");
    tree = DeleteFromTree(1, tree);
    printf("Traverse 1:\n");
    InOrderTraverse(tree);
    printf("\n");

    // Test Find
    for(int i = 0; i < 11; i++) {
        printf("Find %d: %d\n", arr[i], FindInTree(arr[i], tree));
    }

    FreeTree(tree);

    tree = CreateTree(1);
    for(int i = 2; i < 11; i++) {
        InsertIntoTree(i, tree);
    }
    Rotate(tree);
    printf("Rotate:\n");
    InOrderTraverse(tree);
    return 0;
}