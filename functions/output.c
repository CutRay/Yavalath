#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../header.h"

void output_log(int (*boardLog)[BoardSize][BoardSize], int boardCount) {
    struct tm now;
    {
        const time_t t = time(NULL);
        localtime_r(&t, &now);
    }
    char fname[32] = {0};
    strftime(fname, sizeof(fname), "./logs/%Y%m%d%H%M.log", &now);
    FILE *fp;
    fp = fopen(fname, "w");
    int i;
    for (i = 0; i < boardCount; i++) {
        int j, k;
        char *kanjiNums[9] = {"一", "二", "三", "四", "五",
                              "六", "七", "八", "九"};
        fprintf(fp, " ");
        for (j = 0; j < BoardSize; j++) fprintf(fp, " %s", kanjiNums[j]);
        fprintf(fp, " y\n");
        for (j = 0; j < BoardSize; j++) {
            fprintf(fp, "%d", j + 1);
            for (k = 0; k < BoardSize; k++) {
                switch (boardLog[i][j][k]) {
                    case 0:
                        fprintf(fp, " ・");
                        break;
                    case White:
                        fprintf(fp, " ○ ");
                        break;
                    case Black:
                        fprintf(fp, " ● ");
                        break;
                }
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "x\n\n");
    }
    fclose(fp);
}