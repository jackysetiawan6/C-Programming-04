#include <stdio.h>
#include <stdlib.h>

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
    node->left = node->right = NULL;
    return node;
}

BSTNode *BSTNode_insert(BSTNode *curr, int value)
{
    BSTNode *node = BSTNode_new(value);
    if (!curr) return node;
    else if (value < curr->value) curr->left = BSTNode_insert(curr->left, value);
    else if (value > curr->value) curr->right = BSTNode_insert(curr->right, value);
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
            // Sucessor
            BSTNode *temp = curr->right;
            while (temp->left) temp = temp->left;
            curr->value = temp->value;
            curr->right = BSTNode_remove(curr->right, temp->value);

            // Predecessor
            // BSTNode *temp = curr->left;
            // while (temp->right) temp = temp->right;
            // curr->value = temp->value;
            // curr->left = BSTNode_remove(curr->left, temp->value);
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

void printInfix(BSTNode *curr)
{
    if (!curr) return;
    printInfix(curr->left);
    printf("%d ", curr->value);
    printInfix(curr->right);
}

void printPostfix(BSTNode *curr)
{
    if (!curr) return;
    printPostfix(curr->left);
    printPostfix(curr->right);
    printf("%d ", curr->value);
}

int main()
{
    system("cls");
    BSTNode *root = NULL;
    root = BSTNode_insert(root, 20);
    root = BSTNode_insert(root, 10);
    root = BSTNode_insert(root, 5);
    root = BSTNode_insert(root, 15);
    root = BSTNode_insert(root, 30);
    root = BSTNode_insert(root, 40);
    printInfix(root);
    printf("\n");
    root = BSTNode_remove(root, 15);
    printInfix(root);
    return 0;
}