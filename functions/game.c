#include <stdio.h>
#include <stdlib.h>

#include "../header.h"

int detect_board(int (*board)[], int x, int y, int color) {
    int i, j;
    int lineCount[4];
    for (i = 0; i < 4; i++) lineCount[i] = 1;
    int count = 0;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            if (count <= 3) {
                lineCount[count] += stone_count(board, x, y, i, j, color, 0);
            } else {
                lineCount[7 - count] +=
                    stone_count(board, x, y, i, j, color, 0);
            }
            count++;
        }
    }
    for (i = 0; i < 4; i++) {
        switch (lineCount[i]) {
            case 3:
                return Loose;
            case 4:
                return Win;
        }
    }
    return 0;
}

int stone_count(int board[BoardSize][BoardSize], int x, int y, int vx, int vy,
                int color, int count) {
    int posX = x + vx;
    int posY = y + vy;
    if (posX < 0 || posY < 0 || posX > BoardSize - 1 || posY > BoardSize - 1 ||
        board[posX][posY] == 0 || board[posX][posY] != color) {
        return count;
    }
    count++;
    return stone_count(board, posX, posY, vx, vy, color, count);
}

void save_board(int board[BoardSize][BoardSize],
                int output[BoardSize][BoardSize]) {
    int i, j;
    for (i = 0; i < BoardSize; i++) {
        for (j = 0; j < BoardSize; j++) output[i][j] = board[i][j];
    }
}

void print_board(int board[BoardSize][BoardSize]) {
    int i, j;
    char *kanjiNums[9] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};
    printf(" ");
    for (i = 0; i < BoardSize; i++) printf(" %s", kanjiNums[i]);
    printf(" y\n");
    for (i = 0; i < BoardSize; i++) {
        printf("%d", i + 1);
        for (j = 0; j < BoardSize; j++) {
            switch (board[i][j]) {
                case 0:
                    printf(" ・");
                    break;
                case White:
                    printf(" ○ ");
                    break;
                case Black:
                    printf(" ● ");
                    break;
            }
        }
        printf("\n");
    }
    printf("x\n\n");
}