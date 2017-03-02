
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum STATE {
    UNSOLVABLE = -1,//": The array contains some value twice.",
    COMPLETE = 1,//": The array is not INVALID, and every value is assigned. \n"This means the array contains the values between 1 and 9, in some permutation."
};


struct Node {

    struct Node *Header;
    struct Node *Left;
    struct Node *Right;
    struct Node *Up;
    struct Node *Down;
    int IDNum;
};


struct Node **matrix;
struct Node root;
struct Node *root_node = &root;
struct Node **row_header;


char **data;
int *result;
int nResult = 0, MaxK, nCol, nRow, size;
char Finished;

// --> Initialisation functions
int data_left(int i) {
    return i - 1 < 0 ? nCol - 1 : i - 1;
}

int data_right(int i) {
    return (i + 1) % nCol;
}

int data_up(int i) {
    return i - 1 < 0 ? nRow - 1 : i - 1;
}

int data_down(int i) {
    return (i + 1) % nRow;
}

// Functions that extract data from a given 3-digit integer index number in the format [N] [R] [C].
int get_number(int index) {
    return (int) (index / pow(size, 4));
}

int get_row(int index) {
    return (int) (index / pow(size, 2)) % (int) pow(size, 2);
}

int get_col(int index) {
    return index % (int) pow(size, 2);
}

int get_box(int index) {
    return ((get_row(index) / size) * size) + (get_col(index) / size);
}

int get_cell(int index) {
    return (int) (get_row(index) * pow(size, 2) + get_col(index));
}

int get_row_num(int index) {
    return (int) (get_number(index) * pow(size, 2) + get_row(index));
}

int get_col_num(int index) {
    return (int) (get_number(index) * pow(size, 2) + get_col(index));
}

int get_box_num(int index) {
    return (int) (get_number(index) * pow(size, 2) + get_box(index));
}


// Function that get 3-digit integer index from given info
int get_index(int num, int row, int col) {
    return (int) (num * pow(size, 4) + row * pow(size, 2) + col);
}

