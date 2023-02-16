#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// ======================================================================================= MEMBERSHIP

const char *membership[] = { "Non-Member", "Bronze", "Silver", "Gold", "Platinum" };

// =========================================================================================== ADDONS

int checkName(const char *name)
{
    int status = 1;
    for (int i = 0; i < (int)strlen(name); i++)
    {
        if ((name[i] < 'a' || name[i] > 'z') && (name[i] < 'A' || name[i] > 'Z') && name[i] != ' ')
        {
            status = 0;
        }
    }
    return status;
}
int getMembershipLevel(const char *membership)
{
    int result = -1;
    if (strcmpi(membership, "Non-Member") == 0) result = 1;
    else if (strcmpi(membership, "Bronze") == 0) result = 2;
    else if (strcmpi(membership, "Silver") == 0) result = 3;
    else if (strcmpi(membership, "Gold") == 0) result = 4;
    else if (strcmpi(membership, "Platinum") == 0) result = 5;
    return result;
}
char *getMembershipName(int membership)
{
    char *result = (char*)malloc(20 * sizeof(char));
    if (membership == 1) strcpy(result, "Non-Member");
    else if (membership == 2) strcpy(result, "Bronze");
    else if (membership == 3) strcpy(result, "Silver");
    else if (membership == 4) strcpy(result, "Gold");
    else if (membership == 5) strcpy(result, "Platinum");
    return result;
}
char *generateID(const char *membership)
{
    srand(time(NULL));
    int type = getMembershipLevel(membership);
    char *id = (char*)malloc(10 * sizeof(char));
    sprintf(id, "0%d-%c%c%d%d%d%d", type, (rand() % 26 + 65), (rand() % 26 + 65), (rand() % 10), (rand() % 10), (rand() % 10), (rand() % 10));
    return id;
}

// ========================================================================================= CUSTOMER

struct customer
{
    int id;
    char name[30];
    char membership[15];
    struct customer *next, *prev;
};
struct customer *customerHead = NULL, *customerTail = NULL;
struct customer *createCustomer(int id, const char *name, const char *membership)
{
    struct customer *newCustomer = (struct customer*)malloc(sizeof(struct customer));
    newCustomer->id = id;
    strcpy(newCustomer->name, name);
    strcpy(newCustomer->membership, membership);
    newCustomer->next = newCustomer->prev = NULL;
    return newCustomer;
}
void addCustomer(int id, const char *name, const char *membership)
{
    struct customer *newCustomer = createCustomer(id, name, membership);
    if (customerHead == NULL)
    {
        customerHead = customerTail = newCustomer;
    }
    else if (customerHead == customerTail)
    {
        customerHead->next = newCustomer;
        customerTail->prev = customerHead;
        customerTail = newCustomer;
    }
    else
    {
        customerTail->next = newCustomer;
        newCustomer->prev = customerTail;
        customerTail = newCustomer;
    }
    return;
}
struct customer *searchCustomer(const char *name)
{
    struct customer *current = customerHead;
    while (current)
    {
        if (strcmpi(current->name, name) == 0) return current;
        current = current->next;
    }
    return NULL;
}
void viewCustomer()
{
    system("cls");
    struct customer *current = customerHead;
    printf("==============================================================================\n");
    while (current)
    {
        printf("| [%03d] | Name: %-30s | Membership: %-15s |\n", current->id, current->name, current->membership);
        current = current->next;
    }
    printf("==============================================================================\n");
    return;
}
void loadCustomer()
{
    FILE *file = fopen("customers.txt", "r");
    while (!feof(file))
    {
        int id = -1, type = -1; char name[30] = "";
        fscanf(file, "%d#%[^#]#%d\n", &id, name, &type);
        addCustomer(id, name, getMembershipName(type));
    }
    fclose(file);
    return;
}

// ============================================================================================= MENU

struct menu
{
    int id;
    char name[30];
    double price;
    struct menu *next, *prev;
};
struct menu *menuHead = NULL, *menuTail = NULL;
struct menu *createMenu(int id, const char *name, double price)
{
    struct menu *newMenu = (struct menu*)malloc(sizeof(struct menu));
    newMenu->id = id;
    strcpy(newMenu->name, name);
    newMenu->price = price;
    newMenu->next = newMenu->prev = NULL;
    return newMenu;
}
void addMenu(int id, const char *name, double price)
{
    struct menu *newMenu = createMenu(id, name, price);
    if (menuHead == NULL)
    {
        menuHead = menuTail = newMenu;
    }
    else if (menuHead == menuTail)
    {
        menuHead->next = newMenu;
        newMenu->prev = menuHead;
        menuTail = newMenu;
    }
    else
    {
        menuTail->next = newMenu;
        newMenu->prev = menuTail;
        menuTail = newMenu;
    }
    return;
}
struct menu *searchMenu(int id)
{
    struct menu *current = menuHead;
    while (current)
    {
        if (current->id == id) return current;
        current = current->next;
    }
    return NULL;
}
void viewMenu()
{
    system("cls");
    struct menu *current = menuHead;
    printf("=======================================================================\n");
    while (current)
    {
        printf("| [%02d] | Name: %-34s | Price: %-10.lf |\n", current->id, current->name, current->price);
        current = current->next;
    }
    printf("=======================================================================\n");
    return;
}
void loadMenu()
{
    FILE *file = fopen("menus.txt", "r");
    while (!feof(file))
    {
        int id = -1; char name[30] = ""; double price = 0.0;
        fscanf(file, "%d#%[^#]#%lf\n", &id, name, &price);
        addMenu(id, name, price);
    }
    fclose(file);
    return;
}

// ============================================================================================ QUEUE

struct queue
{
    char id[10];
    char name[30];
    struct menu *menus;
    struct queue *next, *prev;
};
struct queue *queueHead = NULL, *queueTail = NULL;
struct queue *createQueue(const char *id, const char *name)
{
    struct queue *newQueue = (struct queue*)malloc(sizeof(struct queue));
    strcpy(newQueue->id, id);
    strcpy(newQueue->name, name);
    newQueue->next = newQueue->prev = NULL;
    return newQueue;
}

// ============================================================================================= MAIN

char buffer[100] = "";
void menu00()
{
    system("cls");
    printf("=======================================================================\n");
    printf("|                  Hov's Fresh Concoction Study Case                  |\n");
    printf("=======================================================================\n");
    printf("| [1] | Add New Order              | [3] | Serve Order                |\n");
    printf("| [2] | View Order Queue           | [4] | Exit application           |\n");
    printf("=======================================================================\n");
}
void menu01()
{
    int loop = 1, count = 0;
    while (loop)
    {
        int check = 0;
        char tempName[30] = "", choice[100] = "", quantity[100] = "";
        system("cls");
        while (!check)
        {
            printf("> Enter customer name: "); gets(tempName);
            if (strlen(tempName) < 1 || strlen(tempName) > 30)
            {
                printf("> Customer name must more between 1 and 30 characters!\n");
            }
            else if (checkName(tempName) == 0)
            {
                printf("> Customer name must contain alphabet only!\n");
            }
            else check = 1;
        }
        struct customer *currentCustomer = searchCustomer(tempName);
        if (currentCustomer)
        {
            printf("=====================================================================================\n");
            printf("| Membership Data Found!                                                            |\n");
            printf("=====================================================================================\n");
            printf("| ID: %03d | Name: %-30s | Membership Type: %-15s |\n", currentCustomer->id, currentCustomer->name, currentCustomer->membership);
            printf("=====================================================================================\n");
        }
        else printf("> Membership Data Not Found\n");
        printf("> Press ENTER to order... "); gets(buffer); viewMenu();
        while (check)
        {
            printf("> Input Menu ID to be added [-1 to finish order]: "); gets(choice);
            if (atoi(choice) == -1)
            {
                loop = 0; return;
            }
            else if (atoi(choice) < 1 || atoi(choice) > 15)
            {
                printf("> Menu ID must between 1 and 15 only.\n");
            }
            else check = 0;
        }
        struct menu *currentMenu = searchMenu(atoi(choice));
        while (!check)
        {
            printf("> Input quantity for \"%s\": ", currentMenu->name); gets(quantity);
            if (atoi(quantity) < 0 || atoi(quantity) > 1000)
            {
                printf("> Menu Quantity must between 0 and 1000 only.\n");
            }
            else check = 1;
        }
        printf("\"%s\" * %d added to the order data. ", currentMenu->name, atoi(quantity)); gets(buffer);
        //s
        count++;
    }
    double totalPrice = 0.0;
    printf("> Please wait to be seated.\n");
    printf("> Below is your order details:\n");
    for (int i = 0; i < count; i++)
    {
        //
    }
    printf("> Total order is %.lf.\n", totalPrice);
    printf("> Press ENTER to back to main menu... "); gets(buffer);
    return;
}
void menu02()
{
    //s
}
void menu03()
{
    //s
}
void menu04()
{
    printf("=======================================================================\n");
    printf("|      Thank you for using this application. See you next time.       |\n");
    printf("=======================================================================\n");
    Sleep(2000);
    exit(0);
}
int main()
{
    loadMenu(); loadCustomer();
    char choice[100] = "";
    while (strcmp(choice, "4") != 0)
    {
        menu00();
        printf("> Enter your choice: "); gets(choice);
        if (strcmp(choice, "1") == 0) menu01();
        else if (strcmp(choice, "2") == 0) menu02();
        else if (strcmp(choice, "3") == 0) menu03();
        else if (strcmp(choice, "4") == 0) menu04();
        else printf("Invalid input, please try again!\n");
    }
    return 0;
}