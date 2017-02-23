#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//
//typedef struct {
//    //thinking represents the boxes in the board ???
//};


typedef struct {
    int size;
    int *board;
//    bool fixedValues[];
//    bool possibleValues[];

}SudokuBoard;


//void readBoard(char *file, SudokuBoard *mainBoard){
//
//}

/*
 * This is wrong for now as should be getting the boxes
 * TODO update with x axis as letters and y axis as numbers
 */
int getCoordinates(int x, int y, int size){
    return y+(x*(size*size));
}


int readValue(SudokuBoard sudokuBoard){
    int locations[2];
    int value = -1;
    printf("please input location: ");
    scanf("%d,%d", &locations[0], &locations[1]);
    int location = getCoordinates(locations[0], locations[1], sudokuBoard.size);
    return sudokuBoard.board[location];
}


int main(){
    SudokuBoard sudokuBoard;
    sudokuBoard.size= 2;
    sudokuBoard.board = (int*)malloc(sizeof(int) * 16);
    int temp[16]  = {0, 2,  3,  4, 3,  4,  1,  2, 4,  0,  2,  1, 2,  0,  4,  0};
    for (int i = 0; i < 16; i++){
        sudokuBoard.board[i] = temp[i];
    }
    printf("%d",readValue(sudokuBoard));
    //now you can fill the array with the same syntax as before.
    //when you no longer need to use the array you have to free the
    //allocated memory block.
    free( sudokuBoard.board);
    return 0;
};