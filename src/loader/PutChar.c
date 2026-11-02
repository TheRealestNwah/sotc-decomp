struct Cell {
    int attr;
    char c;
    char pad[3];
};

extern struct Cell D_0013ED90[][60];
extern int D_0013A16C;
extern int D_0013A170;

void PutChar(int attr, char c) {
    struct Cell *cell = &D_0013ED90[D_0013A170][D_0013A16C];
    cell->attr = attr;
    cell->c = c;
}
