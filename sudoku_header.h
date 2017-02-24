#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#ifndef PRACTICAL3_SUDOKU_HEADER_H
#define PRACTICAL3_SUDOKU_HEADER_H

#endif //PRACTICAL3_SUDOKU_HEADER_H

typedef struct {
    int size;
    int *board;
    bool *fixed_values;
    bool *possible_values;
} Sudoku_board;

bool writ_value(Sudoku_board *sudoku_board);

int read_value(Sudoku_board *sudoku_board);

int get_coordinates(int size);

void print_sudoku_board(Sudoku_board *sudoku_board);

Sudoku_board copy_sudoku_board(Sudoku_board sudoku_board);

bool free_sudoku_board(Sudoku_board *sudoku_board);

void check_list(int *contents, int size);