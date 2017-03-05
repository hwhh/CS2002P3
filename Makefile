#sudoku_check: main_io.c
#	gcc -o sudoku_check main_io.c

sudoku_solver: main_solve.c
	gcc -o sudoku_solver main_solve.c

sudoku_advanced: dancing_links_main.c
	gcc -o sudoku_advanced dancing_links_main.c

#sudoku_advanced: main_solve.c
#	gcc -o sudoku_advanced main_solve.c

clean:
	rm *.o sudoku_check sudoku_solver sudoku_advanced




