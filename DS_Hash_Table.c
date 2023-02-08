#include <stdio.h>

typedef struct HashNode
{
    int value;
    HashNode *next;
} HashNode;

HashNode *HashNode_new(int value)
{
    HashNode *node = (HashNode*)malloc(sizeof(HashNode));
    node->value = value;
    node->next = NULL;
    return node;
}

int main()
{
    return 0;
}