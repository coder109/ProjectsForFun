#include "BinaryTree.h"

int main() {
    int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    BinaryTree* tree = CreateTree(arr[0]);
    for(int i = 1; i < 20; i++) {
        InsertIntoTree(arr[i], tree);
    }
    InOrderTraverse(tree);
    return 0;
}