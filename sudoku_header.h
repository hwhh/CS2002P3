#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#ifndef PRACTICAL3_SUDOKU_HEADER_H
#define PRACTICAL3_SUDOKU_HEADER_H

#endif //PRACTICAL3_SUDOKU_HEADER_H

typedef struct {
    int size;
    int *board;
    bool *fixedValues;
    bool *possibleValues;
}SudokuBoard;

bool writeValue(SudokuBoard sudokuBoard, int value);
int readValue(SudokuBoard sudokuBoard);
int getCoordinates(int size);
void printSudokuBoard(SudokuBoard sudokuBoard);
SudokuBoard copySudokuBoard(SudokuBoard sudokuBoard);
bool freeSudokuBoard(SudokuBoard sudokuBoard);