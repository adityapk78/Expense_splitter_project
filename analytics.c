#include <stdio.h>
#include <string.h>
#include "expense.h"
#include "analytics.h"


// SEARCH BY PAYER NAME

void search_by_payer(const ExpenseList *list, const char *payer){
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

void search_by_amount_range(const ExpenseList *list, double min_amount, double max_amount){
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




//ANALYTICS REPORT


void generate_analytics_report(const ExpenseList *list){
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
        printf("3. Generate Analytics Report\n");
        printf("4. Return To Main Menu\n");

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
                generate_analytics_report(list);
                break;

            case 4:
                break;

            default:
                printf("Invalid choice.\n");
        }

    }
    while(choice != 4);
}