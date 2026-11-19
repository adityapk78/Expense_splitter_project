expense_app: main.o file_io.o list_manager.o settlement.o ui.o analytics.o
	gcc -o expense_app main.o file_io.o list_manager.o settlement.o ui.o analytics.o

main.o: main.c ui.h file_io.h
	gcc -c main.c

file_io.o: file_io.c file_io.h expense.h
	gcc -c file_io.c

list_manager.o: list_manager.c list_manager.h expense.h
	gcc -c list_manager.c

settlement.o: settlement.c settlement.h expense.h list_manager.h
	gcc -c settlement.c

ui.o: ui.c ui.h file_io.h settlement.h list_manager.h expense.h analytics.h
	gcc -c ui.c

analytics.o: analytics.c analytics.h expense.h
	gcc -c analytics.c

clean:
	del /Q *.o expense_app.exe 2>NUL