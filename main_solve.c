#include "sudoku_solver.c"

void printstatus(Sudoku_board s) {
    switch (sudoku_solve(s)) {
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
