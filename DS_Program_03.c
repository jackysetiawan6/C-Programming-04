#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int choice = -1, type = -1;
struct customer { char Name[20]; int ID, Type; struct customer *next; } *cusHead = NULL;
struct menu { char Name[20]; int ID, Price; struct menu *next; } *menHead = NULL;
struct queue
{
    int Count, Type; char ID[20], Name[20];
    double Total;
    struct order { int Quantity; struct menu *Menu; } Orders[100];
    struct queue *next;
};
struct queue *queHead = NULL, *queTemp = NULL;
char *membership[] = { "Non-Member", "Bronze", "Silver", "Gold", "Platinum" };
void readCustomers()
{
    FILE *fp = fopen("customers.txt", "r");
    while (!feof(fp))
    {
        struct customer *new = (struct customer *)malloc(sizeof(struct customer));
        fscanf(fp, "%d#%[^#]#%d\n", &(new->ID), new->Name, &(new->Type));
        new->next = NULL;
        if (cusHead == NULL) cusHead = new;
        else
        {
            struct customer *temp = cusHead;
            while (temp->next != NULL) temp = temp->next;
            temp->next = new;
        }
    }
    fclose(fp);
}
void viewCustomers()
{
    system("cls");
    printf("  ID  Name%20s      Membership\n", " ");
    struct customer *temp = cusHead;
    while (temp != NULL)
    {
        printf(" %3d  %-24s  %14s\n", temp->ID, temp->Name, membership[temp->Type - 1]);
        temp = temp->next;
    }
    printf("\n");
}
struct customer *searchCustomer(char *name)
{
    int status = -1;
    struct customer *temp = cusHead, *result = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->Name, name) == 0)
        {
            printf("Membership data found!\n");
            printf("Customer ID    : %d\n", temp->ID);
            printf("Customer Name  : %s\n", temp->Name);
            printf("Membership Type: %s\n", membership[temp->Type - 1]);
            
            status = 1; result = temp; break;
        }
        temp = temp->next;
    }
    if (status == -1) printf("Membership data not found!\n");
    return result;
}
void readMenus()
{
    FILE *fp = fopen("menus.txt", "r");
    while (!feof(fp))
    {
        struct menu *new = (struct menu *)malloc(sizeof(struct menu));
        fscanf(fp, "%d#%[^#]#%d\n", &(new->ID), new->Name, &(new->Price));
        new->next = NULL;
        if (menHead == NULL) menHead = new;
        else
        {
            struct menu *temp = menHead;
            while (temp->next != NULL) temp = temp->next;
            temp->next = new;
        }
    }
    fclose(fp);
}
void viewMenus()
{
    system("cls");
    printf(" ID  Name%20s      Price\n", " ");
    struct menu *temp = menHead;
    while (temp != NULL)
    {
        printf(" %2d  %-24s  %9d\n", temp->ID, temp->Name, temp->Price);
        temp = temp->next;
    }
    printf("\n");
}
struct menu *searchMenu(int id)
{
    int status = -1;
    struct menu *temp = menHead, *result = NULL;
    while (temp != NULL)
    {
        if (temp->ID == id)
        {
            status = 1; result = temp; break;
        }
        temp = temp->next;
    }
    if (status == -1) { printf("Invalid menu ID!\n"); printf("\n"); }
    return result;
}
void updateQueue()
{
    if (queHead == NULL) queHead = queTemp;
    else
    {
        struct queue *temp = queHead;
        if (temp->Type < queTemp->Type)
        {
            queTemp->next = temp; queHead = queTemp;
        }
        else
        {
            while (temp->next != NULL && temp->next->Type >= queTemp->Type) temp = temp->next;
            queTemp->next = temp->next; temp->next = queTemp;
        }
    }
}
void viewQueue()
{
    system("cls");
    if (queHead == NULL) printf("There is no order in the queue!\n");
    else
    {
        int current = 1;
        struct queue *temp = queHead;
        while (temp != NULL)
        {
            printf("Queue No. %d\n", current++);
            printf("Order ID     : %s\n", temp->ID);
            printf("Customer Name: %s\n", temp->Name);
            printf("Order List:\n");
            for (int i = 0; i < temp->Count; i++)
            {
                double subtotal = temp->Orders[i].Quantity * temp->Orders[i].Menu->Price;
                printf("   %3d x %-20s %.0lf\n", temp->Orders[i].Quantity, temp->Orders[i].Menu->Name, subtotal);
            }
            printf("Total order is %.0lf.\n", temp->Total);
            temp = temp->next;
            printf("\n");
        }
    }
    printf("\n");
}
void displayMenu()
{
    system("cls");
    printf("Hov\'s Fresh Concoction\n");
    printf("====================== \n");
    printf("1. Add New Order       \n");
    printf("2. View Order Queue    \n");
    printf("3. Serve Order         \n");
    printf("4. Exit                \n");
    printf(">> "); scanf("%d", &choice); getchar();
}
void menu01()
{
    system("cls");
    char tempName[20]; int status = 1; double total = 0;
    printf("Customer Name: "); gets(tempName);
    printf("\n");
    struct customer *cusCurr = searchCustomer(tempName);
    if (cusCurr == NULL)
    {
        cusCurr = (struct customer *)malloc(sizeof(struct customer));
        cusCurr->Type = 0; strcpy(cusCurr->Name, tempName);
    }
    printf("\n");
    printf("Press ENTER to order... "); getchar();
    char orderID[20] = {};
    srand(time(NULL));
    sprintf(orderID, "0%d-%c%c%d%d%d%d", cusCurr->Type, (rand() % 26) + 65, (rand() % 26) + 65
                                       , (rand() % 10), (rand() % 10), (rand() % 10));
    queTemp = (struct queue *)malloc(sizeof(struct queue));
    queTemp->Count = 0; queTemp->Type = cusCurr->Type; queTemp->next = NULL;
    strcpy(queTemp->ID, orderID);
    while (status != -1)
    {
        int menID = -1, quantity = -1;
        struct menu *menCurr = NULL;
        while (menCurr == NULL && status != -1)
        {
            viewMenus();
            printf("Input Menu ID to be added [-1 to finish order]: "); scanf("%d", &menID); getchar();
            if (menID == -1) { status = -1; break; }
            menCurr = searchMenu(menID);
        }
        while (quantity <= 0 && status != -1)
        {
            printf("Input quantity for \"%s\": ", menCurr->Name); scanf("%d", &quantity); getchar();
            if (quantity <= 0) { printf("Invalid quantity (minimum 1)!\n"); getchar(); }
        }
        if (status != -1)
        {
            printf("\"%s\" x %d added to the order.", menCurr->Name, quantity);
            strcpy(queTemp->Name, cusCurr->Name);
            queTemp->Orders[queTemp->Count].Quantity = quantity;
            queTemp->Orders[queTemp->Count].Menu = menCurr;
            queTemp->Count++;
            total += (quantity * menCurr->Price); getchar();
        }
    }
    system("cls");
    printf("Please wait to be seated.\n");
    printf("Below is your order details:\n");
    for (int i = 0; i < queTemp->Count; i++)
    {
        double subtotal = queTemp->Orders[i].Quantity * (double)queTemp->Orders[i].Menu->Price;
        printf("   %3d x %-20s = %.0lf\n", queTemp->Orders[i].Quantity, queTemp->Orders[i].Menu->Name, subtotal);
    }
    queTemp->Total = total;
    printf("Total order is %.0lf.\n", total);
    printf("\n");
    printf("Press ENTER to back to Main Menu... "); updateQueue(); getchar();
}
void menu02()
{
    viewQueue();
    printf("Press ENTER to back to Main Menu... "); getchar();
}
void menu03()
{
    system("cls");
    if (queHead == NULL) printf("There is no order in the queue!\n");
    else
    {
        printf("Finished preparation for order ID %s (%s).\n", queHead->ID, queHead->Name);
        struct queue *temp = queHead;
        queHead = queHead->next;
        free(temp);
    }
    printf("\n");
    printf("Press ENTER to back to Main Menu... "); getchar();
}
void menu04()
{
    system("cls");
    free(queHead); free(queTemp); queHead = NULL; queTemp = NULL;
}
int main()
{
    readCustomers(); readMenus();
    while (choice != 4)
    {
        displayMenu();
        if (choice == 1) menu01();
        else if (choice == 2) menu02();
        else if (choice == 3) menu03();
        else if (choice == 4) menu04();
    }
    return 0;
}