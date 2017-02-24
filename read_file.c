#include "sudoku_header.h"

char* getFileName() {
    char *filename = malloc(20);
    printf("Enter file name: ");
    scanf("%s0", filename);
    return filename;
}

SudokuBoard createBoard(char* filename){
    SudokuBoard sudokuBoard = NULL;
    FILE *file;
    file =fopen(filename,"r");

    if (!file)
        printf("Bad input");
    else {
        int  count=0, x = 0;
        double size=0;//2^4
        fscanf (file, "%d", &x);
        while (!feof (file)) {
            if (count==0) {
                sudokuBoard.size = x;
                size = pow(x,4);
                sudokuBoard.board = (int*)malloc((size_t) (sizeof(int) * size));
                sudokuBoard.fixedValues = (bool *) malloc((size_t) (sizeof(bool) * size));
                sudokuBoard.possibleValues = (bool *)malloc((size_t) (sizeof(bool) * size));
                count++;
            }
            else {
                if (x < size && x>=0) {
                    if(x == 0){
                        sudokuBoard.board [count-1]= x;
                        sudokuBoard.fixedValues[count-1] = false;
                        sudokuBoard.possibleValues[count-1] = true;
                    } else if (x > 0) {
                        sudokuBoard.board [count-1] = x;
                        sudokuBoard.fixedValues[count-1] = true;
                        sudokuBoard.possibleValues[count-1] = false;
                    }
                    count++;
                }
            }
            fscanf (file, "%d", &x);
        }
        fclose(file);
    }
    return sudokuBoard;
}