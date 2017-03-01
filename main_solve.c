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
    //Sudoku_board s = create_board("/Users/henryhargreaves/Documents/University/Year_2/CS2002/Practicals/Practical3-C2/stacscheck/2_sudoku_solver_tests/check_empty.in");
    //Sudoku_board s1 = create_board("/Users/henryhargreaves/Documents/University/Year_2/CS2002/Practicals/Practical3-C2/stacscheck/2_sudoku_solver_tests/size-3.in");
    printstatus(s);
    //printf("s1 \n");
    //printstatus(s1);
}
