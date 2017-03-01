

#sudoku_check: main_io.c
#	gcc -o sudoku_check main_io.c

sudoku_solver: main_solve.c
	gcc -o sudoku_solver main_solve.c

clean:
	rm *.o sudoku_solver

