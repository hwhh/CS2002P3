#include "sudoku_solver.c"

void printstatus(Sudoku_board s) {
    enum STATE x = sudoku_solve_opt(s);
    switch (x) {
        case MULTIPLE:
            printf("MULTIPLE");
            break;
        case COMPLETE:
            print_sudoku_board(solved_board);
            break;
        case UNSOLVABLE:
            printf("UNSOLVABLE");
            break;
    }
    counter = 0;
}

int main() {
    Sudoku_board s = create_board("");
    printstatus(s);
}
//DYLD_INSERT_LIBRARIES=/usr/lib/libgmalloc.dylib