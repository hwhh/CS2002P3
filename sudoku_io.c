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
    for (int i = 0; i < sudoku_board->length; i += pow(size, 2)) {
        for (int j =0; j<size*size; j++){
            int x = sudoku_board->board[i + j];
            if (x < 10)
                printf("  %d", x);
            else
                printf(" %d", x);
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

void delete_board(Sudoku_board *sudoku_board) {
    free(sudoku_board->board);
    free(sudoku_board->fixed_values);
    free(sudoku_board->possible_values);
}


enum STATE check_list(int *contents, int size) {
    bool duplicate = false;
    bool zero = false;
    for (int i = 0; i < size; ++i) {
        if (contents[i] == 0)
            zero = true;
        for (int j = i + 1; j < size; ++j)
            if (contents[i] == contents[j] && (contents[i] != 0 || contents[j] != 0)) {
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

bool check_sudoku(Sudoku_board *sudoku_board) {
    int status = 1;
    int offset = 0;
    int root = (int) pow(sudoku_board->size, 3);
    double size = pow(sudoku_board->size, 2);
    for (int i = 0; i < sudoku_board->length; i += size) {
        int row[(int) size];
        for (int j = 0; j < size; j++) {
            row[j] = sudoku_board->board[i + j];
        }
        if (check_list(row, (int) size) == -1) {
            printf("INVALID");
            return false;
        } else if (check_list(row, (int) size) == 0)
            status = 0;
    }
    for (int i = 0; i < size; i++) {
        int count = 0;
        int col[(int) size];
        for (int j = 0; j < sudoku_board->length; j += size) {
            col[count] = sudoku_board->board[i + j];
            count++;
        }
        if (check_list(col, (int) size) == -1) {
            printf("INVALID");
            return false;
        } else if (check_list(col, (int) size) == 0)
            status = 0;
    }
    for (int i = 0; i < sudoku_board->length; i += size) {
        int box[(int) size];
        for (int j = 0; j < size; j++) {
            if (j % sudoku_board->size == 0 && j > 0) {
                offset += (size - sudoku_board->size + 1);
                box[j] = sudoku_board->board[offset - 1];
            } else
                box[j] = sudoku_board->board[offset++];
        }
        if (offset % root != 0)
            offset -= (size * (sudoku_board->size - 1));
        if (check_list(box, (int) size) == -1) {
            printf("INVALID");
            return false;
        } else if (check_list(box, (int) size) == 0)
            status = 0;
    }
    if (status == 1)
        printf("COMPLETE");
    else if (status == 0)
        printf("INCOMPLETE");
    return true;
}

Sudoku_board createBoard() {
    Sudoku_board sudoku_board;
    char line[1024], *p, *e;
    long v;
    int count = 0;
    while (fgets(line, sizeof(line), stdin)) {
        for (p = line;; p = e) {
            v = strtol(p, &e, 10);
            if (p == e)
                break;
            if (count == 0) {
                sudoku_board.size = (int) v;
                sudoku_board.length = pow(v, 4);
                sudoku_board.board = (int *) malloc((size_t) (sizeof(int) * sudoku_board.length));
                sudoku_board.fixed_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
                sudoku_board.possible_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
                count++;
            } else {
                if (v == 0) {
                    sudoku_board.board[count - 1] = (int) v;
                    sudoku_board.fixed_values[count - 1] = false;
                    sudoku_board.possible_values[count - 1] = true;
                } else if (v > 0) {
                    sudoku_board.board[count - 1] = (int) v;
                    sudoku_board.fixed_values[count - 1] = true;
                    sudoku_board.possible_values[count - 1] = false;
                }
                count++;
            }
        }
        if (line[0] == '\n' && line[1] == '\0') {
            break;
        }
    }
    return sudoku_board;
}


int main() {
    Sudoku_board sudoku_board = createBoard();
    print_sudoku_board(&sudoku_board);
    check_sudoku(&sudoku_board);
    delete_board(&sudoku_board);
}