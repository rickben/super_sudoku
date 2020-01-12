CC = gcc
OBJS = main.o MainAux.o Game.o Parser.o Solver.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: main.c MainAux.h Parser.h Solver.h Game.h
	$(CC) $(COMP_FLAG) -c $*.c
MainAux.o: MainAux.c MainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h
	$(CC) $(COMP_FLAG) -c $*.c
Solver.o: Solver.c Solver.h
	$(CC) $(COMP_FLAG) -c $*.c
Game.o: Game.c Game.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
