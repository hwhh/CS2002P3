#include "sudoku_solver.c"
#include <ntsid.h>
#include <time.h>

int complete_counter = 0;

///Print the output from the solve function
void print_status(Sudoku_board s) {
    switch (sudoku_solve(s)) {
        case MULTIPLE:
            printf("MULTIPLE");
            break;
        case COMPLETE:
            complete_counter++;
            print_sudoku_board(solved_board);
            break;
        case UNSOLVABLE:
            printf("UNSOLVABLE");
            break;
    }
}


int main() {
    //Begin the solve
    clock_t begin = clock();
    Sudoku_board s = create_board("");
    if (sudoku_solve_opt(s) != 1)
        print_status(s);
    else
        complete_counter++;
    clock_t end = clock();
    FILE *fp;
    //Append the execution time to a file if solution was valid
    fp = fopen("/Users/henryhargreaves/Documents/University/Year_2/CS2002/Practicals/Practical3-C2/recursive-speed.txt",
               "a+");
    if (fp != NULL) {
        double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        if (complete_counter >= 1)
            fprintf(fp, "%lf\n", time_spent);
    }
    fclose(fp);
    complete_counter = 0;
}
