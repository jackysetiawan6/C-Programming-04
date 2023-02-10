#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct BSTMembership
{
    char *name;
    struct BSTMembership *left;
    struct BSTMembership *right;
} BSTMembership;

typedef struct BSTCustomer
{
    char *name;
    char *membership;
    struct BSTCustomer *left;
    struct BSTCustomer *right;
} BSTCustomer;

BSTMembership *rootMembership = NULL;
BSTCustomer *rootCustomer = NULL;

BSTCustomer *createCustomer(char *name, char *membership)
{
    BSTCustomer *newCustomer = (BSTCustomer *)malloc(sizeof(BSTCustomer));
    newCustomer->name = (char *)malloc(sizeof(char) * strlen(name));
    newCustomer->membership = (char *)malloc(sizeof(char) * strlen(membership));
    strcpy(newCustomer->name, name);
    strcpy(newCustomer->membership, membership);
    newCustomer->left = newCustomer->right = NULL;
    return newCustomer;
}

BSTMembership *createMembership(char *name)
{
    BSTMembership *newMembership = (BSTMembership *)malloc(sizeof(BSTMembership));
    newMembership->name = (char *)malloc(sizeof(char) * strlen(name));
    strcpy(newMembership->name, name);
    newMembership->left = newMembership->right = NULL;
    return newMembership;
}

BSTCustomer *insertCustomer(BSTCustomer *root, char *name, char *membership)
{
    if (!root) return createCustomer(name, membership);
    if (strcmp(root->name, name) > 0) root->left = insertCustomer(root->left, name, membership);
    else if (strcmp(root->name, name) < 0) root->right = insertCustomer(root->right, name, membership);
    return root;
}

BSTMembership *insertMembership(BSTMembership *root, char *name)
{
    if (!root) return createMembership(name);
    if (strcmpi(root->name, name) > 0) root->left = insertMembership(root->left, name);
    else if (strcmpi(root->name, name) < 0) root->right = insertMembership(root->right, name);
    return root;
}

BSTCustomer *searchCustomer(BSTCustomer *root, char *name)
{
    if (!root) return NULL;
    if (strcmp(root->name, name) == 0) return root;
    if (strcmp(root->name, name) > 0) return searchCustomer(root->left, name);
    return searchCustomer(root->right, name);
}

BSTMembership *searchMembership(BSTMembership *root, char *name)
{
    if (!root) return NULL;
    if (strcmpi(root->name, name) == 0) return root;
    if (strcmpi(root->name, name) > 0) return searchMembership(root->left, name);
    return searchMembership(root->right, name);
}

BSTCustomer *deleteCustomer(BSTCustomer *root, char *name)
{
    if (!root) return NULL;
    if (strcmp(root->name, name) > 0) root->left = deleteCustomer(root->left, name);
    else if (strcmp(root->name, name) < 0) root->right = deleteCustomer(root->right, name);
    else
    {
        if (root->left == NULL)
        {
            BSTCustomer *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            BSTCustomer *temp = root->left;
            free(root);
            return temp;
        }
        BSTCustomer *temp = root->right;
        while (temp->left) temp = temp->left;
        strcpy(root->name, temp->name);
        strcpy(root->membership, temp->membership);
        root->right = deleteCustomer(root->right, temp->name);
    }
    return root;
}

void viewCustomer(BSTCustomer *root)
{
    if (!root) return;
    viewCustomer(root->left);-+
    printf("= %-50s %-15s =\n", root->name, root->membership);
    viewCustomer(root->right);
}

void menu01()
{
    int status = 0;
    char name[100] = "", membership[100] = "";
    printf("==========================================\n");
    while (strlen(name) < 3 || strlen(name) > 50)
    {
        printf("> Enter customer name      : ");
        gets(name);
        if (strlen(name) < 3 || strlen(name) > 50)
        {
            printf("Name must between 3 and 50 characters long. Please try again. ");
            Sleep(1000);
            printf("\n");
        }
    }
    while (!status)
    {
        printf("> Enter customer membership: ");
        gets(membership);
        if (searchMembership(rootMembership, membership))
        {
            status = 1;
        }
        else
        {
            printf("Invalid membership. Please try again. ");
            Sleep(1000);
            printf("\n");
        }
    }
    if (searchCustomer(rootCustomer, name))
    {
        printf("Customer already exists! Updated membership. ");
        strcpy(searchCustomer(rootCustomer, name)->membership, membership);
    }
    else
    {
        rootCustomer = insertCustomer(rootCustomer, name, membership);
        printf("Customer added successfully! ");
    }
    Sleep(1000);
}

void menu02()
{
    system("cls");
    printf("======================================================================\n");
    printf("= Customer Name                                      Membership      =\n");
    printf("======================================================================\n");
    if (rootCustomer) viewCustomer(rootCustomer);
    else printf("> No customer found.\n");
    printf("======================================================================\n");
    printf("> Press any key to continue... "); getchar();
}

void menu03()
{
    char name[100] = "";
    printf("==========================================\n");
    while (strlen(name) < 3 || strlen(name) > 50)
    {
        printf("> Enter customer name: ");
        gets(name);
        if (strlen(name) < 3 || strlen(name) > 50)
        {
            printf("Name must between 3 and 50 characters long. Please try again. ");
            Sleep(1000);
            printf("\n");
        }
    }
    if (searchCustomer(rootCustomer, name))
    {
        rootCustomer = deleteCustomer(rootCustomer, name);
        printf("Customer found! Deleted successfully. ");
        Sleep(1000);
    }
    else printf("Customer not found! Delete cancelled. ");
    Sleep(1000);
}

int main()
{
    rootMembership = insertMembership(rootMembership, "Non-Member");
    rootMembership = insertMembership(rootMembership, "Gold");
    rootMembership = insertMembership(rootMembership, "Bronze");
    rootMembership = insertMembership(rootMembership, "Platinum");
    rootMembership = insertMembership(rootMembership, "Silver");
    char choice[100] = "";
    while (atoi(choice) != 4)
    {
        system("cls");
        printf("========= Hov's Fresh Concoction =========\n");
        printf("= 1. Add a new customer                  =\n");
        printf("= 2. View customer                       =\n");
        printf("= 3. Delete customer                     =\n");
        printf("= 4. Exit                                =\n");
        printf("==========================================\n");
        printf("> Choose an option [1 - 4]: ");
        gets(choice);
        switch (atoi(choice))
        {
            case 1: menu01(); break;
            case 2: menu02(); break;
            case 3: menu03(); break;
            case 4: exit(0); break;
            default: printf("Invalid choice. Please try again. "); Sleep(1000); break;
        }
    }
    return 0;
}