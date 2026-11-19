#include <stdio.h>
#include <string.h>
#include "expense.h"
#include "analytics.h"


// SEARCH BY PAYER NAME

void search_by_payer(const ExpenseList *list,
                     const char *payer)
{
    if(list == NULL || payer == NULL)
    {
        return;
    }

    const Node *current = list->head;
    int found = 0;

    printf("\nSEARCH RESULTS\n");
    printf("--------------------------\n");

    while(current != NULL)
    {
        if(strstr(current->data.paid_by, payer) != NULL)
        {
            printf("ID: %d\n",
                   current->data.expense_id);

            printf("Description: %s\n",
                   current->data.description);

            printf("Paid By: %s\n",
                   current->data.paid_by);

            printf("Amount: %.2f\n",
                   current->data.total_amount);

            printf("--------------------------\n");

            found = 1;
        }

        current = current->next;
    }

    if(!found)
    {
        printf("No matching expenses found.\n");
    }
}

//SEARCH BY AMOUNT RANGE

void search_by_amount_range(
        const ExpenseList *list,
        double min_amount,
        double max_amount)
{
    if(list == NULL)
    {
        return;
    }

    const Node *current = list->head;
    int found = 0;

    printf("\nEXPENSES BETWEEN %.2f AND %.2f\n",
           min_amount,
           max_amount);

    while(current != NULL)
    {
        double amount = current->data.total_amount;

        if(amount >= min_amount &&
           amount <= max_amount)
        {
            printf("ID: %d | %s | %.2f\n",
                   current->data.expense_id,
                   current->data.description,
                   amount);

            found = 1;
        }

        current = current->next;
    }

    if(!found)
    {
        printf("No expenses found.\n");
    }
}


// SORT BY AMOUNT

void sort_by_amount(ExpenseList *list)
{
    if(list == NULL ||
       list->head == NULL)
    {
        return;
    }

    int swapped;
    Expense temp;
    Node *current;

    do
    {
        swapped = 0;

        current = list->head;

        while(current->next != NULL)
        {
            if(current->data.total_amount >
               current->next->data.total_amount)
            {
                temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = 1;
            }

            current = current->next;
        }
    }
    while(swapped);

    printf("Expenses sorted by amount.\n");
}


//SORT BY EXPENSE ID


void sort_by_id(ExpenseList *list)
{
    if(list == NULL ||
       list->head == NULL)
    {
        return;
    }

    int swapped;
    Expense temp;
    Node *current;

    do
    {
        swapped = 0;

        current = list->head;

        while(current->next != NULL)
        {
            if(current->data.expense_id >
               current->next->data.expense_id)
            {
                temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = 1;
            }

            current = current->next;
        }
    }
    while(swapped);

    printf("Expenses sorted by ID.\n");
}


//AUDIT REPORT


void generate_audit_report(
        const ExpenseList *list,
        const char *filename)
{
    if(list == NULL ||
       filename == NULL)
    {
        return;
    }

    FILE *fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Unable to create report.\n");
        return;
    }

    const Node *current = list->head;

    fprintf(fp,
            "=========== AUDIT REPORT ===========\n\n");

    while(current != NULL)
    {
        fprintf(fp,
                "Expense ID: %d\n",
                current->data.expense_id);

        fprintf(fp,
                "Description: %s\n",
                current->data.description);

        fprintf(fp,
                "Paid By: %s\n",
                current->data.paid_by);

        fprintf(fp,
                "Amount: %.2f\n",
                current->data.total_amount);

        fprintf(fp,
                "Participants: %d\n",
                current->data.participant_count);

        fprintf(fp,
                "Status: %s\n\n",
                current->data.status ==
                EXPENSE_SETTLED
                ? "Settled"
                : "Unsettled");

        current = current->next;
    }

    fclose(fp);

    printf("Audit report generated.\n");
}

//ANALYTICS REPORT


void generate_analytics_report(
        const ExpenseList *list)
{
    if(list == NULL)
    {
        return;
    }

    const Node *current = list->head;

    int total_expenses = 0;
    int settled = 0;
    int unsettled = 0;

    double total_amount = 0;
    double highest = 0;

    while(current != NULL)
    {
        total_expenses++;

        total_amount +=
            current->data.total_amount;

        if(current->data.total_amount >
           highest)
        {
            highest =
                current->data.total_amount;
        }

        if(current->data.status ==
           EXPENSE_SETTLED)
        {
            settled++;
        }
        else
        {
            unsettled++;
        }

        current = current->next;
    }

    printf("\n========== ANALYTICS ==========\n");

    printf("Total Expenses: %d\n",
           total_expenses);

    printf("Total Amount: %.2f\n",
           total_amount);

    printf("Largest Expense: %.2f\n",
           highest);

    printf("Settled: %d\n",
           settled);

    printf("Unsettled: %d\n",
           unsettled);

    if(total_expenses > 0)
    {
        printf("Average Expense: %.2f\n",
               total_amount /
               total_expenses);
    }

    printf("================================\n");
}

//Analytics Menu

void run_analytics_menu(ExpenseList *list)
{
    int choice = 0;

    do
    {
        printf("\n===== SEARCH & REPORTS =====\n");

        printf("1. Search By Payer\n");
        printf("2. Search By Amount Range\n");
        printf("3. Sort By Amount\n");
        printf("4. Sort By ID\n");
        printf("5. Generate Audit Report\n");
        printf("6. Generate Analytics Report\n");
        printf("7. Return To Main Menu\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        getchar();

        switch(choice)
        {
            case 1:
            {
                char payer[50];

                printf("Enter payer name: ");
                fgets(payer, sizeof(payer), stdin);

                payer[strcspn(payer, "\n")] = '\0';

                search_by_payer(list, payer);
                break;
            }

            case 2:
            {
                double min;
                double max;

                printf("Enter minimum amount: ");
                scanf("%lf", &min);

                printf("Enter maximum amount: ");
                scanf("%lf", &max);

                getchar();

                search_by_amount_range(
                    list,
                    min,
                    max
                );

                break;
            }

            case 3:
                sort_by_amount(list);
                break;

            case 4:
                sort_by_id(list);
                break;

            case 5:
                generate_audit_report(
                    list,
                    "audit_report.txt"
                );
                break;

            case 6:
                generate_analytics_report(list);
                break;

            case 7:
                break;

            default:
                printf("Invalid choice.\n");
        }

    }
    while(choice != 7);
}