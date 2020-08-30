#include <stdio.h>
#include <stdlib.h>
#define MaxBoardSize 0
#define Black 1
#define White -1
#define Win 1
#define Loose -1
char *KanjiNums[10] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};
int detect_board(int (*board)[], int x, int y, int color);
int stone_count(int (*board)[], int x, int y, int vx, int vy, int color,
                int count);
void print_board(int (*board)[]);
int BoardSize = 9;
int main() {
    int i, j;
    int board[BoardSize][BoardSize];
    for (i = 0; i < BoardSize; i++) {
        for (j = 0; j < BoardSize; j++) board[i][j] = 0;
    }
    print_board(board);
    int turnCount = 0;
    int currentColor = Black;
    while (turnCount != BoardSize * BoardSize) {
        int x, y;
        printf("Input position(x y)\n");
        scanf("%d %d", &x, &y);
        if (board[x - 1][y - 1] != 0 || x < 1 || y < 1 || x > BoardSize ||
            y > BoardSize) {
            printf("そこにはコマを置くことができません\n");
            continue;
        }
        board[x - 1][y - 1] = currentColor;
        print_board(board);
        int result = detect_board(board, x - 1, y - 1, currentColor);
        char *color = currentColor == Black ? "Black" : "White";
        if (result == Win) {
            printf("%s Win!!", color);
        } else if (result == Loose) {
            printf("%s Loose!!", color);
        }
        turnCount++;
        currentColor *= -1;
    }
    printf("Draw\n");
    return 0;
}
int detect_board(int (*board)[], int x, int y, int color) {
    int i, j;
    int lineCount[4];
    for (i = 0; i < 4; i++) lineCount[i] = 1;
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
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
void print_board(int board[BoardSize][BoardSize]) {
    int i, j;
    printf(" ");
    for (i = 0; i < BoardSize; i++) printf("%s", KanjiNums[i]);
    printf(" y\n");
    for (i = 0; i < BoardSize; i++) {
        printf("%d", i + 1);
        for (j = 0; j < BoardSize; j++) {
            switch (board[i][j]) {
                case -1:
                    printf("● ");
                    break;
                case 1:
                    printf("○ ");
                    break;
                case 0:
                    printf("・");
                    break;
            }
        }
        printf("\n");
    }
    printf("x\n");
}