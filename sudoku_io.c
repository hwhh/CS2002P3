//TODO update with x axis as letters and y axis as numbers and change to account for boxes
#include <memory.h>
#include "sudoku_header.h"

int get_coordinates(int size) {
    int locations[2];
    printf("please input location: ");
    scanf("%d,%d", &locations[0], &locations[1]);
    return locations[1] + (locations[0] * (size * size));
}

bool write_value(Sudoku_board *sudoku_board) {
    int size = sudoku_board->size, value;
    int location = get_coordinates(size);
    if (location < 0 || location > sudoku_board->length)
        return false;
    printf("Please input new value: ");
    scanf("%d", &value);
    if (value < pow(size, 2) && value > 0) {
        sudoku_board->board[location] = value;
        return true;
    }
    return false;
}

int read_value(Sudoku_board *sudoku_board) {
    int location = get_coordinates(sudoku_board->size);
    return (sudoku_board->board[location]);
}

void print_sudoku_board(Sudoku_board *sudoku_board) {
    int size = sudoku_board->size;
    printf("%d\n", size);
    for (int i = 0; i < sudoku_board->length; i += pow(size, 2)) {
        for (int j =0; j<size*size; j++){
            printf("%d ", sudoku_board->board[i + j]);
        }
        printf("\n");
    }
}

Sudoku_board copy_sudoku_board(Sudoku_board sudoku_board) {
    return sudoku_board;
}

bool free_sudoku_board(Sudoku_board *sudoku_board) {

    for (int i = 0; i < sudoku_board->length; i++) {
        sudoku_board->board[i] = 0;
    }
    return true;
}


enum STATE check_list(int *contents, int size) {
    bool duplicate = false;
    bool zero = false;
    for (int i = 0; i < size; ++i) {
        if (contents[i] == 0)
            zero = true;
        for (int j = i + 1; j < size; ++j)
            if (contents[i] == contents[j]) {
                duplicate = true;
                break;
            }
    }
    if (duplicate)
        return INVALID;
    else if (zero)
        return INCOMPLETE;
    else
        return COMPLETE;
}


bool print_status(int state, bool final) {
    if (state == -1) {
        printf("INVALID: If any row, column, box contains a number twice.");
        return false;
    }
    if (state == 0)
        printf("INCOMPLETE: The sudoku is not INVALID, but is not complete.");
    if (state == 1 && final)
        printf("COMPLETE: The sudoku is not INVALID, and every value is assigned.");

    return true;
}

void check_sudoku(Sudoku_board *sudoku_board) {
    //check box;
    double size = pow(sudoku_board->size, 2);
    for (int i = 0; i < sudoku_board->length; i += pow(size, 2)) {
        int row[(int) size];
        for (int j = 0; j < size; j++) {
            row[j] = sudoku_board->board[i + j];
        }
        if (!check_list(row, (int) size) == -1)
            break;
    }
    printf("\n");
    int offset = 0;
    for (int i = 1; i < size + 1; i++) {
        int box[(int) size];
        for (int j = 1; j < size + 1; j++) {
            if (j == sudoku_board->size) {
                box[j - 1] = sudoku_board->board[offset];
                offset += size - 1;
            } else {
                box[j - 1] = sudoku_board->board[offset++];
                //offset++;
            }
            if (i != sudoku_board->size)
                offset = (int) (offset - size);

            if (!check_list(box, (int) size) == -1)
                break;
        }


    }





