#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ================================================================================================= Binary Search Tree

typedef struct BSTNode
{
    char name[100];
    char NIM[100];
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;
BSTNode *root = NULL;
BSTNode *createNode(const char *name, const char *NIM)
{
    BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
    strcpy(newNode->name, name);
    strcpy(newNode->NIM, NIM);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
BSTNode *searchNode(BSTNode *root, const char *name)
{
    if (root == NULL) return NULL;
    else
    {
        if (strcmpi(name, root->name) == 0) return root;
        else if (strcmpi(name, root->name) < 0) return searchNode(root->left, name);
        else return searchNode(root->right, name);
    }
}
BSTNode *insertNode(BSTNode *root, const char *name, const char *NIM)
{
    if (root == NULL) return createNode(name, NIM);
    else
    {
        if (strcmpi(name, root->name) < 0) root->left = insertNode(root->left, name, NIM);
        else if (strcmpi(name, root->name) > 0) root->right = insertNode(root->right, name, NIM);
        return root;
    }
}
BSTNode *deleteNode(BSTNode *root, const char *name)
{
    if (root == NULL) return NULL;
    else
    {
        if (strcmpi(name, root->name) < 0) root->left = deleteNode(root->left, name);
        else if (strcmpi(name, root->name) > 0) root->right = deleteNode(root->right, name);
        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                free(root);
                root = NULL;
            }
            else if (root->left == NULL)
            {
                BSTNode *temp = root;
                root = root->right;
                free(temp);
            }
            else if (root->right == NULL)
            {
                BSTNode *temp = root;
                root = root->left;
                free(temp);
            }
            else
            {
                BSTNode *temp = root->right;
                while (temp->left != NULL) temp = temp->left;
                strcpy(root->name, temp->name);
                strcpy(root->NIM, temp->NIM);
                root->right = deleteNode(root->right, temp->name);
            }
        }
        return root;
    }
}
void viewNode(BSTNode *root)
{
    if (root == NULL) return;
    viewNode(root->left);
    printf("%-30s -- %-8s\n", root->name, root->NIM);
    viewNode(root->right);
}

// ============================================================================================================ Checker

int checkName(const char *name)
{
    int status = 1;
    for (int i = 0; i < strlen(name); i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            status = 0;
        }
    }
    return status;
}
int checkNIM(const char *NIM)
{
    int status = 1;
    for (int i = 0; i < strlen(NIM); i++)
    {
        if (!isdigit(NIM[i]))
        {
            status = 0;
        }
    }
    return status;
}

// ========================================================================================================== Main Menu

int main()
{
    int choice = -1;
    while (choice != 3)
    {
        system("cls");
        printf("======================== Quiz Data Structures =======================\n");
        printf("| [1] | Insert a student data to binary search tree                 |\n");
        printf("| [2] | Delete a student data from binary search tree               |\n");
        printf("| [3] | Close the application                                       |\n");
        printf("=====================================================================\n");
        printf("> Enter your choice: "); scanf("%d", &choice); fflush(stdin);
        switch (choice)
        {
            case 1:
            {
                int check = 0;
                char name[100] = "", NIM[100] = "";
                while (!check)
                {
                    printf("> Enter student name: "); gets(name);
                    if (strlen(name) < 3 || strlen(name) > 50)
                    {
                        printf("> Name must between 3 to 50 characters! Please try again.\n");
                    }
                    else if (checkName(name) == 0)
                    {
                        printf("> Name must contain alphabet and whitespace only! Please try again.\n");
                    }
                    else check = 1;
                }
                while (check)
                {
                    printf("> Enter student NIM : "); gets(NIM);
                    if (strlen(NIM) != 8)
                    {
                        printf("> NIM must contain 8 characters only! Please try again.\n");
                    }
                    else if (checkNIM(NIM) == 0)
                    {
                        printf("> NIM must contain digits only! Please try again.\n");
                    }
                    else check = 0;
                }
                BSTNode *find = searchNode(root, name);
                if (find != NULL)
                {
                    strcpy(find->NIM, NIM);
                    printf("> Student name already exists! Update NIM instead.\n");
                }
                else
                {
                    root = insertNode(root, name, NIM);
                    printf("> Student data has been successfully inserted.\n");
                }
                printf("> Press ENTER to continue..."); getchar();
                break;
            }
            case 2:
            {
                if (root == NULL)
                {
                    printf("> No data registered yet. Please register one.\n");
                    printf("> Press ENTER to continue..."); getchar();
                    break;
                }
                int check = 0;
                char name[100] = "";
                while (!check)
                {
                    printf("> Enter student name: "); gets(name);
                    if (strlen(name) < 3 || strlen(name) > 50)
                    {
                        printf("> Name must between 3 to 50 characters! Please try again.\n");
                    }
                    else if (checkName(name) == 0)
                    {
                        printf("> Name must contain alphabet and whitespace only! Please try again.\n");
                    }
                    else check = 1;
                }
                BSTNode *find = searchNode(root, name);
                if (find == NULL)
                {
                    printf("> Cannot delete because student name does not exist.\n");
                }
                else
                {
                    root = deleteNode(root, name);
                    printf("> Student data has been successfully deleted.\n");
                }
                printf("> Press ENTER to continue..."); getchar();
                break;
            }
            case 3:
            {
                printf("> Thank you for using this application. Goodbye!\n");
                printf("> Press ENTER to continue..."); getchar();
                exit(0);
                break;
            }
            default:
            {
                printf("> Invalid choice! Please try again.\n");
                printf("> Press ENTER to continue..."); getchar();
                break;
            }
        }
    }
    return 0;
}