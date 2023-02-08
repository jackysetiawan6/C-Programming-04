#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10000

typedef struct HashNode
{
    char *value;
    struct HashNode *next;
} HashNode;

HashNode *HashTable[SIZE];

unsigned int HashNode_code(char *value)
{
    return (value[0] + value[strlen(value) - 1] + strlen(value)) % SIZE;
}

HashNode *HashNode_new(char *value)
{
    HashNode *node = (HashNode*)malloc(sizeof(HashNode));
    node->value = value;
    node->next = NULL;
    return node;
}

void HashNode_insertLinear(char *value)
{
    unsigned int HashIndex = HashNode_code(value);
    if (!HashTable[HashIndex])
    {
        HashTable[HashIndex] = HashNode_new(value);
    }
    else
    {
        HashNode *curr = HashTable[HashIndex];
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = HashNode_new(value);
    }
}

void HashNode_insertCollision(char *value)
{
    unsigned int HashIndex = HashNode_code(value);
    if (!HashTable[HashIndex])
    {
        HashTable[HashIndex] = HashNode_new(value);
    }
    else
    {
        HashNode *node = HashNode_new(value);
        node->next = HashTable[HashIndex];
        HashTable[HashIndex] = node;
    }
}

void HashNode_removeLinear(char *value)
{
    unsigned int HashIndex = HashNode_code(value);
    if (HashTable[HashIndex])
    {
        HashNode *curr = HashTable[HashIndex];
        if (curr->next == NULL)
        {
            free(curr);
            HashTable[HashIndex] = NULL;
        }
        else
        {
            while (curr->next != NULL)
            {
                if (strcmp(curr->next->value, value) == 0)
                {
                    HashNode *temp = curr->next;
                    curr->next = curr->next->next;
                    free(temp);
                    break;
                }
                curr = curr->next;
            }
        }
    }
}

void HashNode_removeCollision(char *value)
{
    unsigned int HashIndex = HashNode_code(value);
    if (HashTable[HashIndex])
    {
        HashNode *curr = HashTable[HashIndex];
        if (strcmp(curr->value, value) == 0)
        {
            HashTable[HashIndex] = curr->next;
            free(curr);
        }
        else
        {
            while (curr->next != NULL)
            {
                if (strcmp(curr->next->value, value) == 0)
                {
                    HashNode *temp = curr->next;
                    curr->next = curr->next->next;
                    free(temp);
                    break;
                }
                curr = curr->next;
            }
        }
    }
}

void HashNode_deleteAll()
{
    for (int i = 0; i < SIZE; i++)
    {
        if (HashTable[i])
        {
            HashNode *curr = HashTable[i];
            while (curr != NULL)
            {
                HashNode *temp = curr;
                curr = curr->next;
                free(temp);
            }
            HashTable[i] = NULL;
        }
    }
}

void printAll()
{
    for (int i = 0; i < SIZE; i++)
    {
        if (HashTable[i])
        {
            HashNode *curr = HashTable[i];
            while (curr != NULL)
            {
                printf("%s -> ", curr->value);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

int main()
{
    HashNode_insertCollision("Jacky");
    HashNode_insertCollision("Jacky Setiawan");
    HashNode_insertCollision("Jennifer");
    HashNode_insertCollision("Athalia");
    printAll();
    HashNode_deleteAll();
    printAll();
    return 0;
}