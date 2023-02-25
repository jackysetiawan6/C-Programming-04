#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode
{
    int value;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode *AVLNode_new(int value)
{
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

int AVL_height(AVLNode *curr)
{
    if (!curr) return 0;
    int left = AVL_height(curr->left);
    int right = AVL_height(curr->right);
    return (left > right) ? left + 1 : right + 1;
}

AVLNode *AVLNode_rotateLeft(AVLNode *curr)
{
    AVLNode *temp = curr->right;
    curr->right = temp->left;
    temp->left = curr;
    return temp;
}

AVLNode *AVLNode_rotateRight(AVLNode *curr)
{
    AVLNode *temp = curr->left;
    curr->left = temp->right;
    temp->right = curr;
    return temp;
}

AVLNode *AVLNode_rotateLeftRight(AVLNode *curr)
{
    curr->left = AVLNode_rotateLeft(curr->left);
    return AVLNode_rotateRight(curr);
}

AVLNode *AVLNode_rotateRightLeft(AVLNode *curr)
{
    curr->right = AVLNode_rotateRight(curr->right);
    return AVLNode_rotateLeft(curr);
}

AVLNode *AVLNode_balance(AVLNode *curr)
{
    int left = AVL_height(curr->left);
    int right = AVL_height(curr->right);
    if (left - right > 1)
    {
        int left_left = AVL_height(curr->left->left);
        int left_right = AVL_height(curr->left->right);
        if (left_left >= left_right) curr = AVLNode_rotateRight(curr);
        else curr = AVLNode_rotateLeftRight(curr);
    }
    else if (right - left > 1)
    {
        int right_left = AVL_height(curr->right->left);
        int right_right = AVL_height(curr->right->right);
        if (right_right >= right_left) curr = AVLNode_rotateLeft(curr);
        else curr = AVLNode_rotateRightLeft(curr);
    }
    return curr;
}

AVLNode *AVLNode_insert(AVLNode *curr, int value)
{
    if (!curr) return AVLNode_new(value);
    else if (value < curr->value) curr->left = AVLNode_insert(curr->left, value);
    else if (value > curr->value) curr->right = AVLNode_insert(curr->right, value);
    return AVLNode_balance(curr);
}

AVLNode *AVLNode_search(AVLNode *curr, int value)
{
    if (!curr) return NULL;
    else if (value < curr->value) return AVLNode_search(curr->left, value);
    else if (value > curr->value) return AVLNode_search(curr->right, value);
    else return curr;
}

AVLNode *AVLNode_remove(AVLNode *curr, int value)
{
    if (!curr) return NULL;
    else if (value < curr->value) curr->left = AVLNode_remove(curr->left, value);
    else if (value > curr->value) curr->right = AVLNode_remove(curr->right, value);
    else
    {
        if (!curr->left && !curr->right)
        {
            free(curr);
            curr = NULL;
        }
        else if (!curr->left)
        {
            AVLNode *temp = curr->right;
            free(curr);
            curr = temp;
        }
        else if (!curr->right)
        {
            AVLNode *temp = curr->left;
            free(curr);
            curr = temp;
        }
        else
        {
            AVLNode *temp = curr->right;
            while (temp->left) temp = temp->left;
            curr->value = temp->value;
            curr->right = AVLNode_remove(curr->right, temp->value);
        }
    }
    return curr;
}

void AVLNode_print(AVLNode *curr)
{
    if (!curr) return;
    printf("%d ", curr->value);
    AVLNode_print(curr->left);
    AVLNode_print(curr->right);
}

int main()
{
    AVLNode *root = NULL;
    root = AVLNode_insert(root, 10);
    root = AVLNode_insert(root, 9);
    root = AVLNode_insert(root, 8);
    root = AVLNode_insert(root, 7);
    root = AVLNode_insert(root, 6);
    root = AVLNode_insert(root, 5);
    root = AVLNode_insert(root, 4);
    root = AVLNode_insert(root, 3);
    root = AVLNode_insert(root, 2);
    root = AVLNode_insert(root, 1);
    root = AVLNode_balance(root);
    printf("Root Value : %d\n", root->value);
    printf("Tree Height: %d\n", AVL_height(root));
    AVLNode_print(root);
    printf("\n");
    return 0;
}