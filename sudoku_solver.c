#include "sudoku_io.c"

int counter = 0;
Sudoku_board solved_board;

bool contains(int *arr, int val, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val && val != 0)
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
    int box_id = ((size * y) + x);
    int offset_y = (int) (pow(size, 3) * floor((box_id * size) / box_size));
    int offset_x = (box_id % size) * size;
    return offset_x + offset_y;
}

int *get_possible_values(Sudoku_board sudoku_board, int index) {
    int size = sudoku_board.size;
    int box_size = (int) pow(size, 2);
    int *possible_values = calloc((size_t) box_size, sizeof(int));
    int row_id = box_size * get_row_location(index, size);
    int col_id = get_col_location(index, size);
    int box_id = get_box_location(index, size);
    int *row = get_row(sudoku_board, row_id, box_size);
    int *col = get_col(sudoku_board, col_id, box_size);
    int *box = get_box(sudoku_board, box_id, box_size);
    int count = 0;
    for (int i = 1; i < box_size + 1; i++) {
        if (!contains(row, i, box_size) && !contains(col, i, box_size) && !contains(box, i, box_size)) {
            possible_values[count] = i;
            count++;
        }
    }
    free(row);
    free(box);
    free(col);
    return possible_values;
}

int get_nex_cell(Sudoku_board sudoku_board) {
    for (int i = 0; i < sudoku_board.length; i++) {
        if (sudoku_board.possible_values[i] == true)
            return i;
    }
}

//
//if (game board is full)
//return SUCCESS
//else
//next_square = getNextEmptySquare()
//for each value that can legally be put in next_square
//        put value in next_square (i.e. modify game state)
//if (solve(game)) return SUCCESS
//        remove value from next_square (i.e. backtrack to a previous state)
//return FAILURE
enum STATE sudoku_solve(Sudoku_board sudoku_board) {
    int state = check_sudoku(sudoku_board);
    if (state == 1) {
        solved_board = sudoku_board;
        counter++;
        return COMPLETE;
    } else if (state == -1)
        return UNSOLVABLE;
    else {
        int index = get_nex_cell(sudoku_board);
        int *values = get_possible_values(sudoku_board, index);
        for (int i = 0; i < pow(sudoku_board.size, 2); i++) {
            if (values[i] == 0)
                break;
            Sudoku_board copy = copy_sudoku_board(sudoku_board);
            copy.board[index] = values[i];
            copy.possible_values[index] = false;
            if (counter > 1)
                return MULTIPLE;
            else
                sudoku_solve(copy);
        }
        free(values);
    }
}


