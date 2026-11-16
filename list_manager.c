#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "list_manager.h"

/* Validate expense information */
static int is_valid_expense(const Expense *expense)
{
    if (expense == NULL) {
        return 0;
    }

    if (expense->expense_id <= 0 ||
        !isfinite(expense->total_amount) ||
        expense->total_amount <= 0 ||
        expense->participant_count <= 0) {
        return 0;
    }

    if (memchr(expense->description, '\0',
               sizeof(expense->description)) == NULL ||
        memchr(expense->paid_by, '\0',
               sizeof(expense->paid_by)) == NULL) {
        return 0;
    }

    if (expense->description[0] == '\0' ||
        expense->paid_by[0] == '\0') {
        return 0;
    }

    if (expense->status != EXPENSE_UNSETTLED &&
        expense->status != EXPENSE_SETTLED) {
        return 0;
    }

    return 1;
}

/* Initialize the linked list */
void init_list(ExpenseList *list)
{
    if (list == NULL) {
        return;
    }

    list->head = NULL;
    list->total_expenses = 0;
}

/* Add a new expense */
int add_expense(ExpenseList *list, const Expense *expense)
{
    if (list == NULL || !is_valid_expense(expense)) {
        return 0;
    }

    if (list->total_expenses < 0 ||
        list->total_expenses == INT_MAX) {
        return 0;
    }

    if (find_expense(list, expense->expense_id) != NULL) {
        return 0;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        return 0;
    }

    new_node->data = *expense;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_node;
    }

    list->total_expenses++;

    return 1;
}

/* Find an expense using its ID */
Node *find_expense(ExpenseList *list, int expense_id)
{
    if (list == NULL || expense_id <= 0) {
        return NULL;
    }

    Node *current = list->head;

    while (current != NULL) {
        if (current->data.expense_id == expense_id) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

/* Display all expenses */
void display_expenses(const ExpenseList *list)
{
    if (list == NULL || list->head == NULL) {
        printf("No expenses available.\n");
        return;
    }

    const Node *current = list->head;

    printf("\n========== EXPENSE LIST ==========\n");

    while (current != NULL) {
        printf("Expense ID: %d\n", current->data.expense_id);
        printf("Description: %s\n", current->data.description);
        printf("Paid By: %s\n", current->data.paid_by);

        printf("Amount: Rs. %.2f\n",
               current->data.total_amount);

        printf("Participants: %d\n",
               current->data.participant_count);

        printf("Status: %s\n",
               current->data.status == EXPENSE_SETTLED
               ? "Settled" : "Unsettled");

        printf("----------------------------------\n");

        current = current->next;
    }
}

/* Delete an expense using its ID */
int delete_expense(ExpenseList *list, int expense_id)
{
    if (list == NULL || expense_id <= 0) {
        return 0;
    }

    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL) {

        if (current->data.expense_id == expense_id) {

            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);

            list->total_expenses--;

            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

/* Free all allocated nodes */
void free_list(ExpenseList *list)
{
    if (list == NULL) {
        return;
    }

    Node *current = list->head;

    while (current != NULL) {
        Node *temp = current;

        current = current->next;

        free(temp);
    }

    list->head = NULL;
    list->total_expenses = 0;
}