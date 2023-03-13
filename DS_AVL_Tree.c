#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Food
{
    char name[100];
    int price, height;
    struct Food *left, *right;
} Food;

int calculateHeight(Food *root)
{
    return root == NULL ? 0 : MAX(calculateHeight(root->left), calculateHeight(root->right)) + 1;
}

int calculateBalanceFactor(Food *root)
{
    return root == NULL ? 0 : calculateHeight(root->left) - calculateHeight(root->right);
}

Food *rotateRight(Food *root)
{
    Food *newParent = root->left;
    root->left = newParent->right;
    newParent->right = root;
    root->height = calculateHeight(root);
    newParent->height = calculateHeight(newParent);
    return newParent;
}

Food *rotateLeft(Food *root)
{
    Food *newParent = root->right;
    root->right = newParent->left;
    newParent->left = root;
    root->height = calculateHeight(root);
    newParent->height = calculateHeight(newParent);
    return newParent;
}

Food *createFood(const char *name, int price)
{
    Food *newFood = malloc(sizeof(Food));
    strcpy(newFood->name, name);
    newFood->price = price;
    newFood->height = 1;
    newFood->left = newFood->right = NULL;
    return newFood;
}

Food *insertFood(Food *root, const char *name, int price)
{
    if (root == NULL)
        return createFood(name, price);
    else if (root->price > price)
        root->left = insertFood(root->left, name, price);
    else if (root->price < price)
        root->right = insertFood(root->right, name, price);
    root->height = calculateHeight(root);
    int balanceFactor = calculateBalanceFactor(root);
    if (balanceFactor > 1)
    {
        if (price > root->left->price)
            root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else if (balanceFactor < -1)
    {
        if (price < root->right->price)
            root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Food *updateFood(Food *root, const char *name, int price)
{
    if (root == NULL)
        return NULL;
    else if (root->price > price)
        root->left = updateFood(root->left, name, price);
    else if (root->price < price)
        root->right = updateFood(root->right, name, price);
    else
    {
        strcpy(root->name, name);
        root->price = price;
    }
    return root;
}

void preOrder(Food *root)
{
    if (root == NULL)
        return;
    printf("Name: %-20s -- Price: %-10d -- Height: %d -- Balance Factor: %d\n", root->name, root->price, root->height, calculateBalanceFactor(root));
    preOrder(root->left);
    preOrder(root->right);
    return;
}

void inOrder(Food *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("Name: %-20s -- Price: %-10d -- Height: %d -- Balance Factor: %d\n", root->name, root->price, root->height, calculateBalanceFactor(root));
    inOrder(root->right);
    return;
}

void postOrder(Food *root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    printf("Name: %-20s -- Price: %-10d -- Height: %d -- Balance Factor: %d\n", root->name, root->price, root->height, calculateBalanceFactor(root));
    return;
}

int main()
{
    system("cls");
    Food *root = NULL;
    printf("===== Initial Food:\n");
    root = insertFood(root, "Sate Padang", 34000);
    root = insertFood(root, "Sate Kambing", 30000);
    root = insertFood(root, "Sate Ayam", 28000);
    root = insertFood(root, "Sate Kelinci", 26000);
    root = insertFood(root, "Sate Taichan", 24000);
    root = insertFood(root, "Sate Babi", 22000);
    inOrder(root);
    printf("\n");
    printf("===== Update Food:\n");
    root = updateFood(root, "Sate Taichan Pedas", 24000);
    inOrder(root);
    return 0;
}