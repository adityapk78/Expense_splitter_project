#include <stdio.h>
#include "ui.h"
#include "file_io.h"

int main()
{
    ExpenseList list;

    init_list(&list);

    load_expenses_from_file(&list, "expenses.dat");
    printf("Expenses loaded: %d\n", list.total_expenses);
    run_main_menu(&list);

    free_list(&list);

    return 0;
}