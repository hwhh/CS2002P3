#include <ntsid.h>
#include <time.h>
#include "dancing_links_solver.c"


int main() {
    create_board_dxl("");
    clock_t begin = clock();
    enum STATE x = solve(0);
    if (x == UNSOLVABLE)
        printf("UNSOLVABLE");
    clock_t end = clock();
    FILE *fp;
    fp = fopen(
            "/Users/henryhargreaves/Documents/University/Year_2/CS2002/Practicals/Practical3-C2/dancing-links-speed.txt",
            "a+");
    if (fp != NULL) {
        double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        if (Finished >= 1)
            fprintf(fp, "%lf\n", time_spent);
    }
    fclose(fp);


}


