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
extern int D_0017A330[];
extern void sheetMgrMapDataUnloadOneBlock(int, int, int, int *);
extern void isysSleepSubThread(void);
extern void iosFree(void *);
extern void forceLoadSeamlessStage(void);

static inline void clearChip(int x, int y, int v)
{
    StageMap *m = &D_0017A340;

    if (((ChipRow *)m->chips)[x].data[y] != 0)
        iosFree((void *)((ChipRow *)m->chips)[x].data[y]);
    ((ChipRow *)m->chips)[x].data[y] = 0;
    ((ChipRow *)m->chips)[x].flags[y].lo = v;
    ((ChipRow *)m->chips)[x].flags[y].hi = 0;
}

static void T_0001F8E8(int *req)
{
    int x = req[1];
    int idx = req[0];
    int state = req[2];
    int reload = req[3];
    int status;
    int data = ((ChipRow *)D_0017A340.chips)[x].data[idx];

    sheetMgrMapDataUnloadOneBlock(D_0017A330[idx], x, data != 0 ? *(int *)(data + 0x10) : 0, &status);
    while (status != 0xDEAF && status != 0xDEB0)
        isysSleepSubThread();
    clearChip(x, idx, state);
    if (reload)
        forceLoadSeamlessStage();
    iosFree(req);
}
