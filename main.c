#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main() {
    int i, j;
    int board[BoardSize][BoardSize];
    int boardLog[BoardSize * BoardSize + 1][BoardSize][BoardSize];
    for (i = 0; i < BoardSize; i++) {
        for (j = 0; j < BoardSize; j++) board[i][j] = 0;
    }
    save_board(board, boardLog[0]);
    int turnCount = 0;
    int currentColor = -1;

    while (1) {
        int x, y, result;
        print_board(board);
        if (turnCount == BoardSize * BoardSize) {
            printf("引き分け!!\n");
            break;
        }
        char *color = currentColor == 1 ? "黒" : "白";
        if (result == Win) {
            printf("%s 勝利!!\n", color);
            break;
        } else if (result == Loose) {
            printf("%s 敗北!!\n", color);
            break;
        }

        printf("石を置く場所を入力(x y)\n0 0と入力すれば, 一手戻ります\n");
        int num = scanf("%d %d", &x, &y);
        if (x == 0 && y == 0) {
            if (turnCount - 1 < 0) {
                save_board(boardLog[0], board);
            } else
                save_board(boardLog[turnCount - 1], board);
            currentColor *= -1;
            turnCount--;
            continue;
        } else if (board[x - 1][y - 1] != 0 || x < 1 || y < 1 ||
                   x > BoardSize || y > BoardSize) {
            printf("そこには石を置くことができません\n");
            continue;
        }

        currentColor *= -1;
        turnCount++;
        board[x - 1][y - 1] = currentColor;
        save_board(board, boardLog[turnCount]);
        result = detect_board(board, x - 1, y - 1, currentColor);
    }
    printf("ログを保存しますか?(はい:1 いいえ;0)\n");
    int isSaved = 0;
    int num = scanf("%d", &isSaved);
    if (isSaved) output_log(boardLog, turnCount + 1);
    return 0;
}
