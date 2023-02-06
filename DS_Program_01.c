#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct PC
{
    char Motherboard[20], Processor[20], VGA[20];
    int RAM;
    double Price;
};
struct PC PCArr[100];
int choice = 0, count = 0;
void menu()
{
    system("cls");
    printf("===========================================================================================================================\n");
    printf("||                                                   Data Structure 01                                                   ||\n");
    printf("===========================================================================================================================\n");
    printf("|| 1. Display PC Data                                                                                                    ||\n");
    printf("|| 2. Insert PC Data                                                                                                     ||\n");
    printf("|| 3. Modify PC Data                                                                                                     ||\n");
    printf("|| 4. Delete PC Data                                                                                                     ||\n");
    printf("|| 5. Exit                                                                                                               ||\n");
    printf("===========================================================================================================================\n");
    printf(">> Choice: "); scanf("%d", &choice); getchar();
}
void view()
{
    if (!count)
    {
        printf("No data to display.\n");
        return;
    }
    printf("===========================================================================================================================\n");
    printf("|| No ||     Motherboard     ||      Processor      ||         VGA         ||         RAM         ||        Price        ||\n");
    printf("===========================================================================================================================\n");
    for (int i = 1; i <= count; i++)
    {
        printf("|| %02d || %-19s || %-19s || %-19s || %-19d || %-19.2lf ||\n", i, PCArr[i].Motherboard, PCArr[i].Processor, PCArr[i].VGA, PCArr[i].RAM, PCArr[i].Price);
    }
    printf("===========================================================================================================================\n");
}
void insert()
{
    char Motherboard[20], Processor[20], VGA[20];
    int RAM; double Price; count++;
    printf(">> Enter Motherboard: "); gets(Motherboard);
    printf(">> Enter Processor  : "); gets(Processor);
    printf(">> Enter VGA        : "); gets(VGA);
    printf(">> Enter RAM        : "); scanf("%d", &RAM); getchar();
    printf(">> Enter Price      : "); scanf("%lf", &Price); getchar();
    strcpy(PCArr[count].Motherboard, Motherboard);
    strcpy(PCArr[count].Processor, Processor);
    strcpy(PCArr[count].VGA, VGA);
    PCArr[count].RAM = RAM;
    PCArr[count].Price = Price;
    printf(">> PC Data Inserted!\n");
}
void modify()
{
    if (!count)
    {
        printf("No data to modify.\n");
        return;
    }
    view();
    int index = -1;
    while (index < 1 || index > count)
    {
        printf(">> Enter index to modify: "); scanf("%d", &index); getchar();
    }
    char Motherboard[20], Processor[20], VGA[20];
    int RAM; double Price;
    printf(">> Enter New Motherboard: "); gets(Motherboard);
    printf(">> Enter New Processor  : "); gets(Processor);
    printf(">> Enter New VGA        : "); gets(VGA);
    printf(">> Enter New RAM        : "); scanf("%d", &RAM); getchar();
    printf(">> Enter New Price      : "); scanf("%lf", &Price); getchar();
    strcpy(PCArr[index].Motherboard, Motherboard);
    strcpy(PCArr[index].Processor, Processor);
    strcpy(PCArr[index].VGA, VGA);
    PCArr[index].RAM = RAM;
    PCArr[index].Price = Price;
    printf(">> PC Data Modified!\n");
}
void delete()
{
    if (!count)
    {
        printf("No data to delete.\n");
        return;
    }
    view();
    int index = -1;
    while (index < 1 || index > count)
    {
        printf(">> Enter index to delete: "); scanf("%d", &index); getchar();
    }
    for (int i = index; i < count; i++) PCArr[i] = PCArr[i + 1];
    count--;
    printf(">> PC Data Deleted!\n");
}
void footer()
{
    printf("Press any key to exit... "); getchar();    
}
int main()
{
    while (choice != 5)
    {
        menu();
        switch (choice)
        {
            case 1: view(); footer(); break;
            case 2: insert(); footer(); break;
            case 3: modify(); footer(); break;
            case 4: delete(); footer(); break;
            case 5: exit(0); break;
            default: printf("Invalid choice!\n"); break;
        }
    }
    return 0;
}
