#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

void save_expenses_to_file(ExpenseList *list, const char *filename){
    if (list == NULL){
        printf("Expense list is NULL. Cannot save to file.\n");
        return;
    }
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }
    Node *current = list->head;
    while(current != NULL){
    fwrite(&current->data, sizeof(Expense), 1, fp);
    current = current->next;
    }
    fclose(fp);

}

void load_expenses_from_file(ExpenseList *list, const char *filename){
    if (list==NULL){
        printf("Expense list is NULL.\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");

    if(fp==NULL){
        printf("Can't read file \n");
        return;
    }
    Expense temp_expense;

    while (fread(&temp_expense, sizeof(Expense), 1, fp) == 1){
        Node *new_node = malloc(sizeof(Node));
        if (new_node==NULL){
            printf("Memory allocation failed\n");
            fclose(fp);
            return;
        }
        new_node->data = temp_expense;
        new_node->next = list->head;
        list->head = new_node;
        list->total_expenses++;
    
    }
    fclose(fp);
   

}