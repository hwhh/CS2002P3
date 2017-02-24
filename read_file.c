#include "sudoku_header.h"

char *get_file_name() {
    char *filename = malloc(20);
    printf("Enter file name: ");
    scanf("%s0", filename);
    return filename;
}

Sudoku_board createBoard(char *filename) {
    Sudoku_board sudoku_board = NULL;
    FILE *file;
    file =fopen(filename,"r");

    if (!file)
        printf("Bad input");
    else {
        int  count=0, x = 0;
        double size = 0;
        fscanf (file, "%d", &x);
        while (!feof (file)) {
            if (count==0) {
                sudoku_board.size = x;
                size = pow(x,4);
                sudoku_board.board = (int *) malloc((size_t) (sizeof(int) * size));
                sudoku_board.fixed_values = (bool *) malloc((size_t) (sizeof(bool) * size));
                sudoku_board.possible_values = (bool *) malloc((size_t) (sizeof(bool) * size));
                count++;
            }
            else {
                if (x < pow(sudoku_board.size, 2) && x >= 0) {
                    if(x == 0){
                        sudoku_board.board[count - 1] = x;
                        sudoku_board.fixed_values[count - 1] = false;
                        sudoku_board.possible_values[count - 1] = true;
                    } else if (x > 0) {
                        sudoku_board.board[count - 1] = x;
                        sudoku_board.fixed_values[count - 1] = true;
                        sudoku_board.possible_values[count - 1] = false;
                    }
                    count++;
                }
            }
            fscanf (file, "%d", &x);
        }
        fclose(file);
    }
    return sudoku_board;
}