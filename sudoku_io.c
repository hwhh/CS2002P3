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

int *get_row(Sudoku_board *sudoku_board, int index, double size) {
    int *row = malloc((size_t) size);
    for (int j = 0; j < size; j++) {
        row[j] = sudoku_board->board[index + j];
    }
    return row;
}

int *get_col(Sudoku_board *sudoku_board, int index, double size) {
    int *col = malloc((size_t) size);
    int count = 0;
    for (int j = 0; j < sudoku_board->length; j += size) {
        col[count] = sudoku_board->board[index + j];
        count++;
    }
    return col;
}

int *get_box(Sudoku_board *sudoku_board, int index, double size) {
    int *box = malloc((size_t) size);
    int offset = index;
    for (int j = 0; j < size; j++) {
        if (j % sudoku_board->size == 0 && j > 0) {
            offset += (size - sudoku_board->size + 1);
            box[j] = sudoku_board->board[offset - 1];
        } else
            box[j] = sudoku_board->board[offset++];
    }
    return box;
}


enum STATE check_sudoku(Sudoku_board *sudoku_board) {
    int status = 1;
    double size = pow(sudoku_board->size, 2);
    for (int i = 0; i < sudoku_board->length; i += size) {
        int *row = get_row(sudoku_board, i, size);
        int res = check_list(row, (int) size);
        free(row);
        if (res == -1) {
            printf("INVALID");
            return INVALID;
        } else if (res == 0)
            status = 0;
    }
    for (int i = 0; i < size; i++) {
        int *col = get_col(sudoku_board, i, size);
        int res = check_list(col, (int) size);
        free(col);
        if (res == -1) {
            printf("INVALID");
            return INVALID;
        } else if (res == 0)
            status = 0;
    }
    int offset = 0;
    for (int i = 0; i < pow(sudoku_board->size, 3); i += sudoku_board->size) {
        if (i % (int) size == 0 && i > 0)
            offset += pow(sudoku_board->size, 3) - size;
        int *box = get_box(sudoku_board, i + offset, size);
        int res = check_list(box, (int) size);
        free(box);
        if (res == -1) {
            printf("INVALID");
            return INVALID;
        } else if (res == 0)
            status = 0;
    }
    if (status == 0) {
        printf("INCOMPLETE");
        return INCOMPLETE;
    }
    printf("COMPLETE");
    return COMPLETE;
}

Sudoku_board create_board(char *filename) {
    static Sudoku_board sudoku_board;
    int x = 0;
    FILE *file;
    file = fopen(filename, "r");
    if (!file)
        fscanf(stdin, "%d", &x);
    else
        fscanf(file, "%d", &x);
    sudoku_board.size = x;
    sudoku_board.length = pow(x, 4);
    sudoku_board.board = (int *) malloc((size_t) (sizeof(int) * sudoku_board.length));
    sudoku_board.possible_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
    int count = 0;
    if (!file)
        fscanf(stdin, "%d", &x);
    else
        fscanf(file, "%d", &x);
    while (count < sudoku_board.length) {
        if (x == 0) {
            sudoku_board.board[count] = x;
            sudoku_board.possible_values[count] = true;
        } else if (x > 0) {
            sudoku_board.board[count] = x;
            sudoku_board.possible_values[count] = false;
        }
        count++;
        if (count < sudoku_board.length)
            if (!file)
                fscanf(stdin, "%d", &x);
            else
                fscanf(file, "%d", &x);
    }
    return sudoku_board;
}

//
//int main(){
//    Sudoku_board s = create_board("/Users/henryhargreaves/Documents/University/Year_2/CS2002/Practicals/Practical3-C2/TestFIiles/incomplete-2.in");
//    print_sudoku_board(&s);
//    check_sudoku(&s);
//    delete_board(&s);
//}
//




































//
//enum STATE check_sudoku(Sudoku_board *sudoku_board) {
//    int status = 1;
//    int offset = 0;
//    int root = (int) pow(sudoku_board->size, 3);
//    double size = pow(sudoku_board->size, 2);
//    for (int i = 0; i < sudoku_board->length; i += size) {
//        int row[(int) size];
//        for (int j = 0; j < size; j++) {
//            row[j] = sudoku_board->board[i + j];
//        }
//        if (check_list(row, (int) size) == -1) {
//            printf("INVALID");
//            return INVALID;
//        } else if (check_list(row, (int) size) == 0)
//            status = 0;
//    }
//    for (int i = 0; i < size; i++) {
//        int count = 0;
//        int col[(int) size];
//        for (int j = 0; j < sudoku_board->length; j += size) {
//            col[count] = sudoku_board->board[i + j];
//            count++;
//        }
//        if (check_list(col, (int) size) == -1) {
//            printf("INVALID");
//            return INVALID;
//        } else if (check_list(col, (int) size) == 0)
//            status = 0;
//    }
//    for (int i = 0; i < sudoku_board->length; i += size) {
//        int box[(int) size];
//        for (int j = 0; j < size; j++) {
//            if (j % sudoku_board->size == 0 && j > 0) {
//                offset += (size - sudoku_board->size + 1);
//                box[j] = sudoku_board->board[offset - 1];
//            } else
//                box[j] = sudoku_board->board[offset++];
//        }
//        if (offset % root != 0)
//            offset -= (size * (sudoku_board->size - 1));
//        if (check_list(box, (int) size) == -1) {
//            printf("INVALID");
//            return INVALID;
//        } else if (check_list(box, (int) size) == 0)
//            status = 0;
//    }
//    if (status == 1) {
//        printf("COMPLETE");
//        return COMPLETE;
//    }else if (status == 0) {
//        printf("INCOMPLETE");
//        return INCOMPLETE;
//    }
//
//}



