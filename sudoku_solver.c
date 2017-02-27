#include "sudoku_io.c"
#include "sudoku_header.h"

bool contains(int *arr, int val, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == val)
            return true;
    }
    return false;
}

int get_row_location(int index, int size) {
    int box_size = (int) pow(size, 2);
    return (index / box_size);
}

int get_col_location(int index, int size) {
    int box_size = (int) pow(size, 2);
    return (index % box_size);
}

int get_box_location(int index, int size) {
    int box_size = (int) pow(size, 2);
    int x = ((index % box_size) / size);
    int y = (index / box_size) / size;
    return ((size * y) + x);
}

int *get_possible_values(Sudoku_board *sudoku_board, int index) {
    int size = sudoku_board->size;
    int box_size = (int) pow(size, 2);
    int *possible_values = malloc((size_t) size);
    int row_id = (int) pow(get_row_location(index, size), 2);
    int col_id = get_row_location(index, size);
    int box_id = get_row_location(index, size);
    int *row = get_row(sudoku_board, row_id, box_size);
    int *col = get_col(sudoku_board, col_id, box_size);
    int *box = get_box(sudoku_board, box_id * size, box_size);
    int count = 0;
    for (int i = 0; i < sudoku_board->length; i++) {
        if (!contains(row, i, box_size) && !contains(col, i, box_size) && !contains(box, i, box_size)) {
            possible_values[count] = i;
            count++;
        }

    }
    return possible_values;
}

int get_nex_cell(Sudoku_board *sudoku_board) {
    for (int i = 0; i < sudoku_board->length; ++i) {
        if (sudoku_board->possible_values[i] == true)
            return i;
    }
    return -1;
}

//if (game board is full)
//return SUCCESS
//else
//next_square = getNextEmptySquare()
//for each value that can legally be put in next_square
//        put value in next_square (i.e. modify game state)
//if (solve(game)) return SUCCESS
//        remove value from next_square (i.e. backtrack to a previous state)
//return FAILURE
enum STATE sudoku_check(Sudoku_board *sudoku_board) {
    if (check_sudoku(sudoku_board) == COMPLETE)
        return COMPLETE;
    else {
        int index = get_nex_cell(sudoku_board);

    }
}


int main() {
    for (int i = 0; i < 16; ++i) {
        printf("%d ", get_row_location(i, 2) * 4);
    }


}
