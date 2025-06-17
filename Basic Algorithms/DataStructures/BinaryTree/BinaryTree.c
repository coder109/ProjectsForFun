#include "BinaryTree.h"

BinaryTree* CreateTree(int data) {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

static bool InsertNodeIntoTree(BinaryTree* tree, BinaryTree* neo_node) {
    if(tree == NULL) {
        tree = neo_node;
        return true;
    }
    if(neo_node->data < tree->data) {
        if(tree->left == NULL) {
            tree->left = neo_node;
            return true;
        }
        InsertNodeIntoTree(tree->left, neo_node);
    } else if(neo_node->data > tree->data) {
        if(tree->right == NULL) {
            tree->right = neo_node;
            return true;
        }
        InsertNodeIntoTree(tree->right, neo_node);
    }

    return false;
}

bool InsertIntoTree(int data, BinaryTree* tree) {
    BinaryTree* neo_node = CreateTree(data);

    return InsertNodeIntoTree(tree, neo_node);
}

bool FindInTree(int data, BinaryTree* tree) {
    if(tree == NULL) {
        return false;
    }
    if(data < tree->data) {
        return FindInTree(data, tree->left);
    } else if(data > tree->data) {
        return FindInTree(data, tree->right);
    } else {
        return true;
    }
}

static BinaryTree* FindMaxInTree(BinaryTree* tree) {
    if(tree == NULL) {
        return NULL;
    }
    while(tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}

BinaryTree* DeleteFromTree(int data, BinaryTree* tree) {
    if(tree == NULL) {
        printf("Delete failed, tree is empty.\n");
        return NULL;
    }

    BinaryTree* curr = tree;
    BinaryTree* prev = NULL;
    int relative_position = RELATIVE_UNK;
    while(curr != NULL) {
        if(curr->data == data) {
            if(curr->left != NULL && curr->right != NULL) {
                BinaryTree* max_node = FindMaxInTree(curr->left);
                curr->data = max_node->data;
                return DeleteFromTree(max_node->data, curr->left);
            } else {
                BinaryTree* to_be_deleted = curr;
                BinaryTree* new_root = NULL;
                if(curr->left != NULL) {
                    new_root = curr->left;
                } else if(curr->right != NULL) {
                    new_root = curr->right;
                }
                if(prev == NULL) { // Node to be deleted is the root node
                    free(to_be_deleted);
                    return new_root; // Return the new root node
                } else if(relative_position == RELATIVE_LEFT) {
                    prev->left = new_root;
                } else if(relative_position == RELATIVE_RIGHT) {
                    prev->right = new_root;
                }
                free(to_be_deleted);
                return tree; // Return the updated tree
            }
        }
        prev = curr;
        if(curr->data > data) {
            curr = curr->left;
            relative_position = RELATIVE_LEFT;
        } else {
            curr = curr->right;
            relative_position = RELATIVE_RIGHT;
        }
    }
    printf("Delete failed, data not found.\n");
    return tree; // Return the original tree if data not found
}

void PreOrderTraverse(BinaryTree* tree) {
    if(tree == NULL) {
        return;
    }
    printf("%d ", tree->data);
    PreOrderTraverse(tree->left);
    PreOrderTraverse(tree->right);
}

void InOrderTraverse(BinaryTree* tree) {
    if(tree == NULL) {
        return;
    }
    InOrderTraverse(tree->left);
    printf("%d ", tree->data);
    InOrderTraverse(tree->right);
}

void PostOrderTraverse(BinaryTree* tree) {
    if(tree == NULL) {
        return;
    }
    PostOrderTraverse(tree->left);
    PostOrderTraverse(tree->right);
    printf("%d ", tree->data);
}

void FreeTree(BinaryTree* tree) {
    if(tree == NULL) {
        return;
    }
    FreeTree(tree->left);
    FreeTree(tree->right);
    free(tree);
}