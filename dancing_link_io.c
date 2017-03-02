#include "dancing_links_solver.h"

void create_matrix() {
    int i, j;
    //Build toroidal linklist matrix according to data bitmap
    for (int a = 0; a < nCol; a++) {
        for (int b = 0; b < nRow; b++) {
            if (data[a][b] != 0) {
                // Left pointer
                i = a;
                j = b;
                do { i = data_left(i); } while (data[i][j] == 0);
                matrix[a][b].Left = &matrix[i][j];
                // Right pointer
                i = a;
                j = b;
                do { i = data_right(i); } while (data[i][j] == 0);
                matrix[a][b].Right = &matrix[i][j];
                // Up pointer
                i = a;
                j = b;
                do { j = data_up(j); } while (data[i][j] == 0);
                matrix[a][b].Up = &matrix[i][j];
                // Down pointer
                i = a;
                j = b;
                do { j = data_down(j); } while (data[i][j] == 0);
                matrix[a][b].Down = &matrix[i][j];
                // Header pointer
                matrix[a][b].Header = &matrix[a][nRow - 1];
                matrix[a][b].IDNum = b;
                //Row Header
                row_header[b] = &matrix[a][b];
            }
        }
    }
    root.Left = &matrix[nCol - 1][nRow - 1];
    root.Right = &matrix[0][nRow - 1];
    matrix[nCol - 1][nRow - 1].Right = &root;
    matrix[0][nRow - 1].Left = &root;
}

void cover(struct Node *col_node) {
    struct Node *row_node, *RightNode;
    col_node->Right->Left = col_node->Left;
    col_node->Left->Right = col_node->Right;
    for (row_node = col_node->Down; row_node != col_node; row_node = row_node->Down) {
        for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) {
            RightNode->Up->Down = RightNode->Down;
            RightNode->Down->Up = RightNode->Up;
        }
    }
}

void solution_row(struct Node *row_node) {
    cover(row_node->Header);
    struct Node *RightNode;
    for (RightNode = row_node->Right; RightNode != row_node; RightNode = RightNode->Right) { cover(RightNode->Header); }
}

void add_number(int num, int row, int col) {
    solution_row(row_header[get_index(num, row, col)]);
    MaxK++;
    result[nResult++] = get_index(num, row, col);
}

void print_board(void) {
    int size_squared = (int) pow(size, 2);
    int Sudoku[size_squared][size_squared];
    for (int a = 0; a < size_squared; a++)
        for (int b = 0; b < size_squared; b++)
            Sudoku[a][b] = -1;
    for (int a = 0; a < nResult; a++) {
        Sudoku[get_row(result[a])][get_col(result[a])] = get_number(result[a]);
    }
    for (int a = 0; a < size_squared; a++) {
        for (int b = 0; b < size_squared; b++) {
            Sudoku[a][b] + 1 < 10 ? printf("  %d", Sudoku[a][b] + 1) : printf(" %d", Sudoku[a][b] + 1);
        }
        printf("\n");
    }
}

void create_board(char *filename) {
    int Index, x;

    FILE *file = fopen(filename, "r");
    (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));

    size = x;
    int size_squared = (int) pow(x, 2);
    int row_offset = (int) pow(x, 4);
    int col_offset = (int) pow(x, 4) * 2;
    int box_offset = (int) (pow(x, 4) * 3);
    nCol = (int) (4 * pow(pow(x, 2), 2));
    nRow = (int) pow(pow(x, 2), 3) + 1;


    data = (char **) malloc(nRow * sizeof(char *));
    for (int i = 0; i < nRow; i++)
        data[i] = (char *) malloc(nRow * sizeof(char));

    matrix = (struct Node **) malloc(nRow * sizeof(struct Node *));
    for (int i = 0; i < nRow; ++i)
        matrix[i] = (struct Node *) malloc(nRow * sizeof(struct Node));

    row_header = (struct Node **) malloc(nRow * sizeof(struct Node *));
    for (int i = 0; i < nRow; ++i)
        row_header[i] = (struct Node *) malloc(nRow * sizeof(struct Node));

    result = calloc((size_t) nRow, sizeof(int));


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
    for (int a = 0; a < nCol; a++) {
        data[a][nRow - 1] = 2;
    }
    create_matrix();
    for (int i = 0; i < size_squared; i++) {
        for (int j = 0; j < size_squared; j++) {
            (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));
            if (x >= 1)
                add_number(x - 1, i, j);
        }
    }
}

