struct Cell {
    int attr;
    char c;
    char pad[3];
};

extern struct Cell D_0013ED90[][60];
extern struct Cell D_0013A160;

void ScrollDisplay(void) {
    int y;
    int x;

    for (y = 1; y < 40; y++) {
        for (x = 0; x < 60; x++) {
            D_0013ED90[y - 1][x] = D_0013ED90[y][x];
        }
    }
    for (x = 0; x < 60; x++) {
        D_0013ED90[39][x] = D_0013A160;
    }
}
