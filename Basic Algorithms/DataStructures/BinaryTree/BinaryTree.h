#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define RELATIVE_UNKNOWN -1
#define RELATIVE_LEFT 0
#define RELATIVE_RIGHT 1

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTree;

BinaryTree* CreateTree(int data);

bool InsertIntoTree(int data, BinaryTree* tree);

bool FindInTree(int data, BinaryTree* tree);

bool DeleteFromTree(int data, BinaryTree* tree);

void PreOrderTraverse(BinaryTree* tree);

void InOrderTraverse(BinaryTree* tree);

void PostOrderTraverse(BinaryTree* tree);

void FreeTree(BinaryTree* tree);

#endif