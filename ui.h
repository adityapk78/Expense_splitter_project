#ifndef UI_H
#define UI_H

#include "list_manager.h"
void display_main_menu();
void display_expense_menu();
int get_user_choice();
void run_main_menu();
void get_string_input(char input[], int size);
int get_integer_input();
double get_decimal_input();
void display_expense_table(const ExpenseList *list);
void display_expense_details(const Expense *expense);
void clear_screen();
void run_main_menu(ExpenseList *list);
void run_expense_menu(ExpenseList *list);
void display_expense_summary(const ExpenseList *list);
#endif