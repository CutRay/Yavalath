#define Black 1
#define White -1
#define Win 1
#define Loose -1
#define BoardSize 9

int detect_board(int (*board)[BoardSize], int x, int y, int color);
int stone_count(int (*board)[BoardSize], int x, int y, int vx, int vy,
                int color, int count);
void save_board(int (*board)[BoardSize], int (*output)[BoardSize]);
void print_board(int (*board)[BoardSize]);
void output_log(int (*boardLog)[BoardSize][BoardSize], int boardCount);