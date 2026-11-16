#ifndef EXPENSE_H
#define EXPENSE_H

typedef enum {
    EXPENSE_UNSETTLED,
    EXPENSE_SETTLED
} ExpenseStatus;

typedef struct Expense {
    int expense_id;
    char description[50];
    char paid_by[50];
    double total_amount;
    int participant_count;
    ExpenseStatus status;
} Expense;

typedef struct Node {
    Expense data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int total_expenses;
} ExpenseList;

#endif