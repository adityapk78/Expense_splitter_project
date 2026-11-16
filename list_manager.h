#ifndef LIST_MANAGER_H
#define LIST_MANAGER_H

#include "expense.h"

/* Initialize an empty expense list */
void init_list(ExpenseList *list);

/* Add a new expense */
int add_expense(ExpenseList *list, const Expense *expense);

/* Search for an expense using its ID */
Node *find_expense(ExpenseList *list, int expense_id);

/* Delete an expense using its ID */
int delete_expense(ExpenseList *list, int expense_id);

/* Display all expenses */
void display_expenses(const ExpenseList *list);

/* Free all allocated memory */
void free_list(ExpenseList *list);

#endif