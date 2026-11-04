typedef struct Grp {
    int state;
    char pad4[0x1C];
    struct Grp *next;
} Grp;

typedef struct {
    char pad0[0x10];
    Grp *grp;
    char pad14[4];
} ChipRow;

typedef struct {
    char pad0[8];
    ChipRow *chips;
    char padC[0x3C];
    int width;
    int height;
} StageMap;

extern StageMap D_0017A340;
extern Grp *D_0017A310;
extern void iosFree(void *);

static inline int getChipNo(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int getGrpState(int no)
{
    Grp *g = D_0017A340.chips[no].grp;

    return g != 0 ? g->state : 0;
}

static inline void DeleteLoadAreaGroupData(Grp *g)
{
    Grp **h = &D_0017A310;
    Grp *p = *h;

    if (p == g) {
        *h = g->next;
        iosFree(g);
    } else {
        while (p != 0) {
            if (p->next == g) {
                p->next = g->next;
                iosFree(g);
                break;
            }
            p = p->next;
        }
    }
}

void DeleteNoUseLoadAreaGroupData(Grp *g)
{
    int x;
    int y;

    for (y = 0; y < D_0017A340.height; y++) {
        for (x = 0; x < D_0017A340.width; x++) {
            if (getGrpState(getChipNo(x, y)) == 5 && D_0017A340.chips[getChipNo(x, y)].grp == g) {
                return;
            }
        }
    }
    DeleteLoadAreaGroupData(g);
}
