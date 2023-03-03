#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int count = 0;
typedef struct BST
{
    char name[150]; int rating, playedHours;
    struct BST *left, *right;
} BST;
BST *root = NULL;
BST *createNode(char name[], int rating, int playedHours)
{
    BST *newNode = (BST *)malloc(sizeof(BST));
    strcpy(newNode->name, name);
    newNode->rating = rating;
    newNode->playedHours = playedHours;
    newNode->left = newNode->right = NULL;
    return newNode;
}
BST *insert(BST *root, char name[], int rating, int playedHours)
{
    if (root == NULL)
    {
        printf(">> The game has been added to the database.\n");
        return createNode(name, rating, playedHours);
    }
    if (strcmpi(name, root->name) > 0) root->left = insert(root->left, name, rating, playedHours);
    else if (strcmpi(name, root->name) < 0) root->right = insert(root->right, name, rating, playedHours);
    else
    {
        printf(">> The game already exists in the database. Updated the rating instead.\n");
        root->rating = rating;
    }
    return root;
}
BST *delete(BST *root, char name[])
{
    if (root == NULL) return root;
    if (strcmpi(name, root->name) > 0) root->left = delete(root->left, name);
    else if (strcmpi(name, root->name) < 0) root->right = delete(root->right, name);
    else
    {
        if (root->left == NULL)
        {
            BST *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            BST *temp = root->left;
            free(root);
            return temp;
        }
        BST *temp = root->right;
        while (temp->left != NULL) temp = temp->left;
        strcpy(root->name, temp->name);
        root->rating = temp->rating;
        root->playedHours = temp->playedHours;
        root->right = delete(root->right, temp->name);
    }
    return root;
}
BST *search(BST *root, char name[])
{
    if (root == NULL || strcmp(name, root->name) == 0) return root;
    if (strcmp(name, root->name) > 0) return search(root->left, name);
    return search(root->right, name);
}
typedef struct RPQ
{
    char name[150]; int rating, playedHours;
    struct RPQ *next;
} RPQ;
RPQ *front = NULL;
RPQ *createRPQNode(char name[], int rating, int playedHours)
{
    RPQ *newNode = (RPQ *)malloc(sizeof(RPQ));
    strcpy(newNode->name, name);
    newNode->rating = rating;
    newNode->playedHours = playedHours;
    newNode->next = NULL;
    return newNode;
}
void insertRPQ(char name[], int rating, int playedHours)
{
    RPQ *newNode = createRPQNode(name, rating, playedHours);
    if (front == NULL || newNode->rating > front->rating)
    {
        newNode->next = front;
        front = newNode;
    }
    else
    {
        RPQ *temp = front;
        while (temp->next != NULL && temp->next->rating >= newNode->rating)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}
void inOrder(BST *root)
{
    if (root == NULL) return;
    inOrder(root->left);
    insertRPQ(root->name, root->rating, root->playedHours);
    printf("| %-43s | %-6d | %-12d |\n", root->name, root->rating, root->playedHours);
    inOrder(root->right);
}
int isValidName(char name[])
{
    if (strlen(name) < 1 || strlen(name) > 100) return 0;
    for (int i = 0; i < strlen(name); i++)
    {
        if (!isalnum(name[i]) && !isspace(name[i])) return 0;
    }
    return 1;
}
void menu00()
{
    system("cls");
    printf("=======================================================================\n");
    printf("|                          My Games Database                          |\n");
    printf("=======================================================================\n");
    if (count == 0) printf("| No games in the database.                                           |\n");
    else
    {
        printf("| %-43s | %-6s | %-12s |\n", "Name", "Rating", "Played Hours");
        printf("=======================================================================\n");
        inOrder(root);
    }
    printf("=======================================================================\n");
    printf("| [1] | Insert a new game          | [3] | View by Rating             |\n");
    printf("| [2] | Delete an existing game    | [4] | Exit application           |\n");
    printf("=======================================================================\n");
    return;
}
void menu01()
{
    char name[150] = ""; int rating = -1, playedHours = -1;
    while (isValidName(name) == 0)
    {
        printf(">> Enter the name of the game     : "); gets(name);
        fflush(stdin);
    }
    while (rating < 1 || rating > 10)
    {
        printf(">> Enter the rating of the game   : "); scanf("%d", &rating); getchar();
        fflush(stdin);
    }
    while (playedHours < 0 || playedHours > 2000)
    {
        printf(">> Enter the played hours of game : "); scanf("%d", &playedHours); getchar();
        fflush(stdin);
    }
    root = insert(root, name, rating, playedHours);
    count++;
    printf(">> Press ENTER to continue..."); getchar();
    return;
}
void menu02()
{
    char name[150] = "";
    while (isValidName(name) == 0)
    {
        printf(">> Enter the name of the game     : "); gets(name);
        fflush(stdin);
    }
    BST *temp = search(root, name);
    if (temp == NULL) printf(">> The game does not exist in the database.\n");
    else
    {
        printf(">> The game has been deleted from the database.\n");
        root = delete(root, name);
        count--;
    }
    printf(">> Press ENTER to continue..."); getchar();
    return;
}
void menu03()
{
    if (front == NULL) printf(">> No games in the database.\n");
    else
    {
        printf("=======================================================================\n");
        printf("| %-43s | %-6s | %-12s |\n", "Name", "Rating", "Played Hours");
        printf("=======================================================================\n");
        RPQ *temp = front;
        while (temp != NULL)
        {
            printf("| %-43s | %-6d | %-12d |\n", temp->name, temp->rating, temp->playedHours);
            temp = temp->next;
        }
        printf("=======================================================================\n");
    }
    printf(">> Press ENTER to continue..."); getchar();
}
void menu04()
{
    printf("=======================================================================\n");
    printf("|      Thank you for using this application. See you next time.       |\n");
    printf("=======================================================================\n");
    exit(0);
    return;
}
void initializeData()
{
    root = insert(root, "Grand Chase", 9, 1000); count++;
    root = insert(root, "The Witcher 3", 9, 2000); count++;
    root = insert(root, "Sekiro", 9, 1000); count++;
    root = insert(root, "Dota 2", 9, 213); count++;
    root = insert(root, "Frostpunk", 9, 2); count++;
    root = insert(root, "CSGO", 9, 444); count++;
    root = insert(root, "Elden Ring", 9, 1); count++;
    root = insert(root, "Arknights", 9, 2); count++;
    root = insert(root, "Ace Combat", 9, 5); count++;
}
int main()
{
    initializeData();
    int choice = -1;
    while (choice != 4)
    {
        menu00();
        printf(">> Enter your choice: "); scanf("%d", &choice); getchar();
        fflush(stdin);
        if (choice == 1) menu01();
        else if (choice == 2) menu02();
        else if (choice == 3) menu03();
        else if (choice == 4) menu04();
        else
        {
            printf(">> Invalid choice. Please try again.\n");
            printf(">> Press ENTER to continue..."); getchar();
        }
        choice = -1; front = NULL;
    }
    return 0;
}