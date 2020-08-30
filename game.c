#include <stdio.h>
#include <stdlib.h>
#define MaxBoardSize 0
#define Black 1
#define White -1
#define Win 1
#define Loose -1
#define BoardSize 9
char *KanjiNums[10] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};
int detect_board(int (*board)[], int x, int y, int color);
int stone_count(int (*board)[], int x, int y, int vx, int vy, int color,
                int count);
void save_board(int (*board)[], int (*output)[]);
void print_board(int (*board)[]);
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
        if (result == Win) {
            printf("%c 勝利!!\n", currentColor * -1);
            break;
        } else if (result == Loose) {
            printf("%c 敗北!!\n", currentColor * -1);
            break;
        }

        printf("石を置く場所を入力(x y)\n0 0と入力すれば, 一手戻ります\n");
        scanf("%d %d", &x, &y);
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
    return 0;
}

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
    printf(" ");
    for (i = 0; i < BoardSize; i++) printf(" %s", KanjiNums[i]);
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