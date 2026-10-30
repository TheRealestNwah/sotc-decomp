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
    char padC[0x3C];
    int width;
    int height;
} StageMap;

extern StageMap D_0017A340;

static inline int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int getChipState(int no, int i)
{
    int v;

    if (no != -1)
        v = D_0017A340.chips[no].flags[i].lo;
    else
        v = 7;
    return v;
}

int SeamlessStageLoadComplete(void)
{
    StageMap *m = &D_0017A340;
    int x;
    int y;
    int i;
    int no;

    if (m->chips == 0)
        return 1;
    for (y = 0; y < m->height; y++) {
        for (x = 0; x < D_0017A340.width; x++) {
            no = getChipNo(x, y);
            for (i = 0; i < 2; i++) {
                if (getChipState(no, i) == 1 || getChipState(no, i) == 2 || getChipState(no, i) == 4)
                    return 0;
            }
        }
    }
    return 1;
}
