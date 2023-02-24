#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#define size 1007
#define cc const char
struct hashItem
{
    char title[55], author[30], ISBN[20], ID[30];
    int page;
    struct hashItem *next, *prev;
};
struct hashTable
{
    struct hashItem *head, *tail;
};
struct hashTable *table[size]; int count = 0;
void initializeTable()
{
    for (int i = 0; i < size; i++)
    {
        table[i] = (struct hashTable*)malloc(sizeof(struct hashTable));
        table[i]->head = table[i]->tail = NULL;
    }
    return;
}
int hashFunction(cc *ID)
{
    int sum = 0;
    int length = strlen(ID);
    for (int i = 0; i < length; i++) sum += (int)ID[i];
    return sum % size;
}
struct hashItem *createItem(cc *title, cc *author, cc *ISBN, cc *ID, int page)
{
    struct hashItem *newItem = (struct hashItem*)malloc(sizeof(struct hashItem));
    strcpy(newItem->title, title);
    strcpy(newItem->author, author);
    strcpy(newItem->ISBN, ISBN);
    strcpy(newItem->ID, ID);
    newItem->page = page;
    newItem->next = newItem->prev = NULL;
    return newItem;
}
struct hashItem *searchItem(cc *target)
{
    for (int i = 0; i < size; i++)
    {
        struct hashItem *current = table[i]->head;
        while (current != NULL)
        {
            if (strcmp(current->title, target) == 0 || strcmp(current->ID, target) == 0)
            {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}
void pushHead(int key, struct hashItem *newItem)
{
    if (table[key]->head == NULL)
    {
        table[key]->head = table[key]->tail = newItem;
    }
    else
    {
        newItem->next = table[key]->head;
        table[key]->head->prev = newItem;
        table[key]->head = newItem;
    }
    return;
}
void pushTail(int key, struct hashItem *newItem)
{
    if (table[key]->head == NULL)
    {
        table[key]->head = table[key]->tail = newItem;
    }
    else
    {
        newItem->prev = table[key]->tail;
        table[key]->tail->next = newItem;
        table[key]->tail = newItem;
    }
    return;
}
void pushMid(int key, struct hashItem *newItem)
{
    struct hashItem *tempItem = table[key]->head;
    while (tempItem && strcmp(newItem->title, tempItem->title) >= 0)
    {
        tempItem = tempItem->next;
    }
    newItem->next = tempItem->next;
    newItem->prev = tempItem;
    tempItem->next->prev = newItem;
    tempItem->next = newItem;
    return;
}
void insertItem(cc *title, cc *author, cc *ISBN, cc *ID, int page)
{
    int key = hashFunction(ID);
    struct hashItem *newItem = createItem(title, author, ISBN, ID, page);
    if (table[key]->head == NULL || strcmp(title, table[key]->head->title) < 0) pushHead(key, newItem);
    else if (strcmp(title, table[key]->tail->title) >= 0) pushTail(key, newItem);
    else pushMid(key, newItem);
    return;
}
void popHead(int key)
{
    if (table[key]->head == NULL) return;
    else if (table[key]->head == table[key]->tail)
    {
        free(table[key]->head);
        table[key]->head = table[key]->tail = NULL;
    }
    else
    {
        table[key]->head = table[key]->head->next;
        free(table[key]->head->prev);
        table[key]->head->prev = NULL;
    }
}
void popTail(int key)
{
    if (table[key]->head == NULL) return;
    else if (table[key]->head == table[key]->tail)
    {
        free(table[key]->head);
        table[key]->head = table[key]->tail = NULL;
    }
    else
    {
        table[key]->tail = table[key]->tail->prev;
        free(table[key]->tail->next);
        table[key]->tail->next = NULL;
    }
}
void popMid(int key, const char *id)
{
    struct hashItem *temp = table[key]->head;
    while (temp != NULL && strcmp(temp->ID, id) != 0)
    {
        temp = temp->next;
    }
    if (temp)
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}
void deleteItem(const char *id)
{
    int key = hashFunction(id);
    if (strcmp(table[key]->head->ID, id) == 0) popHead(key);
    else if (strcmp(table[key]->tail->ID, id) == 0) popTail(key);
    else popMid(key, id);
}
void menu00()
{
    // system("cls");
    printf("Bluejack Library\n");
    printf("================\n");
    printf("1. View Book    \n");
    printf("2. Insert Book  \n");
    printf("3. Remove Book  \n");
    printf("4. Exit         \n");
    printf(">> Choice: ");
    return;
}
void menu01()
{
    if (count == 0)
    {
        printf(">> There is no book(s)!\n");
        printf(">> Press ENTER to continue... "); getchar();
    }
    else
    {
        printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| Book ID                 | Book Title                                         | Book Author               | ISBN          | Page Number |\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < size; i++)
        {
            struct hashItem *current = table[i]->head;
            while (current)
            {
                printf("| %-23s | %-50s | %-25s | %-13s | %-011d |\n", current->ID, current->title, current->author, current->ISBN, current->page);
                printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
                current = current->next;
            }
        }
        printf("\n");
        printf(">> Press ENTER to continue... "); getchar();
    }
    return;
}
void menu02()
{
    char title[55] = "", author[30] = "", ISBN[20] = "", ID[30] = "", page[5] = "";
    while (strlen(title) < 5 || strlen(title) > 50)
    {
        printf(">> Input book title       [5-50][unique]: "); gets(title);
        if (strlen(title) < 5 || strlen(title) > 50)
        {
            printf(">> Book's title should between 5 and 50 characters.\n");
        }
        else if (searchItem(title) != NULL)
        {
            printf(">> The book title is already exists!\n");
        }
    }
    while (strlen(author) < 3 || strlen(author) > 25)
    {
        printf(">> Input author name [3-25][Mr. ][Mrs. ]: "); gets(author);
        if (strlen(author) < 3 || strlen(author) > 25)
        {
            printf(">> Book's author should between 5 and 50 characters.\n");
        }
        else if (strncmp(author, "Mr. ", 4) != 0 && strncmp(author, "Mrs. ", 5) != 0)
        {
            printf(">> Author name should starts with \"Mr. \" or \"Mrs. \"!\n");
            strcpy(author, "");
        }
    }
    while (strlen(ISBN) < 10 || strlen(ISBN) > 13 || atoi(ISBN) <= 0)
    {
        printf(">> Input ISBN           [10-13][numeric]: "); gets(ISBN);
        if (strlen(ISBN) < 10 || strlen(ISBN) > 13)
        {
            printf(">> Book's ISBN should between 10 and 13 characters.\n");
        }
        else if (atoi(ISBN) <= 0)
        {
            printf(">> Book's ISBN must be numeric.\n");
        }
    }
    while (atoi(page) < 16)
    {
        printf(">> Input page number             [>= 16]: "); gets(page);
        if (atoi(page) < 16)
        {
            printf(">> Page number should not less than 16 pages.");
        }
    }
    sprintf(ID, "B%05d-%s-%c%c", count + 1, ISBN, toupper(author[0]), toupper(title[0]));
    insertItem(title, author, ISBN, ID, atoi(page));
    count++;
    printf(">> Insert success!\n");
    printf("\n");
    printf(">> Press ENTER to continue... "); getchar();
    return;
}
void menu03()
{
    if (count == 0)
    {
        printf(">> There is no book(s)!\n");
        printf(">> Press ENTER to continue... "); getchar();
    }
    else
    {
        char id[30] ="";
        struct hashItem *currentItem = searchItem(id);
        while (currentItem == NULL)
        {
            printf(">> Input book id to delete: "); gets(id);
            currentItem = searchItem(id);
            if (currentItem == NULL) printf(">> Book not found!\n");
        }
        char input[10] = "";
        printf(">> Book ID    : %s\n", currentItem->ID);
        printf(">> Book Title : %s\n", currentItem->title);
        printf(">> Book Author: %s\n", currentItem->author);
        printf(">> Book ISBN  : %s\n", currentItem->ISBN);
        printf(">> Page Number: %d\n", currentItem->page);
        while (strcmp(input, "y") != 0 && strcmp(input, "n") != 0)
        {
            printf(">> Are you sure [y/n]? "); gets(input);
        }
        if (strcmp(input, "y") == 0)
        {
            deleteItem(id);
            count--;
            printf(">> Delete success!\n");
        }
        printf("\n");
        printf(">> Press ENTER to continue... "); getchar();
    }
    return;
}
void menu04()
{
    printf(">> Thank you for using this application. See you next time. ");
    Sleep(2000);
    return;
}
int main()
{
    initializeTable();
    int choice = -1;
    while (choice != 4)
    {
        menu00(); scanf("%d", &choice); getchar();
        if (choice == 1) menu01();
        else if (choice == 2) menu02();
        else if (choice == 3) menu03();
        else if (choice == 4) menu04();
        else
        {
            printf(">> Invalid input! Please try again. ");
            Sleep(2000);
        }
        choice = -1; fflush(stdin);
    }
    exit(0);
    return 0;
}