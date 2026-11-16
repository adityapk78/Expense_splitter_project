#ifndef FILE_IO_H // it will ignore the repeated calls 
#define FILE_IO_H

#include "expense.h"

void load_expenses_from_file(ExpenseList *list, const char *filename);
void save_expenses_to_file(ExpenseList *list, const char *filename);

#endif