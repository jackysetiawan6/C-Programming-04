#include <stdio.h>
#include <stdlib.h>

typedef struct SLLNode
{
    int value;
    struct SLLNode *next;
} SLLNode;

SLLNode *head = NULL;

SLLNode *SLLNode_new(int value)
{
    SLLNode *node = (SLLNode*)malloc(sizeof(SLLNode));
    node->value = value;
    node->next = NULL;
    return node;
}

void SLLNode_insert(int value)
{
    SLLNode *node = SLLNode_new(value);
    if (!head)
    {
        head = node;
    }
    else
    {
        node->next = head;
        head = node;
    }
}

void SLLNode_remove(int value)
{
    if (head->value == value)
    {
        SLLNode *temp = head;
        head = head->next;
        free(temp);
    }
    else
    {
        SLLNode *curr = head;
        while (curr->next != NULL)
        {
            if (curr->next->value == value)
            {
                SLLNode *temp = curr->next;
                curr->next = curr->next->next;
                free(temp);
                break;
            }
            curr = curr->next;
        }
    }
}

void SLLNode_deleteAll()
{
    SLLNode *curr = head;
    while (curr != NULL)
    {
        SLLNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = NULL;
}

void printAll()
{
    SLLNode *curr = head;
    while (curr != NULL)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
}

int main()
{
    SLLNode_insert(10);
    SLLNode_insert(20);
    SLLNode_insert(30);
    SLLNode_insert(40);
    SLLNode_insert(50);
    SLLNode_insert(60);
    printAll();
    printf("\n");
    SLLNode_deleteAll();
    printAll();
    return 0;
}