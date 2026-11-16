#include <stdio.h>
#include "settlement.h"

/* Calculate individual expense share */
double calculate_share(Expense *expense)
{
if (expense == NULL)
{
return 0.0;
}

if (expense->total_amount <= 0 ||
    expense->participant_count <= 0)
{
    return 0.0;
}

return expense->total_amount / expense->participant_count;

}

/* Settle an expense using its ID */
int settle_expense(ExpenseList *list, int expense_id)
{
if (list == NULL || expense_id <= 0)
{
return 0;
}

/* Find the expense using its ID */
Node *found = find_expense(list, expense_id);

if (found == NULL)
{
    printf("Expense not found.\n");
    return 0;
}

/* Check whether already settled */
if (found->data.status == EXPENSE_SETTLED)
{
    printf("This expense is already settled.\n");
    return 0;
}

/* Update expense status */
found->data.status = EXPENSE_SETTLED;

printf("Expense settled successfully!\n");

return 1;

}
