#include "../sudoku_io.c"

//char *get_file_name() {
//    char *filename = malloc(20);
//    printf("Enter file name: ");
//    scanf("%s0", filename);
//    return filename;
//}
//
//
//
//Sudoku_board createBoard(char *filename) {
//    static Sudoku_board sudoku_board;
//    int x = 0;
//    FILE *file;
//    file =fopen(filename,"r");
//    if (!file)
//        fscanf (stdin, "%d", &x);
//    else
//        fscanf (file, "%d", &x);
//    sudoku_board.size = x;
//    sudoku_board.length = pow(x, 4);
//    sudoku_board.board = (int *) malloc((size_t) (sizeof(int) * sudoku_board.length));
//    sudoku_board.fixed_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
//    sudoku_board.possible_values = (bool *) malloc((size_t) (sizeof(bool) * sudoku_board.length));
//    int count = 0;
//    if (!file)
//        fscanf (stdin, "%d", &x);
//    else
//        fscanf (file, "%d", &x);
//    while (count < sudoku_board.length){
//        if(x == 0){
//            sudoku_board.board[count] = x;
//            sudoku_board.fixed_values[count] = false;
//            sudoku_board.possible_values[count] = true;
//        } else if (x > 0) {
//            sudoku_board.board[count] = x;
//            sudoku_board.fixed_values[count] = true;
//            sudoku_board.possible_values[count] = false;
//        }
//        count++;
//        if(count<sudoku_board.length)
//            if (!file)
//                fscanf (stdin, "%d", &x);
//            else
//                fscanf (file, "%d", &x);
//    }
//    return sudoku_board;
//}
//








































//
//enum STATE check_sudoku(Sudoku_board *sudoku_board) {
//    int status = 1;
//    int offset = 0;
//    int root = (int) pow(sudoku_board->size, 3);
//    double size = pow(sudoku_board->size, 2);
//    for (int i = 0; i < sudoku_board->length; i += size) {
//        int row[(int) size];
//        for (int j = 0; j < size; j++) {
//            row[j] = sudoku_board->board[i + j];
//        }
//        if (check_list(row, (int) size) == -1) {
//            printf("INVALID");
//            return INVALID;
//        } else if (check_list(row, (int) size) == 0)
//            status = 0;
//    }
//    for (int i = 0; i < size; i++) {
//        int count = 0;
//        int col[(int) size];
//        for (int j = 0; j < sudoku_board->length; j += size) {
//            col[count] = sudoku_board->board[i + j];
//            count++;
//        }
//        if (check_list(col, (int) size) == -1) {
//            printf("INVALID");
//            return INVALID;
//        } else if (check_list(col, (int) size) == 0)
//            status = 0;
//    }
//    for (int i = 0; i < sudoku_board->length; i += size) {
//        int box[(int) size];
//        for (int j = 0; j < size; j++) {
//            if (j % sudoku_board->size == 0 && j > 0) {
//                offset += (size - sudoku_board->size + 1);
//                box[j] = sudoku_board->board[offset - 1];
//            } else
//                box[j] = sudoku_board->board[offset++];
//        }
//        if (offset % root != 0)
//            offset -= (size * (sudoku_board->size - 1));
//        if (check_list(box, (int) size) == -1) {
//            printf("INVALID");
//            return INVALID;
//        } else if (check_list(box, (int) size) == 0)
//            status = 0;
//    }
//    if (status == 1) {
//        printf("COMPLETE");
//        return COMPLETE;
//    }else if (status == 0) {
//        printf("INCOMPLETE");
//        return INCOMPLETE;
//    }
//
//}
s