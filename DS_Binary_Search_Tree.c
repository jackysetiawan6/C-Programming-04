#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct BSTNode
{
    int value;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *BSTNode_new(int value)
{
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode *BSTNode_insert(BSTNode *curr, BSTNode *node)
{
    if (!curr) return node;
    else if (node->value < curr->value) curr->left = BSTNode_insert(curr->left, node);
    else if (node->value > curr->value) curr->right = BSTNode_insert(curr->right, node);
    return curr;
}

BSTNode *BSTNode_search(BSTNode *curr, int value)
{
    if (!curr) return NULL;
    else if (value < curr->value) return BSTNode_search(curr->left, value);
    else if (value > curr->value) return BSTNode_search(curr->right, value);
    else return curr;
}

BSTNode *BSTNode_remove(BSTNode *curr, int value)
{
    if (!curr) return NULL;
    else if (value < curr->value) curr->left = BSTNode_remove(curr->left, value);
    else if (value > curr->value) curr->right = BSTNode_remove(curr->right, value);
    else
    {
        if (!curr->left && !curr->right)
        {
            free(curr);
            curr = NULL;
        }
        else if (!curr->left)
        {
            BSTNode *temp = curr->right;
            free(curr);
            curr = temp;
        }
        else if (!curr->right)
        {
            BSTNode *temp = curr->left;
            free(curr);
            curr = temp;
        }
        else
        {
            BSTNode *temp = curr->right;
            while (temp->left) temp = temp->left;
            curr->value = temp->value;
            curr->right = BSTNode_remove(curr->right, temp->value);
        }
    }
    return curr;
}

BSTNode *BSTNode_deleteAll(BSTNode *curr)
{
    while (curr)
    {
        curr = BSTNode_remove(curr, curr->value);
    }
    return curr;
}

void printPrefix(BSTNode *curr)
{
    if (!curr) return;
    printf("%d ", curr->value);
    printPrefix(curr->left);
    printPrefix(curr->right);
}

void printPostfix(BSTNode *curr)
{
    if (!curr) return;
    printPostfix(curr->left);
    printPostfix(curr->right);
    printf("%d ", curr->value);
}

void printInfix(BSTNode *curr)
{
    if (!curr) return;
    printInfix(curr->left);
    printf("%d ", curr->value);
    printInfix(curr->right);
}

int main()
{
    system("cls");
    BSTNode *root = NULL;
    root = BSTNode_insert(root, BSTNode_new(20));
    root = BSTNode_insert(root, BSTNode_new(10));
    root = BSTNode_insert(root, BSTNode_new(5));
    root = BSTNode_insert(root, BSTNode_new(15));
    root = BSTNode_insert(root, BSTNode_new(30));
    root = BSTNode_insert(root, BSTNode_new(40));
    printInfix(root);
    printf("\n");
    root = BSTNode_deleteAll(root);
    printInfix(root);
    return 0;
}