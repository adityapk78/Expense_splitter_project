#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "expense.h"

void run_analytics_menu(ExpenseList *list);
void search_by_payer(const ExpenseList *list, const char *payer);
void search_by_amount_range(const ExpenseList *list, double min_amount, double max_amount);
void generate_audit_report(const ExpenseList *list, const char *filename);
void generate_analytics_report(const ExpenseList *list);
void sort_by_amount(ExpenseList *list);
void sort_by_id(ExpenseList *list);

#endif