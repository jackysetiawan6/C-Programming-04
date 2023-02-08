#include <stdio.h>
#include <stdlib.h>

typedef struct DLLNode
{
    int value;
    struct DLLNode *next;
    struct DLLNode *prev;
} DLLNode;

DLLNode *head = NULL, *tail = NULL;

DLLNode *DLLNode_new(int value)
{
    DLLNode *node = (DLLNode*)malloc(sizeof(DLLNode));
    node->value = value;
    node->next = node->prev = NULL;
    return node;
}

void DLLNode_pushHead(int value)
{
    DLLNode *new = DLLNode_new(value);
    if (!head) head = tail = new;
    else
    {
        
    }
}

void DLLNode_remove(int value)
{
    //s
}

void printFront()
{
    DLLNode *curr = head;
    while (curr != NULL)
    {
        printf("%02d -> ", curr->value);
        curr = curr->next;
    }
}

void printBack()
{
    DLLNode *curr = tail;
    while (curr != NULL)
    {
        printf("%02d <- ", curr->value);
        curr = curr->prev;
    }
}

int main()
{
    DLLNode_pushHead(5);
    // DLLNode_remove(5);
    // DLLNode_remove(7);
    // DLLNode_remove(17);
    // DLLNode_remove(10);
    printFront();
    printf("\n");
    printBack();
    return 0;
}