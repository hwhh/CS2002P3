#include <stdio.h>
#include <math.h>
#include "dancing_links_header.h"


Node *create_board(char *filename) {

    int x = 0;
    FILE *file;
    file = fopen(filename, "r");
    (!file ? fscanf(stdin, "%d", &x) : fscanf(file, "%d", &x));

    row_offset = (int) pow(x, 3);
    col_offset = (int) pow(x, 3) * 2;
    col_offset = (int) pow(x, 3) * 3;
    cols = (int) (4 * pow(pow(x, 2), 2));
    rows = (int) pow(pow(x, 2), 3) + 1;

    int size = (int) pow(x, 2), index;
    char data[rows][rows];

    for (int a = 0; a < size; a++) {
        for (int b = 0; b < size; b++) {
            for (int c = 0; c < size; c++) {
                index = get_index(c, a, b, x);
                data[get_cell(index, x)][index] = 1; //Constraint 1: Only 1 per square
                data[row_offset + get_row_number(index, x)][index] = 1; //Constraint 2: Only 1 of per number per Row
                data[col_offset + get_col_number(index, x)][index] = 1; //Constraint 3: Only 1 of per number per Column
                data[box_offset + get_box_number(index, x)][index] = 1; //Constraint 4: Only 1 of per number per Box
            }
        }
    }
}


int main() {

}

