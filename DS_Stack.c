#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode
{
    int value;
    struct StackNode *next;
} StackNode;

StackNode *top = NULL;

StackNode *StackNode_new(int value)
{
    StackNode *node = (StackNode*)malloc(sizeof(StackNode));
    node->value = value;
    node->next = NULL;
    return node;
}

void StackNode_insert(int value)
{
    StackNode *node = StackNode_new(value);
    if (!top)
    {
        top = node;
    }
    else
    {
        node->next = top;
        top = node;
    }
}

void StackNode_remove()
{
    if (top)
    {
        StackNode *node = top;
        top = top->next;
        free(node);
    }
}

void StackNode_deleteAll()
{
    while (top)
    {
        StackNode_remove();
    }
}

void printAll()
{
    StackNode *curr = top;
    while (curr)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
}

int main()
{
    StackNode_insert(1);
    StackNode_insert(2);
    StackNode_insert(3);
    StackNode_insert(4);
    StackNode_insert(5);
    printAll();
    printf("\n");
    StackNode_deleteAll();
    printAll();
    return 0;
}