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

static BinaryTree* FindMinInTree(BinaryTree* tree) {
    if(tree == NULL) {
        return NULL;
    }
    while(tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

bool DeleteFromTree(int data, BinaryTree* tree) {
    if(tree == NULL) {
        return false;
    }

    BinaryTree* prev = NULL;
    BinaryTree* curr = tree;
    int relative_position = RELATIVE_UNKNOWN;
    while(curr != NULL) {
        if(curr->data > data) {
            prev = curr;
            curr = curr->left;
            relative_position = RELATIVE_LEFT;
        } else if(curr->data < data) {
            prev = curr;
            curr = curr->right;
            relative_position = RELATIVE_RIGHT;
        } else {
            if(curr->left == NULL && curr->right == NULL) {
                if(relative_position == RELATIVE_LEFT) {
                    prev->left = NULL;
                } else if(relative_position == RELATIVE_RIGHT) {
                    prev->right = NULL;
                }
                free(curr);
                return true;
            } else if(curr->left == NULL) {
                prev->right = curr->right;
                free(curr);
                return true;
            } else if(curr->right == NULL) {
                prev->left = curr->left;
                free(curr);
                return true;
            } else {
                BinaryTree* max_in_left = FindMaxInTree(curr->left);
                curr->data = max_in_left->data;
                return DeleteFromTree(max_in_left->data, curr->left);
            }
        }
    }
    return false;
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