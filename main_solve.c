#include "sudoku_solver.c"

int main() {
    Sudoku_board s = create_board("");
    switch (sudoku_solve(s)) {
        case INVALID:
            printf("INVALID");
            break;
        case COMPLETE:
            break;
        case MULTIPLE:
            printf("MULTIPLE");
            break;
        case UNSOLVABLE:
            printf("UNSOLVABLE");
            break;
        case INCOMPLETE:
            break;
    }
}