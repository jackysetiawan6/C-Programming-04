/*
    Cators Orders - Customer Automated Transaction Ordering System
    1. Membership using BST (Package A, Package B, Package C, Package D, Package E)
    2. Get the customer priority by searching from the BST level (not height)
    3. Package A is the highest priority, Package E is the lowest priority
    4. Customer using Hash Table (Name, Membership Name)
    5. If the customer name already exist, update the membership name and its priority
    6. If the customer name does not exist, insert the customer name and its membership name
    7. View the customer name and its membership name
    8. Serving the customer by its name, while there are similar name, choose the highest priority
    9. Hash Function Rules:
            First Character of the name converted to ASCII number
                (A = 0, B = 1, C = 2, ..., Z = 25) (a = 0, b = 1, c = 2, ..., z = 25)
            Last Character of the name converted to ASCII number
                (A = 0, B = 1, C = 2, ..., Z = 25) (a = 0, b = 1, c = 2, ..., z = 25)
            Multiply the first character with the last character and mod with the table size
    10. Table Size = 1000
    11. Create the hash table using chaining method (linked list)
    12. Please try the program to see the result
    13. Don't forget to save customer data to the file named "customers.in"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define SIZE 1000

// ================================================================================================= Binary Search Tree

struct treeMembership
{
    char name[100];
    struct treeMembership *left, *right;
};
struct treeMembership *rootMembership = NULL;
struct treeMembership *createTreeNode(const char *name)
{
    struct treeMembership *newNode = (struct treeMembership*)malloc(sizeof(struct treeMembership));
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    return newNode;
}
struct treeMembership *insertTreeNode(struct treeMembership *current, const char *name)
{
    if (current == NULL) current = createTreeNode(name);
    else if (strcmp(name, current->name) < 0) current->left = insertTreeNode(current->left, name);
    else if (strcmp(name, current->name) > 0) current->right = insertTreeNode(current->right, name);
    return current;
}
int searchTreeNode(struct treeMembership *current, const char *name)
{
    if (current == NULL) return 0;
    else if (strcmp(name, current->name) == 0) return 1;
    else if (strcmp(name, current->name) < 0) return searchTreeNode(current->left, name);
    else if (strcmp(name, current->name) > 0) return searchTreeNode(current->right, name);
}
int getTreeLevel(struct treeMembership *current, const char *name, int level)
{
    if (current == NULL) return 0;
    else if (strcmp(name, current->name) == 0) return level;
    else if (strcmp(name, current->name) < 0) return getTreeLevel(current->left, name, level + 1);
    else if (strcmp(name, current->name) > 0) return getTreeLevel(current->right, name, level + 1);
}
void viewTree(struct treeMembership *current)
{
    if (current == NULL) return;
    viewTree(current->left);
    printf("%s ", current->name);
    viewTree(current->right);
    return;
}
void initializeTree()
{
    rootMembership = insertTreeNode(rootMembership, "Package A");
    rootMembership = insertTreeNode(rootMembership, "Package B");
    rootMembership = insertTreeNode(rootMembership, "Package C");
    rootMembership = insertTreeNode(rootMembership, "Package D");
    rootMembership = insertTreeNode(rootMembership, "Package E");
    return;
}

// ========================================================================================================= Hash Table

struct hashNode
{
    char name[50];
    char membership[30];
    struct hashNode *next, *prev;
};
struct hashTable
{
    struct hashNode *head, *tail;
};
struct hashTable *Table[10000];
int hashFunction(const char *name)
{
    char firChar = name[0];
    int firKey = firChar >= 'A' && firChar <= 'Z' ? firChar - 'A' : firChar >= 'a' && firChar <= 'z' ? firChar - 'a' : firChar;
    char lasChar = name[strlen(name) - 1];
    int lasKey = lasChar >= 'A' && lasChar <= 'Z' ? lasChar - 'A' : lasChar >= 'a' && lasChar <= 'z' ? lasChar - 'a' : lasChar;
    return (firKey * lasKey) % SIZE;
}
struct hashTable *createHashTable()
{
    struct hashTable *newTable = (struct hashTable*)malloc(sizeof(struct hashTable));
    newTable->head = newTable->tail = NULL;
    return newTable;
}
struct hashNode *createHashNode(const char *name, const char *membership)
{
    struct hashNode *newNode = (struct hashNode*)malloc(sizeof(struct hashNode));
    strcpy(newNode->name, name);
    strcpy(newNode->membership, membership);
    newNode->prev = newNode->next = NULL;
    return newNode;
}
void pushHead(struct hashTable *current, struct hashNode *newNode)
{
    if (current->head == NULL)
    {
        current->head = current->tail = newNode;
    }
    else
    {
        newNode->next = current->head;
        current->head->prev = newNode;
        current->head = newNode;
    }
}
void pushTail(struct hashTable *current, struct hashNode *newNode)
{
    if (current->head == NULL)
    {
        current->head = current->tail = newNode;
    }
    else
    {
        newNode->prev = current->tail;
        current->tail->next = newNode;
        current->tail = newNode;
    }
}
void pushMid(struct hashTable *current, struct hashNode *newNode)
{
    struct hashNode *temp = current->head;
    while (temp != NULL)
    {
        if (strcmp(newNode->name, temp->name) < 0)
        {
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
            break;
        }
        temp = temp->next;
    }
}
struct hashNode *insertHashNode(const char *name, const char *membership)
{
    int key = hashFunction(name);
    int priority = getTreeLevel(rootMembership, membership, 1);
    if (Table[key] == NULL) Table[key] = createHashTable();
    struct hashNode *newNode = createHashNode(name, membership);
    if (Table[key]->head == NULL) pushHead(Table[key], newNode);
    else if (getTreeLevel(rootMembership, Table[key]->head->membership, 1) > priority) pushHead(Table[key], newNode);
    else if (getTreeLevel(rootMembership, Table[key]->tail->membership, 1) < priority) pushTail(Table[key], newNode);
    else pushMid(Table[key], newNode);
    return newNode;
}
struct hashNode *searchHashNode(const char *name)
{
    int key = hashFunction(name);
    if (Table[key] == NULL) return NULL;
    struct hashNode *temp = Table[key]->head;
    while (temp != NULL)
    {
        if (strcmp(name, temp->name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}
struct hashNode *deleteHashNode(const char *name)
{
    int key = hashFunction(name);
    if (Table[key] == NULL) return NULL;
    struct hashNode *temp = Table[key]->head;
    while (temp != NULL)
    {
        if (strcmp(name, temp->name) == 0)
        {
            if (temp->prev == NULL && temp->next == NULL)
            {
                Table[key]->head = Table[key]->tail = NULL;
            }
            else if (temp->prev == NULL)
            {
                temp->next->prev = NULL;
                Table[key]->head = temp->next;
            }
            else if (temp->next == NULL)
            {
                temp->prev->next = NULL;
                Table[key]->tail = temp->prev;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
int getHashTableSize()
{
    int size = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (Table[i] != NULL) size++;
    }
    return size;
}
int getHashNodeLevel(const char *name)
{
    int key = hashFunction(name);
    if (Table[key] == NULL) return 0;
    struct hashNode *temp = Table[key]->head;
    int level = 1;
    while (temp != NULL)
    {
        if (strcmp(name, temp->name) == 0) return level;
        temp = temp->next;
        level++;
    }
    return 0;
}

// ====================================================================================================== Miscellaneous

int countQueue = 0;
void saveFile()
{
    FILE *file = fopen("customers.in", "w");
    for (int i = 0; i < SIZE; i++)
    {
        if (Table[i] != NULL)
        {
            struct hashNode *temp = Table[i]->head;
            while (temp != NULL)
            {
                fprintf(file, "%s#%s\n", temp->name, temp->membership);
                temp = temp->next;
            }
        }
    }
    fclose(file);
}
void loadFile()
{
    FILE *file = fopen("customers.in", "r");
    if (file == NULL) return;
    while (!feof(file))
    {
        char name[100] = "", membership[100] = "";
        fscanf(file, "%[^#]#%[^\n]\n", name, membership);
        insertHashNode(name, membership);
        countQueue++;
    }
    fclose(file);
}

// ========================================================================================================== Main Menu

void menuDisplay01()
{
    system("cls");
    printf("====================================================================\n");
    printf("|                   ~ Welcome to Cators Orders ~                   |\n");
    printf("====================================================================\n");
    printf("| [1] | Check customer's order status.                             |\n");
    printf("| [2] | Create a new order.                                        |\n");
    printf("| [3] | See the order queue.                                       |\n");
    printf("| [4] | Serve an order.                                            |\n");
    printf("| [5] | Close the program.                                         |\n");
    printf("====================================================================\n");
}
void menu01()
{
    if (countQueue == 0) printf("> There is no order in the queue.\n");
    else
    {
        char name[100] = "";
        while (strlen(name) <= 0)
        {
            printf("> Enter customer's name: "); gets(name);
        }
        int level = getHashNodeLevel(name);
        if (level == 0) printf("> Customer's name is not found.\n");
        else printf("> Your order is found at number %d of the queue.\n", level + getHashTableSize() - 1);
    }
    printf("> Press any key to continue..."); getchar();
}
void menu02()
{
    int check = 0;
    char name[100] = "", membership[50] = "";
    while (!check)
    {
        printf("> Enter customer's name: "); gets(name);
        if (strlen(name) <= 0) printf("> Customer's name should between 5 - 30 characters.\n");
        else check = 1;
    }
    struct hashNode *temp = searchHashNode(name);
    while (check)
    {
        printf("> Enter customer's membership: "); gets(membership);
        if (searchTreeNode(rootMembership, membership) == 0) printf("> Membership is not found.\n");
        else check = 0;
    }
    if (temp != NULL)
    {
        deleteHashNode(name);
        insertHashNode(name, membership);
        printf("> Customer's name is already in the queue. Order priority renewed.\n");
    }
    else
    {
        insertHashNode(name, membership);
        countQueue++;
    }
    printf("> Your order has been added to the queue.\n");
    printf("> Press any key to continue..."); getchar();
}
void menu03()
{
    if (!countQueue) printf("> There is no order in the queue.\n");
    else
    {
        printf("> There are %d orders in the queue.\n", countQueue);
        for (int i = 0; i < SIZE; i++)
        {
            if (Table[i] != NULL)
            {
                struct hashNode *temp = Table[i]->head;
                while (temp != NULL)
                {
                    printf("> Name      : %-50s\n", temp->name);
                    printf("  Membership: %-30s\n", temp->membership);
                    temp = temp->next;
                }
            }
        }
    }
    printf("> Press any key to continue..."); getchar();
}
void menu04()
{
    if (!countQueue) printf("> There is no order in the queue.\n");
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (Table[i] != NULL)
            {
                struct hashNode *temp = Table[i]->head;
                printf("> Customer's name      : %s\n", temp->name);
                printf("  Customer's membership: %s\n", temp->membership);
                printf("  Customer's order is ready.\n");
                if (temp->next != NULL)
                {
                    temp->next->prev = NULL;
                    Table[i]->head = temp->next;
                }
                else Table[i]->head = Table[i]->tail = NULL;
                free(temp);
                countQueue--;
                break;
            }
        }
    }
    printf("> Press any key to continue..."); getchar();
}
void menu05()
{
    system("cls");
    printf("====================================================================\n");
    printf("|               ~ Thank you for using this program ~               |\n");
    printf("====================================================================\n");
    exit(0);
}
int main()
{
    initializeTree();
    loadFile();
    int choice = -1;
    while (choice != 5)
    {
        menuDisplay01();
        printf("> Enter your choice [1 - 4]: "); scanf("%d", &choice); getchar();
        if (choice == 1) menu01();
        else if (choice == 2) menu02();
        else if (choice == 3) menu03();
        else if (choice == 4) menu04();
        else if (choice == 5) menu05();
        else printf("> Please enter the number between 1 and 5 only.\n");
        saveFile();
    }
    return 0;
}