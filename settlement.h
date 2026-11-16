#ifndef SETTLEMENTS_H
#define SETTLEMENTS_H

#include "expense.h"
#include "list_manager.h"
// calculate the individual share of an expense
double calculate_share(Expense *expense);
// settle an expense using its ID
int settle_expense(ExpenseList *list, int expense_id);

#endif