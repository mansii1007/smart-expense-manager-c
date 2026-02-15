#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NAME "expenses.dat"

struct Expense {
    int id;
    char category[20];
    float amount;
    char note[50];
    char date[15];
    char time[10];
};

int expenseCount = 0;
float monthlyBudget = 0;

// Date & Time Utility
void getDateTime(char *date, char *timeStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(date, "%02d-%02d-%04d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    sprintf(timeStr, "%02d:%02d:%02d",
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// Add Expense
void addExpense() {
    system("cls");

    struct Expense e;
    FILE *fp = fopen(FILE_NAME, "ab");

    e.id = ++expenseCount;

    printf("=== ADD NEW EXPENSE ===\n\n");

    printf("Amount: ");
    scanf("%f", &e.amount);

    printf("Category (food/travel/rent/medical/other): ");
    scanf("%s", e.category);

    printf("Note: ");
    scanf(" %[^\n]", e.note);

    getDateTime(e.date, e.time);

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("\n✔ Expense Added Successfully\n");
    system("pause");
}

// View Expenses
void viewExpenses() {
    system("cls");

    struct Expense e;
    FILE *fp = fopen(FILE_NAME, "rb");

    float total = 0;

    printf("=== EXPENSE HISTORY ===\n\n");

    if (!fp) {
        printf("No expenses found.\n");
        system("pause");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp)) {
        printf("[%d] %.2f | %s | %s %s\n    %s\n\n",
               e.id, e.amount, e.category,
               e.date, e.time, e.note);

        total += e.amount;
    }

    fclose(fp);

    printf("Total Spent: %.2f\n", total);

    if (monthlyBudget > 0) {
        printf("Budget Used: %.2f%%\n",
               (total / monthlyBudget) * 100);
    }

    system("pause");
}

// Set Budget
void setBudget() {
    system("cls");

    printf("=== SET MONTHLY BUDGET ===\n\n");
    printf("Enter Budget Amount: ");
    scanf("%f", &monthlyBudget);

    printf("\n✔ Budget Updated Successfully\n");
    system("pause");
}

// Category Analytics
void categoryAnalytics() {
    system("cls");

    struct Expense e;
    FILE *fp = fopen(FILE_NAME, "rb");

    float food = 0, travel = 0, rent = 0, medical = 0, other = 0;

    if (!fp) {
        printf("No data available.\n");
        system("pause");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp)) {
        if (strcmp(e.category, "food") == 0)
            food += e.amount;
        else if (strcmp(e.category, "travel") == 0)
            travel += e.amount;
        else if (strcmp(e.category, "rent") == 0)
            rent += e.amount;
        else if (strcmp(e.category, "medical") == 0)
            medical += e.amount;
        else
            other += e.amount;
    }

    fclose(fp);

    printf("=== CATEGORY ANALYTICS ===\n\n");
    printf("Food    : %.2f\n", food);
    printf("Travel  : %.2f\n", travel);
    printf("Rent    : %.2f\n", rent);
    printf("Medical : %.2f\n", medical);
    printf("Other   : %.2f\n", other);

    system("pause");
}

// Main Menu
int main() {
    int choice;

    do {
        system("cls");

        printf("==== SMART EXPENSE MANAGER ====\n\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Set Monthly Budget\n");
        printf("4. Category Analytics\n");
        printf("0. Exit\n\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: setBudget(); break;
            case 4: categoryAnalytics(); break;
        }

    } while (choice != 0);

    system("cls");
    printf("Thank you for using Expense Manager 💸\n");

    return 0;
}
