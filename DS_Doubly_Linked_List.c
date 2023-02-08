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

void DLLNode_insert(int value)
{
    DLLNode *node = DLLNode_new(value);
    if (!head)
    {
        head = tail = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void DLLNode_remove(int value)
{
    if (head == tail)
    {
        free(head);
        head = tail = NULL;
    }
    else if (head->value == value)
    {
        head = head->next;
        free(head->prev);
        head->prev = NULL;
    }
    else if (tail->value == value)
    {
        tail = tail->prev;
        free(tail->next);
        tail->next = NULL;
    }
    else
    {
        DLLNode *curr = head;
        while (curr != NULL)
        {
            if (curr->value == value)
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
                break;
            }
            curr = curr->next;
        }
    }
}

void DLLNode_deleteAll()
{
    DLLNode *curr = head;
    while (curr != NULL)
    {
        DLLNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = tail = NULL;
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
    DLLNode_insert(10);
    DLLNode_insert(20);
    DLLNode_insert(30);
    DLLNode_insert(40);
    DLLNode_insert(50);
    DLLNode_insert(60);
    printFront();
    printf("\n");
    DLLNode_deleteAll();
    printBack();
    return 0;
}