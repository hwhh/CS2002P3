#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dancing_links_header.h"

void CreateMatrix() {
    int i, j;
    row_header = malloc(rows * sizeof(Node));
    //Build toroidal linklist matrix according to data bitmap
    for (int a = 0; a < cols; a++) {
        for (int b = 0; b < rows; b++) {
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
                matrix[a][b].Header = &matrix[a][rows - 1];
                matrix[a][b].IDNum = b;
                //Row Header
                row_header[b] = &matrix[a][b];
            }
        }
    }
    for (int a = 0; a < cols; a++) {
        matrix[a][rows - 1].IDName = 'C';
        matrix[a][rows - 1].IDNum = a;
    }
    //Insert root
    root.IDName = 'R';
    root.Left = &matrix[cols - 1][rows - 1];
    root.Right = &matrix[0][rows - 1];
    matrix[cols - 1][rows - 1].Right = &root;
    matrix[0][rows - 1].Left = &root;
}



Node *create_board(char *filename) {
    int x = 0;
    FILE *file;
    file = fopen(filename, "r");
    (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));

    row_offset = (int) pow(x, 3);
    col_offset = (int) pow(x, 3) * 2;
    box_offset = (int) pow(x, 3) * 3;
    cols = (int) (4 * pow(pow(x, 2), 2));
    rows = (int) pow(pow(x, 2), 3) + 1;

    int size = (int) pow(x, 2), index;
    data = malloc(rows * sizeof(char *) + (rows * (rows * sizeof(char))));
    matrix = malloc(rows * sizeof(Node) + (rows * (rows * sizeof(Node))));

    for (int i = 0; i < size; i++) {
        for (int b = 0; b < size; b++) {
            for (int c = 0; c < size; c++) {
                index = get_index(c, i, b, x);
                data[get_cell(index, x)][index] = 1; //Constraint 1: Only 1 per square
                data[row_offset + get_row_number(index, x)][index] = 1; //Constraint 2: Only 1 of per number per Row
                data[col_offset + get_col_number(index, x)][index] = 1; //Constraint 3: Only 1 of per number per Column
                data[box_offset + get_box_number(index, x)][index] = 1; //Constraint 4: Only 1 of per number per Box
            }
        }
    }
    for (int i = 0; i < cols; i++) {
        data[i][rows - 1] = 2;
    }
    for (int i = 0; i < row_offset; i++) {
        matrix[i][rows - 1].IDName = 'S';
        matrix[i][rows - 1].IDNum = i;
    }

    for (int i = row_offset; i < col_offset; i++) {
        matrix[i][rows - 1].IDName = 'R';
        matrix[i][rows - 1].IDNum = i - row_offset;
    }

    for (int i = col_offset; i < box_offset; i++) {
        matrix[i][rows - 1].IDName = 'C';
        matrix[i][rows - 1].IDNum = i - col_offset;
    }

    for (int i = box_offset; i < cols; i++) {
        matrix[i][rows - 1].IDName = 'B';
        matrix[i][rows - 1].IDNum = i - box_offset;
    }
}


int main() {

}

