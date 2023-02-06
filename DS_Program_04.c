#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int choice = -1, count = 0, maxIndex = 200;
struct hashItem
{
    char *key, *name, *phone, *address, *city;
    struct hashItem *next;
};
struct hashTable
{
    int size, count; struct hashItem **items;
};
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++) hash = ((hash << 5) + hash) + c;
    return hash;
}
struct hashItem *createItem(char *key, char *name, char *phone, char *address, char *city)
{
    struct hashItem *newItem = (struct hashItem *)malloc(sizeof(struct hashItem));
    newItem->key = (char *)malloc(strlen(key) + 1);
    newItem->name = (char *)malloc(strlen(name) + 1);
    newItem->phone = (char *)malloc(strlen(phone) + 1);
    newItem->address = (char *)malloc(strlen(address) + 1);
    newItem->city = (char *)malloc(strlen(city) + 1);
    strcpy(newItem->key, key);
    strcpy(newItem->name, name);
    strcpy(newItem->phone, phone);
    strcpy(newItem->address, address);
    strcpy(newItem->city, city);
    newItem->next = NULL;
    return newItem;
}
struct hashTable *createTable(int size)
{
    struct hashTable *ht = (struct hashTable *)malloc(sizeof(struct hashTable));
    ht->size = size;
    ht->count = 0;
    ht->items = (struct hashItem **)calloc(ht->size, sizeof(struct hashItem *));
    return ht;
}
void insertItem(struct hashTable *ht, char *key, char *name, char *phone, char *address, char *city)
{
    struct hashItem *newItem = createItem(key, name, phone, address, city);
    int index = hash(key) % ht->size;
    struct hashItem *current = ht->items[index];
    if (current == NULL)
    {
        ht->items[index] = newItem;
        ht->count++;
    }
    else
    {
        while (current->next != NULL) current = current->next;
        current->next = newItem;
    }
}
struct hashItem *searchItem(struct hashTable *ht, char *key)
{
    int index = hash(key) % ht->size;
    struct hashItem *current = ht->items[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0) return current;
        current = current->next;
    }
    return NULL;
}
void deleteItem(struct hashTable *ht, char *key)
{
    int index = hash(key) % ht->size;
    struct hashItem *current = ht->items[index];
    struct hashItem *prev = NULL;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                ht->items[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            ht->count--;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
void displayMenu()
{
    system("cls");
    printf("My Hashed Phone Book\n");
    printf("1. Insert new phone number\n");
    printf("2. View all phone book\n");
    printf("3. Update phone info by name\n");
    printf("4. Remove phone info by name\n");
    printf("5. Search phone by name\n");
    printf("6. Exit\n");
    printf("Choose [ 1 - 6 ] : "); scanf("%d", &choice); getchar();
}
void menu01(struct hashTable *ht)
{
    system("cls");
    char tempName[100] = {}, tempPhone[28] = {}, tempAddr[100] = {}, tempCity[200] = {};
    int valPhone = 0;
    while (strlen(tempName) < 3 || strlen(tempName) > 50)
    {
        printf("Insert name [ 3 - 50 characters ] : "); gets(tempName);
    }
    while (!valPhone)
    {
        printf("Insert phone number [ 08XX-XXXX-XXXX format ] : "); gets(tempPhone);
        if (strlen(tempPhone) != 14) printf("Phone number must be 14 characters long!\n");
        else if (tempPhone[0] != '0' || tempPhone[1] != '8') printf("Phone number must starts with 0 and 8!\n");
        else if (tempPhone[4] != '-' || tempPhone[9] != '-') printf("Invalid format!\n");
        else valPhone = 1;
    }
    while (strcmp(tempAddr + (strlen(tempAddr) - 6), "street") != 0)
    {
        printf("Insert address [ ends with street ] : "); gets(tempAddr);
    }
    while (strlen(tempCity) < 3 || strlen(tempCity) > 100)
    {
        printf("Insert city [ 3 - 100 characters ] : "); gets(tempCity);
    }
    insertItem(ht, tempName, tempName, tempPhone, tempAddr, tempCity);
    printf("Data inserted successfully!\n");
    printf("Press any key to continue... "); getchar();
}
void menu02(struct hashTable *ht)
{
    system("cls");
    if (ht->count == 0) printf("There are no data!\n");
    else
    {
        for (int i = 0; i < ht->size; i++)
        {
            struct hashItem *current = ht->items[i];
            if (current != NULL)
            {
                printf("%d ->\n", i);
                while (current != NULL)
                {
                    printf("\t%s %s %s %s\n", current->name, current->phone, current->address, current->city);
                    current = current->next;
                }
            }
        }
    }
    printf("Press any key to continue... "); getchar();
}
void menu03(struct hashTable *ht)
{
    char tempName[100] = {}, tempPhone[28] = {}, tempAddr[100] = {}, tempCity[200] = {};
    int valPhone = 0;
    while (strlen(tempName) < 3 || strlen(tempName) > 50)
    {
        printf("Insert name [ 3 - 50 characters ] : "); gets(tempName);
    }
    struct hashItem *current = searchItem(ht, tempName);
    if (current == NULL) printf("Not found!\n");
    else
    {
        while (!valPhone)
        {
            printf("Insert phone number [ 08XX-XXXX-XXXX format ] : "); gets(tempPhone);
            if (strlen(tempPhone) != 14) printf("Phone number must be 14 characters long!\n");
            else if (tempPhone[0] != '0' || tempPhone[1] != '8') printf("Phone number must starts with 0 and 8!\n");
            else if (tempPhone[4] != '-' || tempPhone[9] != '-') printf("Invalid format!\n");
            else valPhone = 1;
        }
        while (strcmp(tempAddr + (strlen(tempAddr) - 6), "street") != 0)
        {
            printf("Insert address [ ends with street ] : "); gets(tempAddr);
        }
        while (strlen(tempCity) < 3 || strlen(tempCity) > 100)
        {
            printf("Insert city [ 3 - 100 characters ] : "); gets(tempCity);
        }
        strcpy(current->phone, tempPhone);
        strcpy(current->address, tempAddr);
        strcpy(current->city, tempCity);
        printf("Data updated successfully!\n");
    }
    printf("Press any key to continue... "); getchar();
}
void menu04(struct hashTable *ht)
{
    char tempName[100] = {};
    while (strlen(tempName) < 3 || strlen(tempName) > 50)
    {
        printf("Insert name [ 3 - 50 characters ] : "); gets(tempName);
    }
    struct hashItem *current = searchItem(ht, tempName);
    if (current == NULL) printf("Not found!\n");
    else
    {
        deleteItem(ht, tempName);
        if (ht->count == 0) printf("There are no data!\n");
        else
        {
            for (int i = 0; i < ht->size; i++)
            {
                struct hashItem *current = ht->items[i];
                if (current != NULL)
                {
                    printf("%d ->\n", i);
                    while (current != NULL)
                    {
                        printf("\t%s %s %s %s\n", current->name, current->phone, current->address, current->city);
                        current = current->next;
                    }
                }
            }
        }
    }
    printf("Press any key to continue... "); getchar();
}
void menu05(struct hashTable *ht)
{
    char tempName[100] = {};
    while (strlen(tempName) < 3 || strlen(tempName) > 50)
    {
        printf("Insert name [ 3 - 50 characters ] : "); gets(tempName);
    }
    struct hashItem *current = searchItem(ht, tempName);
    if (current == NULL) printf("Not found!\n");
    else
    {
        printf("Data found!\n");
        printf("%s %s %s %s\n", current->name, current->phone, current->address, current->city);
    }
    printf("Press any key to continue... "); getchar();
}
int main()
{
    struct hashTable *ht = createTable(maxIndex);
    while (choice != 6)
    {
        displayMenu();
        if (choice == 1) menu01(ht);
        else if (choice == 2) menu02(ht);
        else if (choice == 3) menu03(ht);
        else if (choice == 4) menu04(ht);
        else if (choice == 5) menu05(ht);
        else if (choice == 6) return 0;
    }
    return 0;
}