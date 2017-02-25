#include "sudoku_header.h"


char *get_file_name() {
    char *filename = malloc(20);
    printf("Enter file name: ");
    scanf("%s0", filename);
    return filename;
}

Sudoku_board createBoard(char *filename) {
    Sudoku_board sudoku_board;
    FILE *file;
    file =fopen(filename,"r");
    if (!file)
        printf("Bad input");
    else {
        int count = 0, x = 0;
        fscanf (file, "%d", &x);
        while (!feof (file)) {
            if (count==0) {
                sudoku_board.size = x;
                sudoku_board.length = pow(x, 4);
                sudoku_board.board = (int *) malloc((size_t) (sizeof(int) * sudoku_board.length));
                sudoku_board.fixed_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
                sudoku_board.possible_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
                count++;
            }
            else {
                if (x <= pow(sudoku_board.size, 2) && x >= 0) {
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


void check_sudoku(Sudoku_board *sudoku_board) {
    int offset = 0;
    int root = (int) pow(sudoku_board->size, 3);
    double size = pow(sudoku_board->size, 2);
    for (int i = 0; i < sudoku_board->length; i += size) {
        int row[(int) size];
        for (int j = 0; j < size; j++) {
            row[j] = sudoku_board->board[i + j];
        }
//        if (!check_list(row, (int) size) == -1)
//            break;
    }

    for (int i = 0; i < size; i++) {
        int count = 0;
        int col[(int) size];
        for (int j = 0; j < sudoku_board->length; j += size) {
            col[count] = sudoku_board->board[i + j];
            count++;
        }
//        if (!check_list(col, (int) size) == -1)
//            break;
        for (int k = 0; k < size; k++) {
            printf("%d ", col[k]);
        }
        printf("\n");
    }

    for (int i = 0; i < sudoku_board->length; i += size) {
        int box[(int) size];
        for (int j = 0; j < size; j++) {
            if (j % sudoku_board->size == 0 && j > 0) {
                offset += (size - sudoku_board->size + 1);
                box[j] = sudoku_board->board[offset - 1];
            } else
                box[j] = sudoku_board->board[offset++];
        }
        if (offset % root != 0)
            offset -= (size * (sudoku_board->size - 1));

//        if (!check_list(box, (int) size) == -1)
//            break;
    }


}

int main() {
    Sudoku_board sudoku_board = createBoard(
            "/Users/henryhargreaves/Documents/University/Year_2/CS2002/Practicals/Practical3/TestFIiles/incomplete-2.in");
    check_sudoku(&sudoku_board);
    return 0;
};
