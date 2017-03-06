#include "dancing_links_solver.h"
#include "sudoku_io.c"

///Create the 2D Linked list from the data array
void create_matrix() {
    int i, j;
    //Loop over all the elements in the data array
    for (int a = 0; a < nCol; a++) {
        for (int b = 0; b < nRow; b++) {
            if (data[a][b] != 0) {
                //Create the left pointer
                i = a;
                j = b;
                do { i = data_left(i); } while (data[i][j] == 0);
                matrix[a][b].Left = &matrix[i][j];
                //Create the right pointer
                i = a;
                j = b;
                do { i = data_right(i); } while (data[i][j] == 0);
                matrix[a][b].Right = &matrix[i][j];
                //Create the pointer above
                i = a;
                j = b;
                do { j = data_up(j); } while (data[i][j] == 0);
                matrix[a][b].Up = &matrix[i][j];
                //Create the pointer bellow
                i = a;
                j = b;
                do { j = data_down(j); } while (data[i][j] == 0);
                matrix[a][b].Down = &matrix[i][j];
                //Header pointer
                matrix[a][b].Header = &matrix[a][nRow - 1];
                matrix[a][b].IDNum = b;
                //Row Header
                row_header[b] = &matrix[a][b];
            }
        }
    }
    //Create the root
    root.Left = &matrix[nCol - 1][nRow - 1];
    root.Right = &matrix[0][nRow - 1];
    matrix[nCol - 1][nRow - 1].Right = &root;
    matrix[0][nRow - 1].Left = &root;
}

///Romve a node from the linked list
void cover(struct Node *col_node) {
    struct Node *row_node, *RightNode;
    //Remove the pointers the right and left nodes
    col_node->Right->Left = col_node->Left;
    col_node->Left->Right = col_node->Right;
    //Loop over the left and right nodes for the row and add the node remove them
    for (row_node = col_node->Down; row_node != col_node; row_node = row_node->Down) {
        for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) {
            RightNode->Up->Down = RightNode->Down;
            RightNode->Down->Up = RightNode->Up;
        }
    }
}

///Add the number to the correct location
void solution_row(struct Node *row_node) {
    //Create a new root
    cover(row_node->Header);
    struct Node *RightNode;
    //Update the board
    for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) {
        cover(RightNode->Header);
    }
}

///Add new number to the board
void add_number(int num, int row, int col) {
    //Place the number in the board
    solution_row(row_header[get_index(num, row, col)]);
    MaxK++;
    result[nResult++] = get_index(num, row, col);
}

///Print the board out
void print_board(void) {
    //Get n
    int size_squared = (int) pow(size, 2);
    int Sudoku[size_squared][size_squared];
    //Create a new board
    for (int a = 0; a < size_squared; a++)
        for (int b = 0; b < size_squared; b++)
            Sudoku[a][b] = -1;
    //Get all the numbers that belong in the board
    for (int a = 0; a < nResult; a++) {
        Sudoku[get_row_index(result[a])][get_col_index(result[a])] = get_number(result[a]);
    }
    //Loop over all the elements in the board
    for (int a = 0; a < size_squared; a++) {
        for (int b = 0; b < size_squared; b++) {
            Sudoku[a][b] + 1 < 10 ? printf("  %d", Sudoku[a][b] + 1) : printf(" %d", Sudoku[a][b] + 1);
        }
        printf("\n");
    }
}

///Create the board
void create_board_dxl(char *filename) {
    //Use the validator from the basic spec
    Sudoku_board validator;
    int Index, x;
    //Try and open file
    FILE *file = fopen(filename, "r");
    //Check to see if user input file
    (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));
    //Get the first number from the input to get n
    size = x;
    validator.size = x;
    validator.length = pow(x, 4);
    validator.board = (int *) malloc((size_t) (sizeof(int) * validator.length));
    validator.possible_values = (bool *) malloc((size_t) (sizeof(bool) * validator.length));
    int size_squared = (int) pow(x, 2);
    //Calculate the offsets from n
    int row_offset = (int) pow(x, 4);
    int col_offset = (int) pow(x, 4) * 2;
    int box_offset = (int) (pow(x, 4) * 3);
    //Set the number of requirements and number of possibilities using n
    nCol = (int) (4 * pow(pow(x, 2), 2));
    nRow = (int) pow(pow(x, 2), 3) + 1;
    //Dynamically create new array for the data bitmap array
    data = (char **) malloc(nRow * sizeof(char *));
    for (int i = 0; i < nRow; i++)
        data[i] = (char *) malloc(nRow * sizeof(char));
    //Dynamically create the new matrix array
    matrix = (struct Node **) malloc(nRow * sizeof(struct Node *));
    for (int i = 0; i < nRow; ++i)
        matrix[i] = (struct Node *) malloc(nRow * sizeof(struct Node));
    //Dynamically create the new row_header array
    row_header = (struct Node **) malloc(nRow * sizeof(struct Node *));
    for (int i = 0; i < nRow; ++i)
        row_header[i] = (struct Node *) malloc(nRow * sizeof(struct Node));

    result = calloc((size_t) nRow, sizeof(int));
    //Create the bitmap
    for (int a = 0; a < size_squared; a++) {
        for (int b = 0; b < size_squared; b++) {
            for (int c = 0; c < size_squared; c++) {
                Index = get_index(c, a, b);
                data[get_cell(Index)][Index] = 1; //Constraint 1: Only 1 per square
                data[row_offset + get_row_num(Index)][Index] = 1; //Constraint 2: Only 1 of per number per Row
                data[col_offset + get_col_num(Index)][Index] = 1; //Constraint 3: Only 1 of per number per Column
                data[box_offset + get_box_num(Index)][Index] = 1; //Constraint 4: Only 1 of per number per Box
            }
        }
    }
    //Mark row ends
    for (int a = 0; a < nCol; a++) {
        data[a][nRow - 1] = 2;
    }
    create_matrix();
    int count = 0;
    //Read the rest of the data in from file / stdin
    for (int i = 0; i < size_squared; i++) {
        for (int j = 0; j < size_squared; j++) {
            (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));
            validator.board[count] = x;
            if (x >= 1) {
                validator.possible_values[count] = false;
                add_number(x - 1, i, j);
            } else
                validator.possible_values[count] = true;

            count++;
        }
    }
    //Check if the input board is valid
    if (check_sudoku(validator) == INVALID)
        valid = false;
    else
        valid = true;

}

