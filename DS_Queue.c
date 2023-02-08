#include <stdio.h>
#include <stdlib.h>

enum Membership
{
    NON_MEMBER, BRONZE, SILVER, GOLD, PLATINUM, DIAMOND
};

typedef struct QueueNode
{
    char *name;
    enum Membership membership;
    struct QueueNode *next;
} QueueNode;

QueueNode *first = NULL;

QueueNode *QueueNode_new(char *name, enum Membership membership)
{
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->name = name;
    node->membership = membership;
    node->next = NULL;
    return node;
}

void QueueNode_enqueue(char *name, enum Membership membership)
{
    QueueNode *node = QueueNode_new(name, membership);
    if (!first)
    {
        first = node;
    }
    else
    {
        QueueNode *curr = first;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = node;
    }
}

void QueueNode_dequeue()
{
    if (first)
    {
        QueueNode *temp = first;
        first = first->next;
        free(temp);
    }
}

void QueueNode_deleteAll()
{
    while (first)
    {
        QueueNode_dequeue();
    }
}

void QueueNode_print()
{
    QueueNode *curr = first;
    while (curr != NULL)
    {
        printf("%s %d\n", curr->name, curr->membership);
        curr = curr->next;
    }
}

int main()
{
    QueueNode_enqueue("John", BRONZE);
    QueueNode_enqueue("Mary", SILVER);
    QueueNode_enqueue("Peter", GOLD);
    QueueNode_enqueue("Paul", PLATINUM);
    QueueNode_enqueue("Mark", DIAMOND);
    QueueNode_print();
    QueueNode_dequeue();
    QueueNode_dequeue();
    QueueNode_dequeue();
    QueueNode_dequeue();
    QueueNode_dequeue();
    QueueNode_print();
    return 0;
}