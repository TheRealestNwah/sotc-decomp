struct Cell {
    int attr;
    char c;
    char pad[3];
};

extern struct Cell D_0013ED90[][60];
extern struct Cell D_0013A160;

void ClearDisplay(void) {
    int y;
    int x;

    for (y = 0; y < 40; y++) {
        for (x = 0; x < 60; x++) {
            D_0013ED90[y][x] = D_0013A160;
        }
    }
}
