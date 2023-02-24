/*
    Cators Accounting - Centralized Money Management
    1. Create a student BST where each student has name, id, assets, liability, and equity.
    2. Sort the student BST by looking at the value student's assets.
    3. Suppose that you are Gators Admin, that you can add, view, edit, and delete student data.
    4. To add, you need to enter student name, its current liabilities, and current equity.
    5. After that, the system will generate an unique id for every new account.
       ID = ST-XXXXX-YZ where XXXXX is a random five integer, Y is first char of name, and Z is last char of name.
       For example, ST-12345-JN is for Jacky Setiawan
    6. To search for an account, you need to enter a student name or id.
    7. Then, system will show a list with same name or id.
    8. As an admin, you can only edit the student's liability or equity amount.
    9. But you need to make sure that the accounting equation should be balanced.
    10. Deleting a student data will show its data and confirm before deletion.
    11. After each modification, rearrange the BST (if needed).
    12. Do it in 60 minutes (at least add and delete function must be finished).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#define cc const char
int count = 0;
struct tree
{
    char name[50], id[20];
    double assets, liability, equity;
    struct tree *left, *right;
};
struct tree *root = NULL;
struct tree *createTree(cc *name, cc *id, double assets, double liability, double equity)
{
    struct tree *newTree = (struct tree*)malloc(sizeof(struct tree));
    strcpy(newTree->name, name);
    strcpy(newTree->id, id);
    newTree->assets = assets;
    newTree->liability = liability;
    newTree->equity = equity;
    newTree->left = newTree->right = NULL;
    return newTree;
}
struct tree *insertTree(struct tree *current, cc *name, cc *id, double assets, double liability, double equity)
{
    if (current == NULL) return createTree(name, id, assets, liability, equity);
    else if (assets < current->assets) current->left = insertTree(current->left, name, id, assets, liability, equity);
    else if (assets > current->assets) current->right = insertTree(current->right, name, id, assets, liability, equity);
    return current;
}
struct tree *searchTree(struct tree *current, cc *target)
{
    if (current == NULL) return NULL;
    if (strcmp(target, current->name) == 0 || strcmp(target, current->id) == 0) return current;
    if (current->left != NULL) return searchTree(current->left, target);
    if (current->right != NULL) return searchTree(current->right, target);
}
struct tree *deleteTree(struct tree *current, cc *name)
{
    if (current == NULL) return NULL;
    if (strcmp(name, current->name) == 0)
    {
        if (current->left == NULL && current->right == NULL)
        {
            free(current);
            return NULL;
        }
        else if (current->left == NULL)
        {
            struct tree *temp = current->right;
            free(current);
            return temp;
        }
        else if (current->right == NULL)
        {
            struct tree *temp = current->left;
            free(current);
            return temp;
        }
        else
        {
            struct tree *temp = current->right;
            while (temp->left != NULL) temp = temp->left;
            strcpy(current->name, temp->name);
            strcpy(current->id, temp->id);
            current->assets = temp->assets;
            current->liability = temp->liability;
            current->equity = temp->equity;
            current->right = deleteTree(current->right, temp->name);
        }
    }
    else if (current->left != NULL) current->left = deleteTree(current->left, name);
    else if (current->right != NULL) current->right = deleteTree(current->right, name);
    return current;
}
void viewTree(struct tree *current)
{
    if (current == NULL) return;
    viewTree(current->left);
    printf("| %-40s | %-15s | %-15.2lf | %-15.2lf | %-15.2lf |\n", current->name, current->id, current->assets, current->liability, current->equity);
    viewTree(current->right);
}
void menu00()
{
    system("cls");
    printf("Gators Accounting\n");
    printf("=================\n");
    printf("1. Add Student   \n");
    printf("2. View Student  \n");
    printf("3. Edit Student  \n");
    printf("4. Delete Student\n");
    printf("5. Exit          \n");
    printf(">> Choice: ");
    return;
}
void menu01()
{
    char name[50] = "", id[20] = "";
    double assets = -1.0, liability = -1.0, equity = -1.0;
    while (strlen(name) < 5 || strlen(name) > 50)
    {
        printf(">> Enter a student name             [5-50]: "); gets(name);
        if (strlen(name) < 5 || strlen(name) > 50)
        {
            printf(">> Name must between 5 and 50 characters!\n");
        }
    }
    while (liability <= 0.0)
    {
        printf(">> Enter a student liability [more than 0]: "); scanf("%lf", &liability); getchar();
        if (liability <= 0.0)
        {
            printf(">> Liability must be more than 0!\n");
        }
    }
    while (equity <= 0.0)
    {
        printf(">> Enter a student equity    [more than 0]: "); scanf("%lf", &equity); getchar();
        if (equity <= 0.0)
        {
            printf(">> Equity must be more than 0!\n");
        }
    }
    assets = liability + equity;
    srand(time(NULL));
    sprintf(id, "ST-%d%d%d%d%d-%c%c", rand()%10, rand()%10, rand()%10, rand()%10, rand()%10, toupper(name[0]), toupper(name[strlen(name)-1]));
    root = insertTree(root, name, id, assets, liability, equity);
    printf(">> New student data has been added.\n");
    count++;
    printf(">> Press ENTER to continue... "); getchar();
    return;
}
void menu02()
{
    if (root == NULL || count == 0)
    {
        printf(">> There is no student data to view!\n");
        printf(">> Press ENTER to continue... "); getchar();
        return;
    }
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("| Name                                     | ID              | Assets          | Liability       | Equity          |\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    viewTree(root);
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf(">> Press ENTER to continue... "); getchar();
    return;
}
void menu03()
{
    if (root == NULL || count == 0)
    {
        printf(">> There is no student data to edit!\n");
        printf(">> Press ENTER to continue... "); getchar();
        return;
    }
    char name[50] = "";
    while (strlen(name) < 5 || strlen(name) > 50)
    {
        printf(">> Enter a student name             [5-50]: "); gets(name);
        if (strlen(name) < 5 || strlen(name) > 50)
        {
            printf(">> Name must between 5 and 50 characters!\n");
        }
    }
    struct tree *target = searchTree(root, name);
    if (target == NULL)
    {
        printf(">> There is no such account name or id!\n");
    }
    else
    {
        char input[50] = ""; double value = -1.0;
        printf(">> Current student name     : %s\n", target->name);
        printf(">> Current student assets   : %.2lf\n", target->assets);
        printf(">> Current student liability: %.2lf\n", target->liability);
        printf(">> Current student equity   : %.2lf\n", target->equity);
        while (strcmp(input, "liability") != 0 && strcmp(input, "equity") != 0)
        {
            printf(">> Which value you wanna change? [liability/equity]: "); gets(input);
            if (strcmp(input, "liability") != 0 && strcmp(input, "equity") != 0)
            {
                printf(">> Input must be \"liability\" or \"equity\" only!\n");
            }
        }
        while (value <= 0.0)
        {
            printf(">> Enter the new value of %s: ", input); scanf("%lf", &value); getchar();
            if (value <= 0.0)
            {
                printf(">> %s value must be more than 0!\n", input);
            }
        }
        if (strcmp(input, "liability") == 0)
        {
            target->liability = value; target->assets = target->liability + target->equity;
        }
        else if (strcmp(input, "equity") == 0)
        {
            target->equity = value; target->assets = target->liability + target->equity;
        }
        root = deleteTree(root, name);
        root = insertTree(root, name, target->id, target->assets, target->liability, target->equity);
        printf(">> Student data has been updated!\n");
    }
    printf(">> Press ENTER to continue... "); getchar();
    return;
}
void menu04()
{
    if (root == NULL || count == 0)
    {
        printf(">> There is no student data to delete!\n");
        printf(">> Press ENTER to continue... "); getchar();
        return;
    }
    char name[50] = "";
    while (strlen(name) < 5 || strlen(name) > 50)
    {
        printf(">> Enter a student name             [5-50]: "); gets(name);
        if (strlen(name) < 5 || strlen(name) > 50)
        {
            printf(">> Name must between 5 and 50 characters!\n");
        }
    }
    struct tree *target = searchTree(root, name);
    if (target == NULL)
    {
        printf(">> There is no such account name or id!\n");
    }
    else
    {
        char input[50] = "";
        while (strcmp(input, "y") != 0 && strcmp(input, "n") != 0)
        {
            printf(">> Are you sure to delete this account? [y/n] "); gets(input);
            if (strcmp(input, "y") != 0 && strcmp(input, "n") != 0)
            {
                printf(">> Input must be \"y\" or \"n\" only!\n");
            }
        }
        if (strcmp(input, "y") == 0)
        {
            root = deleteTree(root, target->name);
            printf(">> Student account has been deleted.\n");
            count--;
        }
        else if (strcmp(input, "n") == 0)
        {
            printf(">> Deletion has been canceled.\n");
        }
    }
    printf(">> Press ENTER to continue... "); getchar();
    return;
}
void menu05()
{
    printf(">> Thank you for using this application. See you next time. ");
    Sleep(2000);
    return;
}
int main()
{
    int choice = -1;
    while (choice != 5)
    {
        menu00(); scanf("%d", &choice); getchar();
        if (choice == 1) menu01();
        else if (choice == 2) menu02();
        else if (choice == 3) menu03();
        else if (choice == 4) menu04();
        else if (choice == 5) menu05();
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