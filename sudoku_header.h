#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define BUFFER_SIZE 10000

#ifndef PRACTICAL3_SUDOKU_HEADER_H
#define PRACTICAL3_SUDOKU_HEADER_H

#endif //PRACTICAL3_SUDOKU_HEADER_H

typedef struct {
    int size;
    double length;
    int *board;
    bool *fixed_values;
    bool *possible_values;
} Sudoku_board;


enum STATE {
    INVALID = -1,//": The array contains some value twice.",
    INCOMPLETE = 0,//": The array is not INVALID, but is not complete.",
    COMPLETE = 1//": The array is not INVALID, and every value is assigned. \n"This means the array contains the values between 1 and 9, in some permutation."
};

bool writ_value(Sudoku_board *sudoku_board);

int read_value(Sudoku_board *sudoku_board);

int get_coordinates(int size);

void print_sudoku_board(Sudoku_board *sudoku_board);

Sudoku_board copy_sudoku_board(Sudoku_board sudoku_board);

bool free_sudoku_board(Sudoku_board *sudoku_board);

enum STATE check_list(int *contents, int size);

bool check_sudoku(Sudoku_board *sudoku_board);