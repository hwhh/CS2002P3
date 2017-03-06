#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int *board;
    bool *possible_values;
    double length;
    int size;
} Sudoku_board;


enum STATE {
    INVALID = -1,//": The array contains some value twice.",
    INCOMPLETE = 0,//": The array is not INVALID, but is not complete.",
    COMPLETE = 1,//": The array is not INVALID, and every value is assigned. \n"This means the array contains the values between 1 and 9, in some permutation."
    MULTIPLE = 2,
    UNSOLVABLE = 3
};

