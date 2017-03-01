//
// Created by Henry Hargreaves on 01/03/2017.
//

#ifndef PRACTICAL3_DANCING_LINKS_HEADER_H
#define PRACTICAL3_DANCING_LINKS_HEADER_H

#endif //PRACTICAL3_DANCING_LINKS_HEADER_H


typedef struct {

    struct Node *Header;
    struct Node *Left;
    struct Node *Right;
    struct Node *Up;
    struct Node *Down;

    char IDName;
    int IDNum;
} Node;

int rows, cols, row_offset, col_offset, box_offset;


int get_number(int index, int size) {
    return (int) (index / pow(size, 4));
}

int get_row(int index, int size) {
    return (int) (index / pow(size, 2)) % (int) pow(size, 2);
}

int get_col(int index, int size) {
    return index % (int) pow(size, 2);
}

int get_box(int index, int size) {
    return ((get_row(index, size) / size) * size) + (get_col(index, size) / size);
}

int get_cell(int index, int size) {
    return (int) (get_row(index, size) * pow(size, 2) + get_col(index, size));
}

int get_row_number(int index, int size) {
    return (int) (get_number(index, size) * pow(size, 2) + get_row(index, size));
}

int get_col_number(int index, int size) {
    return (int) (get_number(index, size) * pow(size, 2) + get_col(index, size));
}

int get_box_number(int index, int size) {
    return (int) (get_number(index, size) * pow(size, 2) + get_box(index, size));
}


// Function that get 3-digit integer index from given info
int get_index(int num, int row, int col, int size) {
    return (int) (num * pow(size, 4) + row * pow(size, 2) + col);
}







