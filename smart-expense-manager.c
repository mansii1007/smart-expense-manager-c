#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXP_FILE "expenses.dat"
#define USER_FILE "user.dat"

struct Expense {
    int id;
    char category[20];
    float amount;
    char note[50];
    char date[15];
    char time[10];
};

struct User {
    char username[20];
    char password[20];
};

int expenseCount = 0;
float monthlyBudget = 0;

/* ---------- UI ---------- */
void border() {
    printf("========================================\n");
}

/* ---------- DATE TIME ---------- */
void getDateTime(char *date, char *timeStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(date, "%02d-%02d-%04d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    sprintf(timeStr, "%02d:%02d:%02d",
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* ---------- LOGIN ---------- */
void registerUser() {
    system("cls");
    border();
    printf(" REGISTER USER\n");
    border();

    struct User u;
    FILE *fp = fopen(USER_FILE, "wb");

    printf("Create Username: ");
    scanf("%s", u.username);

    printf("Create Password: ");
    scanf("%s", u.password);

    fwrite(&u, sizeof(u), 1, fp);
    fclose(fp);

    printf("\n✔ Registration Successful\n");
    system("pause");
}

int login() {
    system("cls");
    border();
    printf(" USER LOGIN\n");
    border();

    struct User u, temp;
    FILE *fp = fopen(USER_FILE, "rb");

    if (!fp) {
        printf("No user found. Please register first.\n");
        system("pause");
        registerUser();
        return login();
    }

    printf("Username: ");
    scanf("%s", temp.username);

    printf("Password: ");
    scanf("%s", temp.password);

    fread(&u, sizeof(u), 1, fp);
    fclose(fp);

    if (strcmp(u.username, temp.username) == 0 &&
        strcmp(u.password, temp.password) == 0) {
        printf("\n✔ Login Successful\n");
        system("pause");
        return 1;
    } else {
        printf("\n❌ Invalid Credentials\n");
        system("pause");
        return 0;
    }
}

/* ---------- EXPENSE ---------- */
void addExpense() {
    system("cls");
    border();
    printf(" ADD EXPENSE\n");
    border();

    struct Expense e;
    FILE *fp = fopen(EXP_FILE, "ab");

    e.id = ++expenseCount;

    printf("Amount: ");
    scanf("%f", &e.amount);

    printf("Category: ");
    scanf("%s", e.category);

    printf("Note: ");
    scanf(" %[^\n]", e.note);

    getDateTime(e.date, e.time);

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("\n✔ Expense Added\n");
    system("pause");
}

void viewExpenses() {
    system("cls");
    border();
    printf(" EXPENSE HISTORY\n");
    border();

    struct Expense e;
    FILE *fp = fopen(EXP_FILE, "rb");
    float total = 0;

    if (!fp) {
        printf("No data found.\n");
        system("pause");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp)) {
        printf("[%d] %.2f | %s | %s %s\n%s\n\n",
               e.id, e.amount, e.category,
               e.date, e.time, e.note);
        total += e.amount;
    }

    fclose(fp);

    printf("Total Spent: %.2f\n", total);
    if (monthlyBudget > 0)
        printf("Budget Used: %.2f%%\n", (total / monthlyBudget) * 100);

    system("pause");
}

void setBudget() {
    system("cls");
    border();
    printf(" SET BUDGET\n");
    border();

    printf("Enter Monthly Budget: ");
    scanf("%f", &monthlyBudget);

    printf("\n✔ Budget Saved\n");
    system("pause");
}

void analytics() {
    system("cls");
    border();
    printf(" CATEGORY ANALYTICS\n");
    border();

    struct Expense e;
    FILE *fp = fopen(EXP_FILE, "rb");

    float total = 0;

    if (!fp) {
        printf("No data.\n");
        system("pause");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp))
        total += e.amount;

    fclose(fp);

    printf("Total Expenses: %.2f\n", total);
    system("pause");
}

/* ---------- MAIN ---------- */
int main() {
    int choice;

    if (!login())
        return 0;

    do {
        system("cls");
        border();
        printf(" SMART EXPENSE MANAGER\n");
        border();
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Set Budget\n");
        printf("4. Analytics\n");
        printf("0. Exit\n");
        border();
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: setBudget(); break;
            case 4: analytics(); break;
        }

    } while (choice != 0);

    system("cls");
    printf("Logged out successfully 👋\n");
    return 0;
}
