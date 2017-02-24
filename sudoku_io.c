//TODO update with x axis as letters and y axis as numbers and change to account for boxes
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
    for (int i = 0; i < pow(size, 4); i += pow(size, 2)) {
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
    int size = sudoku_board->size;
    for (int i =0; i < pow(size, 4); i++){
        sudoku_board->board[i] = 0;
    }
    return true;
}

int main(){
    Sudoku_board sudoku_board;
    sudoku_board.size = 2;
    sudoku_board.board = (int *) malloc(sizeof(int) * 16);
    int temp[16] = {0, 2, 3, 4, 3, 4, 1, 2, 4, 0, 2, 1, 2, 0, 4, 0};
    for (int i = 0; i < 16; i++) {
        sudoku_board.board[i] = temp[i];
    }
    print_sudoku_board(&sudoku_board);
    write_value(&sudoku_board);
    print_sudoku_board(&sudoku_board);

    return 0;
};
