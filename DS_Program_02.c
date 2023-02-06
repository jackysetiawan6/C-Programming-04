#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct data { char type[20]; int furs, meat, firewood, herbs; } database[100] = {};
int choice = -1, count = 0;
void displayMenu()
{
    system("cls");
    printf("Exploration Game            \n");
    printf("============================\n");
    printf("1. Explore the Woods!       \n");
    printf("2. Exploration Records      \n");
    printf("3. Clear Exploration Records\n");
    printf("4. Exit                     \n");
    printf(">> Choice: "); scanf("%d", &choice); getchar();
}
void menu01()
{
    system("cls");
    char type[20] = {};
    int hours = -1, furs = 0, meat = 0, firewood = 0, herbs = 0;
    printf("Explore the Woods!\n");
    printf("==================\n");
    while (strcmp(type, "hunting") != 0 && strcmp(type, "gathering") != 0)
    {
        printf("Choose exploration type [hunting|gathering]: ");
        gets(type);
    }
    while (hours < 1 || hours > 3)
    {
        printf("How long do you want to do %s? [1-3 hours]: ", type);
        scanf("%d", &hours); getchar();
    }
    printf("                                        \n");
    printf("You explored the darkside of the woods!!\n");
    printf("You obtained:                           \n");
    if (strcmp(type, "hunting") == 0)
    {
        furs = rand() % 11, meat = rand() % 6, firewood = 0, herbs = 0;
        printf(" %-02d piece(s) of furs\n", furs);
        printf(" %-02d slice(s) of meat\n", meat);
    }
    else if (strcmp(type, "gathering") == 0)
    {
        firewood = rand() % 101, herbs = rand() % 6, furs = 0, meat = 0;
        printf(" %-02d piece(s) of firewood\n", firewood);
        printf(" %-02d pouch(s) of herbs\n", herbs);
    }
    printf("                                        \n");
    strcpy(database[count].type, type);
    database[count].furs = furs;
    database[count].meat = meat;
    database[count].firewood = firewood;
    database[count].herbs = herbs;
    count++;
    printf("Press enter to continue... "); getchar();
}
void menu02()
{
    system("cls");
    printf("Exploration Records\n");
    printf("===================\n");
    for (int i = 0; i < count; i++)
    {
        printf("Exploration number %03d:\n", i + 1);
        printf("You go %s and got\t: ", database[i].type);
        if (strcmp(database[i].type, "hunting") == 0)
        {
            printf("%d piece(s) of furs and ", database[i].furs);
            printf("%d slice(s) of meat\n", database[i].meat);
        }
        else if (strcmp(database[i].type, "gathering") == 0)
        {
            printf("%d piece(s) of firewood and ", database[i].firewood);
            printf("%d pouch(s) of herbs\n", database[i].herbs);
        }
        printf("\n");
    }
    printf("\n");
    printf("Press enter to continue... "); getchar();
}
void menu03()
{
    system("cls");
    printf("Clear Exploration Records   \n");
    printf("============================\n");
    printf("Exploration records cleared!\n");
    printf("\n");
    count = 0;
    printf("Press enter to continue... "); getchar();
}
void menu04()
{
    system("cls");
    printf("Thank you for playing!\n");
    printf("\n");
    printf("Press enter to exit... "); getchar();
    exit(0);
}
int main()
{
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