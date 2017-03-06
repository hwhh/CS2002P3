#include "sudoku_header.h"

///Print an input Sudoku board
void print_sudoku_board(Sudoku_board sudoku_board) {
    //Get the size of the Sudoku board
    int size = sudoku_board.size;
    //Loop n elements at a time
    for (int i = 0; i < sudoku_board.length; i += pow(size, 2)) {
        for (int j =0; j<size*size; j++){
            //Print the elements in the board with correct formatting
            sudoku_board.board[i + j] < 10 ? printf("  %d", sudoku_board.board[i + j]) : printf(" %d",
                                                                                                sudoku_board.board[i +
                                                                                                                   j]);
        }
        printf("\n");
    }
}

///Copy all the elements in the Sudoku board to a new Sudoku board
Sudoku_board copy_sudoku_board(Sudoku_board sudoku_board) {
    Sudoku_board copy;
    copy.size = sudoku_board.size;
    copy.length = sudoku_board.length;
    //Dynamically create the new arrays
    copy.board = (int *) malloc((size_t) (sizeof(int) * sudoku_board.length));
    copy.possible_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
    //Copy each value over
    for (int i = 0; i < copy.length; i++) {
        copy.board[i] = sudoku_board.board[i];
        copy.possible_values[i] = sudoku_board.possible_values[i];
    }
    return copy;
}

///Free all the arrays allocated on the stack
void delete_board(Sudoku_board sudoku_board) {
    free(sudoku_board.board);
    free(sudoku_board.possible_values);
}


///Check an array for duplicates and 0's
enum STATE check_list(int *contents, int size) {
    bool duplicate = false;
    bool zero = false;
    //Loop n times
    for (int i = 0; i < size; i++) {
        //Check for 0's
        if (contents[i] == 0)
            zero = true;
        //Check for duplicates
        for (int j = i + 1; j < size; j++)
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

///Get all the elements in row by index
int *get_row(Sudoku_board sudoku_board, int index, int size) {
    //Create new array
    int *row = calloc((size_t) size, sizeof(int));
    //Add elements
    for (int j = 0; j < size; j++) {
        row[j] = sudoku_board.board[index + j];
    }
    return row;
}

///Get all the elements in column by index
int *get_col(Sudoku_board sudoku_board, int index, int size) {
    //Create new array
    int *col = calloc((size_t) size, sizeof(int));
    int count = 0;
    //Add elements
    for (int j = 0; j < sudoku_board.length; j += size) {
        col[count] = sudoku_board.board[index + j];
        count++;
    }
    return col;
}

///Get all the elements in box by index
int *get_box(Sudoku_board sudoku_board, int index, int size) {
    //Create new array
    int *box = calloc((size_t) size, sizeof(int));
    int offset = index;
    for (int j = 0; j < size; j++) {
        //Check to see at edge of the box
        if (j % sudoku_board.size == 0 && j > 0) {
            //Adjust offset to skip remaining elements in row
            offset += (size - sudoku_board.size + 1);
            box[j] = sudoku_board.board[offset - 1];
        } else
            box[j] = sudoku_board.board[offset++];
    }
    return box;
}

///Check to see if a board is valid
enum STATE check_sudoku(Sudoku_board sudoku_board) {
    int status = 1;
    int size = (int) pow(sudoku_board.size, 2);
    //Check all the rows
    for (int i = 0; i < sudoku_board.length; i += size) {
        //Get the row and check it
        int *row = get_row(sudoku_board, i, size);
        int res = check_list(row, (int) size);
        free(row);
        if (res == -1) {
            return INVALID;
        } else if (res == 0)
            status = 0;
    }
    //Check all the columns
    for (int i = 0; i < size; i++) {
        //Get the column and check it
        int *col = get_col(sudoku_board, i, size);
        int res = check_list(col, size);
        free(col);
        if (res == -1) {
            return INVALID;
        } else if (res == 0)
            status = 0;
    }
    int offset = 0;
    //Check all the boxes
    for (int i = 0; i < pow(sudoku_board.size, 3); i += sudoku_board.size) {
        //Check to see if how many rows of boxes down to adjust offset
        if (i % (int) size == 0 && i > 0)
            offset += pow(sudoku_board.size, 3) - size;
        //Get the box and check it
        int *box = get_box(sudoku_board, i + offset, size);
        int res = check_list(box, size);
        free(box);
        if (res == -1) {
            return INVALID;
        } else if (res == 0)
            status = 0;
    }
    //Return the sate
    if (status == 0) {
        return INCOMPLETE;
    }
    return COMPLETE;
}

///Parse the input and create Sudoku board instace
Sudoku_board create_board(char *filename) {
    static Sudoku_board sudoku_board;
    int x = 0;
    FILE *file;
    //Try and open file
    file = fopen(filename, "r");
    //Check to see if user input file
    (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));
    //Get the first number from the input to get n
    sudoku_board.size = x;
    sudoku_board.length = pow(x, 4);
    sudoku_board.board = (int *) malloc((size_t) (sizeof(int) * sudoku_board.length));
    sudoku_board.possible_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
    int count = 0;
    //Get the next number from the input file / stdin
    (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));
    //Loop n^4 times to get all the values
    while (count < sudoku_board.length) {
        //Check if cell is empty and therefore available
        if (x == 0) {
            sudoku_board.board[count] = x;
            sudoku_board.possible_values[count] = true;
        } else if (x > 0) {
            sudoku_board.board[count] = x;
            sudoku_board.possible_values[count] = false;
        }
        count++;
        if (count < sudoku_board.length)
            (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));
    }
    check_sudoku(sudoku_board);
    return sudoku_board;
}



