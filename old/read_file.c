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

