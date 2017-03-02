#include <ntsid.h>
#include <time.h>
#include "dancing_links_solver.c"

int main() {
    clock_t start = clock(), diff;
    create_board("");

    solve(0);
    if (Finished != 1)
        printf("UNSOLVABLE");


    diff = clock() - start;
    int msec = (int) (diff * 1000 / CLOCKS_PER_SEC);
    //printf("\nTime taken %d seconds %d milliseconds", msec/1000, msec%1000);

}


