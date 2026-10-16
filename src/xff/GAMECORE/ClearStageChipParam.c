typedef struct {
    unsigned int lo : 4;
    unsigned int hi : 28;
} ChipFlags;

typedef struct {
    int data[2];
    ChipFlags flags[2];
    char pad10[8];
} ChipRow;

typedef struct {
    char pad0[8];
    int chips;
} StageMap;

extern StageMap D_0017A340;
extern void iosFree(int);

void ClearStageChipParam(int x, int y, int v)
{
    StageMap *m = &D_0017A340;

    if (((ChipRow *)m->chips)[x].data[y] != 0)
        iosFree(((ChipRow *)m->chips)[x].data[y]);
    ((ChipRow *)m->chips)[x].data[y] = 0;
    ((ChipRow *)m->chips)[x].flags[y].lo = v;
    ((ChipRow *)m->chips)[x].flags[y].hi = 0;
}
