/* Parked: 11 differing words (register allocation in the second chip lookup). */
#ifdef NONMATCHING
typedef struct { unsigned int lo : 4; unsigned int hi : 28; } ChipFlags;
typedef struct { int data[2]; ChipFlags flags[2]; char pad10[8]; } ChipRow;
typedef struct { char pad0[8]; int chips; char padC[0x3C]; int width; int height; } MapSize;
typedef struct SeamlessObj {
    int x;
    int y;
    int layer;
    int id;
    int arg;
    struct SeamlessObj *prev;
    struct SeamlessObj *next;
} SeamlessObj;
typedef struct { char pad[0x260]; long long flags; } LayoutWork;
typedef struct { char pad[0x144]; LayoutWork *work; } Layout;

extern MapSize D_0017A340;
extern int D_0017A3D0;
extern int D_0017A3D4;
#define ROW(c) (((ChipRow *)D_0017A340.chips)[c])
extern char rootPtn[];
extern int *iosMallocAlign(void *, int, int);
extern Layout *GetLayoutClass(int);
extern int func_0001EC38(void *);
extern void func_0001FA68(int, int, int);

static inline int get_chip_no(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int get_chip_no_alt(int x, int y)
{
    int c = -1;
    if (x >= 0 && x < D_0017A340.width && y >= 0 && y < D_0017A340.height)
        c = y * D_0017A340.width + x;
    return c;
}

static inline int get_chip_state(int layer, int group)
{
    if (group != -1)
        return ((ChipRow *)D_0017A340.chips)[group].flags[layer].lo;
    return 7;
}

void EntrySeamlessStageObject(int id, int arg, int x, int y, int layer, int hi)
{
    int chip = get_chip_no(x, y);
    {
    int other_tbl[2] = { 1, 0 };
    int *o = iosMallocAlign(rootPtn, 0x1C, 0x10);
    int *p;
    int other;
    int pid;

    o[3] = id;
    o[4] = arg;
    o[0] = x;
    o[1] = y;
    o[2] = layer;
    o[5] = 0;
    o[6] = D_0017A3D4;
    if (D_0017A3D4 != 0)
        ((int *)D_0017A3D4)[5] = (int)o;
    D_0017A3D0++;
    D_0017A3D4 = (int)o;
    ROW(chip).data[layer] = (int)o;
    ROW(chip).flags[layer].hi = hi;
    ROW(chip).flags[layer].lo = 3;
    other = other_tbl[layer];
    p = (int *)ROW(chip).data[other];
    if (p != 0)
        pid = p[3];
    else
        pid = 0;
    if (get_chip_state(other, chip) == 3) {
        func_0001EC38((void *)ROW(get_chip_no_alt(x, y)).data[other]);
        func_0001FA68(other, x, y);
        if (pid != 0)
            GetLayoutClass(pid)->work->flags |= 0x10;
    } else if (get_chip_state(other, chip) == 4) {
        if (pid != 0)
            GetLayoutClass(pid)->work->flags |= 0x10;
    } else {
        if (pid != 0)
            GetLayoutClass(pid)->work->flags &= ~0x10;
    }
    }
}
#endif
