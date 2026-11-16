#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "file_io.h"
#include "settlement.h"

void display_main_menu(){
    printf("Expense Splitter\n");
    printf("1.List all expenses\n");
    printf("2.Add a New Expense\n");
    printf("3.Select Expense\n");
    printf("4.Generate Summary\n");
    printf("5.Save and Exit\n");

    printf("Enter your choice: ");
}

void display_expense_menu(){
    printf("Expense Operations\n");
    printf("1. View Expense Details\n");
    printf("2. Mark Expense as Settled\n");
    printf("3. Edit Expense Details\n");
    printf("4. Delete Expense\n");
    printf("5. Return to Main Menu\n");
}
int get_user_choice(){
    char input[100];
    int choice;
    while (1){
        fgets(input, sizeof(input), stdin);
        int result = sscanf(input, "%d", &choice);
        if (result == 1){
            if (choice >= 1 && choice <= 5){
                return choice;
            }
        }
        printf("Invalid choice. Enter between 1 and 5: ");
    }
}
void run_main_menu(ExpenseList *list){
    int choice ;
    while (choice != 5){
        display_main_menu();
        choice = get_user_choice();

        if (choice ==1){
             display_expense_table(list);
        }
       else if (choice == 2){
        Expense new_expense;

        printf("\nADD NEW EXPENSE\n");

        printf("Enter Expense ID: ");
        new_expense.expense_id = get_integer_input();

        printf("Enter Description: ");
        get_string_input(new_expense.description, 50);

        printf("Enter Paid By: ");
        get_string_input(new_expense.paid_by, 50);

        printf("Enter Total Amount: ");
        new_expense.total_amount = get_decimal_input();

        printf("Enter Number of Participants: ");
        new_expense.participant_count = get_integer_input();

        new_expense.status = EXPENSE_UNSETTLED;

        if (add_expense(list, &new_expense))
        {
            printf("\nExpense added successfully!\n");
        }
        else
        {
            printf("\nFailed to add expense. Check the details or ID.\n");
        }
        }
        else if(choice == 3){
            run_expense_menu(list);
          
}
        else if(choice == 4){
            display_expense_summary(list);
        }
        else if(choice == 5){
            save_expenses_to_file(list, "expenses.dat");
            printf("\nThank you, Exiting\n");
            break;
        }
        printf("\nPress Enter to return to the main menu...");
        getchar();
        clear_screen();
}
}

void get_string_input(char input[], int size){
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0';
}
int get_integer_input(){
    char input[100];
    int number;
    while (1){
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &number) == 1){
            return number;
        }
        printf("Invalid input. Enter a number: ");
    }
}
double get_decimal_input()
{
    char input[100];
    double number;

    while (1)
    {
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%lf", &number) == 1)
        {
            return number;
        }

        printf("Invalid input! Enter a valid amount: ");
    }
}
void display_expense_table(const ExpenseList *list){
    if (list == NULL)
    {
        printf("List is NULL\n");
        return;
    }

    const Node *current = list->head;

    if (current == NULL)
    {
        printf("No expenses available.\n");
        return;
    }

    printf("\nALL EXPENSES\n");
    printf("ID\tDESCRIPTION\tPAID BY\t\tAMOUNT\n");

    while (current != NULL)
    {
        printf("%d\t%s\t\t%s\t\t%.2f\n",
               current->data.expense_id,
               current->data.description,
               current->data.paid_by,
               current->data.total_amount);

        current = current->next;
    }
}
void display_expense_details(const Expense *expense){
    if (expense == NULL){
        printf("No expense found.\n");
        return;
    }
    printf("\nEXPENSE DETAILS\n");
    printf("Expense ID: %d\n", expense->expense_id);
    printf("Description: %s\n", expense->description);
    printf("Paid By: %s\n", expense->paid_by);
    printf("Total Amount: %.2f\n", expense->total_amount);
    printf("Participants: %d\n", expense->participant_count);
    if (expense->status == EXPENSE_UNSETTLED){
        printf("Status: Unsettled\n");
    }
    else if (expense->status == EXPENSE_SETTLED){
        printf("Status: Settled\n");
    }
}
void clear_screen()
{
    system("cls");
}
void display_expense_summary(const ExpenseList *list){
    const Node *current;
    int total = 0;
    int settled = 0;
    int unsettled = 0;
    double total_amount = 0;

    current = list->head;

    while (current != NULL)
    {
        total++;
        total_amount += current->data.total_amount;

        if (current->data.status == EXPENSE_SETTLED)
        {
            settled++;
        }
        else
        {
            unsettled++;
        }

        current = current->next;
    }

    printf("\nEXPENSE SUMMARY\n");
    printf("--------------------------\n");
    printf("Total Expenses: %d\n", total);
    printf("Total Amount Spent: %.2f\n", total_amount);
    printf("Settled Expenses: %d\n", settled);
    printf("Unsettled Expenses: %d\n", unsettled);
}
void run_expense_menu(ExpenseList *list){
    int choice;
    int expense_id;
    Node *found;
    while(1){
        display_expense_menu();
        printf("Enter Your choice: ");
        choice = get_user_choice();
        if (choice ==1){
             printf("Enter Expense ID: ");
            expense_id = get_integer_input();

            found = find_expense(list, expense_id);
             if (found != NULL){
                display_expense_details(&found->data);
            }
            else{
                printf("Expense not found!\n");
            }
        }
      else if (choice == 2){
        printf("Enter Expense ID: ");
        expense_id = get_integer_input();
        settle_expense(list, expense_id);
}
        else if( choice == 3){
            printf("Enter Expense ID to edit: ");
            expense_id = get_integer_input();
            found = find_expense(list, expense_id);
            if (found != NULL){
                printf("\nCurrent Expense Details:\n");
                display_expense_details(&found->data);

                printf("\nEnter New Description: ");
                get_string_input(found->data.description, 50);

                printf("Enter New Paid By: ");
                get_string_input(found->data.paid_by, 50);

                printf("Enter New Total Amount: ");
                found->data.total_amount = get_decimal_input();
                if(found->data.total_amount <= 0){
                    printf("Invalid amount! Amount must be greater than zero.\n");
                    printf("Expense not updated.\n");
                }
                else{
                    printf("Enter New Number of Participants: ");
                    found->data.participant_count = get_integer_input();
                    if(found->data.participant_count<=0){
                        printf("Invalid participant count! It must be greater than zero.\n");
                        printf("Expense not updated.\n");
                    }
                    else{
                        printf("\nExpense updated Successfully.\n");
                    }
                }
            }
            else{
                printf("Expense not found.\n");
            }
        }
        else if (choice == 4){
            printf("Enter Expense ID to delete: ");
            expense_id = get_integer_input();
            if(delete_expense(list, expense_id)){
                printf("Expense deleted Successfully.\n");
            }
            else{
                printf("Expense not found.\n");
            }
        }
        else if (choice == 5){
            break;
        }
        printf("\nPress Enter to continue.");
        getchar();
        clear_screen();
    }
}