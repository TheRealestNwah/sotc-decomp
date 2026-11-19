/* Map-data load request thread: checks that the n chips in a row (mode 0) or column (mode 1) starting at (x, y) are all in state 1, marks them state 2, starts sheetMgrMapDataLoad for them and waits for its status word, then frees the request. */
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
    ChipRow *chips;
    char padC[0x48 - 0xC];
    int width;
    int height;
} StageMap;

typedef struct {
    int z;
    int mode;
    int x;
    int y;
    int n;
} MapLoadReq;

extern StageMap D_0017A340;
extern int D_0017A330[];
extern int D_0017A338[];
extern int D_0017A34C;
extern void sheetMgrMapDataLoad(int, int, int, int, int, int *);
extern void isysSleepSubThread(void);
extern void iosFree(void *);

static inline int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int getChipState(int no, int z)
{
    int s;

    if (no != -1)
        s = D_0017A340.chips[no].flags[z].lo;
    else
        s = 7;
    return s;
}

static void func_0001F560(MapLoadReq *r)
{
    int z = r->z;
    int mode = r->mode;
    int x = r->x;
    int y = r->y;
    int n = r->n;
    int no = -1;
    int i;
    int c;
    int st[4];

    switch (mode) {
    case 0:
        no = getChipNo(x, y);
        for (i = 0; i < n; i++) {
            c = getChipNo(x + i, y);
            if (getChipState(c, z) == 1) {
                D_0017A340.chips[c].flags[z].lo = 2;
            } else {
                no = -1;
                break;
            }
        }
        break;
    case 1:
        no = x * D_0017A340.height + y;
        for (i = 0; i < n; i++) {
            c = getChipNo(x, y + i);
            if (getChipState(c, z) == 1) {
                D_0017A340.chips[c].flags[z].lo = 2;
            } else {
                no = -1;
                break;
            }
        }
        break;
    }
    if (no != -1) {
        sheetMgrMapDataLoad(D_0017A34C, D_0017A330[z], D_0017A338[mode], no, n, st);
        while ((unsigned)(st[0] - 0xDEAF) >= 2)
            isysSleepSubThread();
    }
    iosFree(r);
}
