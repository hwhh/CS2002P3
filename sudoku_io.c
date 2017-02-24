//TODO update with x axis as letters and y axis as numbers and change to account for boxes
#include "sudoku_header.h"


bool writeValue(SudokuBoard sudokuBoard, int value){
    int location = getCoordinates(sudokuBoard.size);
    sudokuBoard.board[location] = value;
    return true;
}

int readValue(SudokuBoard sudokuBoard){
    int location = getCoordinates(sudokuBoard.size);
    return sudokuBoard.board[location];
}

void printSudokuBoard(SudokuBoard sudokuBoard){
    int size = sudokuBoard.size;
    printf("%d", size);
    for(int i = 0; i < size*size; i++){
        for (int j =0; j<size*size; j++){
            printf("%d ", sudokuBoard.board[i+j]);
        }
        printf("\n");
    }
}

SudokuBoard copySudokuBoard(SudokuBoard sudokuBoard){
    return sudokuBoard;
}

bool freeSudokuBoard(SudokuBoard sudokuBoard){
    int size = sudokuBoard.size;
    for (int i =0; i < pow(size, 4); i++){
        sudokuBoard.board[i]=0;
    }
    return true;
}

int getCoordinates(int size){
    int locations[2];
    printf("please input location: ");
    scanf("%d,%d", &locations[0], &locations[1]);
    return locations[1]+(locations[0]*(size*size));
}

int main(){



    return 0;
};













//    SudokuBoard sudokuBoard;
//    sudokuBoard.size= 2;
//    sudokuBoard.board = (int*)malloc(sizeof(int) * 16);
//    int temp[16]  = {0, 2,  3,  4, 3,  4,  1,  2, 4,  0,  2,  1, 2,  0,  4,  0};
//    for (int i = 0; i < 16; i++){
//        sudokuBoard.board[i] = temp[i];
//    }
//    printf("%d",readValue(sudokuBoard));
//    //now you can fill the array with the same syntax as before.
//    //when you no longer need to use the array you have to free the
//    //allocated memory block.
//    free( sudokuBoard.board);