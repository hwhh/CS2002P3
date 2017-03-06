#include "sudoku_io.c"

int counter = 0;
Sudoku_board solved_board;
bool changes_made = true;

///Check if an input array contains a value
bool contains(int *arr, int val, int size) {
    //Loop over contents of the array
    for (int i = 0; i < size; i++) {
        //Check for value
        if (arr[i] == val && val != 0)
            return true;
    }
    return false;
}

///Get the index of the row
int get_row_location(int index, int size) {
    int box_size = (int) pow(size, 2);
    return (index / box_size);
}

///Get the index of the column
int get_col_location(int index, int size) {
    int box_size = (int) pow(size, 2);
    return (index % box_size);
}

///Get the index of the box
int get_box_location(int index, int size) {
    int box_size = (int) pow(size, 2);
    //Index the boxes
    int x = ((index % box_size) / size);
    int y = (index / box_size) / size;
    //Calculate the box id
    int box_id = ((size * y) + x);
    //Determine row and column offset
    int offset_y = (int) (pow(size, 3) * floor((box_id * size) / box_size));
    int offset_x = (box_id % size) * size;
    return offset_x + offset_y;
}

///Get all the possible values at a location given a board
int *get_possible_values(Sudoku_board sudoku_board, int index) {
    //Gte the board size
    int size = sudoku_board.size;
    int box_size = (int) pow(size, 2);
    //Create a new array which can accommodate all the possible values
    int *possible_values = calloc((size_t) box_size, sizeof(int));
    //Calculate the box, row and column id
    int row_id = box_size * get_row_location(index, size);
    int col_id = get_col_location(index, size);
    int box_id = get_box_location(index, size);
    //Get the contents of the box, row and column
    int *row = get_row(sudoku_board, row_id, box_size);
    int *col = get_col(sudoku_board, col_id, box_size);
    int *box = get_box(sudoku_board, box_id, box_size);
    int count = 0;
    //Find all the values that aren't in the box, row or column
    for (int i = 1; i < box_size + 1; i++) {
        if (!contains(row, i, box_size) && !contains(col, i, box_size) && !contains(box, i, box_size)) {
            possible_values[count] = i;
            count++;
        }
    }
    //Free all the arrays
    free(row);
    free(box);
    free(col);
    return possible_values;
}

///Get the next free cell
int get_nex_cell(Sudoku_board sudoku_board, int index) {
    for (int i = index; i < sudoku_board.length; i++) {
        if (sudoku_board.possible_values[i] == true)
            return i;
    }
}

///Solve the Sudoku board
enum STATE sudoku_solve(Sudoku_board sudoku_board) {
    int state = check_sudoku(sudoku_board);
    //If the board is complete return COMPLETE
    if (state == 1) {
        solved_board = sudoku_board;
        counter++;
        return COMPLETE;
        //If the board is invalid return UNSOLVABLE
    } else if (state == -1) {
        return UNSOLVABLE;
    } else {
        //Get the next free cell
        int index = get_nex_cell(sudoku_board, 0);
        //Get the valid values for that cell
        int *values = get_possible_values(sudoku_board, index);
        //Try each valid value
        for (int i = 0; i < pow(sudoku_board.size, 2); i++) {
            //If no more valid values break
            if (values[i] == 0)
                break;
            //Create copy of board and update it
            Sudoku_board copy = copy_sudoku_board(sudoku_board);
            copy.board[index] = values[i];
            copy.possible_values[index] = false;
            //Check if more than one solution
            if (counter > 1)
                return MULTIPLE;
            else
                sudoku_solve(copy);
        }
        free(values);
    }
}


///Calculate the number of free cells
int free_cells(Sudoku_board sudoku_board) {
    int count = 0;
    //For every cell that is empty increment count
    for (int i = 0; i < sudoku_board.length; i++) {
        if (sudoku_board.possible_values[i] == true)
            count++;
    }
    return count;
}

///Fill all the cells that can only contain one value
Sudoku_board fill_single_cell(Sudoku_board sudoku_board) {
    changes_made = false;
    //Create a copy of the board
    Sudoku_board copy = copy_sudoku_board(sudoku_board);
    int no_of_cells = free_cells(copy);
    for (int i = 0; i < no_of_cells; i++) {
        //Get next empty cell
        int index = get_nex_cell(copy, i);
        int *values = get_possible_values(copy, index);
        if (check_sudoku(copy) == 1)
            return sudoku_board;
        //Check if second value is 0
        if (values[1] == 0) {
            //Fill cell
            copy.board[index] = values[0];
            copy.possible_values[index] = false;
            changes_made = true;
        }
        free(values);
    }
    return copy;
}

///Solve the Sudoku board by filling all the certian values until there are no more certain values
enum STATE sudoku_solve_opt(Sudoku_board sudoku_board) {
    int state = check_sudoku(sudoku_board);
    //If the board is complete return COMPLETE
    if (state == 1) {
        print_sudoku_board(sudoku_board);
        return COMPLETE;
        //If the board is invalid return UNSOLVABLE
    } else if (state == -1)
        return UNSOLVABLE;
    else {
        //Loop until no changes have been made signifying there are no more certain values
        Sudoku_board s = sudoku_board;
        while (changes_made != false) {
            s = fill_single_cell(s);
            //If the board is complete return COMPLETE
            if (check_sudoku(s) == 1) {
                print_sudoku_board(s);
                return COMPLETE;
            }
        }
        return INCOMPLETE;
    }
}




