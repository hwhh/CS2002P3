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

char **data;
Node **matrix;
Node root;
Node *root_node = &root;
Node *row_header[];

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


int data_left(int i) {
    return i - 1 < 0 ? cols - 1 : i - 1;
}

int data_right(int i) {
    return (i + 1) % cols;
}

int data_up(int i) {
    return i - 1 < 0 ? rows - 1 : i - 1;
}

int data_down(int i) {
    return (i + 1) % rows;
}





