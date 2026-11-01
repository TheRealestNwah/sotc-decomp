typedef struct {
    float vec[4];
    float color[4];
    float brightness;
    float scale;
    float absBrightness;
    int p2C;
    long type;
    long p38;
} LightSlot;

typedef struct {
    LightSlot slots[4];
    char p100[0x20];
    int count;
} LightTable;

static void func_0007CDF8(LightTable *t)
{
    LightSlot key;
    int i;
    int j;

    for (i = 1; i < t->count; i++) {
        key = t->slots[i];
        for (j = i - 1; j >= 0 && t->slots[j].absBrightness < key.absBrightness; j--) {
            t->slots[j + 1] = t->slots[j];
        }
        t->slots[j + 1] = key;
    }
}

typedef struct {
    char p0[0x110];
    int flags;
    char p114[0xC];
    int count;
} GlobalLightWork;

extern char *GetLightColMan(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);

void GlobalLightConsistencyWorkGrp(void *arg)
{
    char *man;
    void **node;
    unsigned char *last = 0;
    int changed = 0;

    man = GetLightColMan(arg);
    for (node = isysGroupForFirst(man + 0x518, 0); node != 0; node = isysGroupForNext(node, 0)) {
        GlobalLightWork *w;
        int moved;

        last = *node;
        w = (GlobalLightWork *)(last[8] == 0x19 ? last + 0x20 : 0);
        moved = 0;
        if ((w->flags & 0x600) == 0x600 && (w->flags & 0x3C) != 0) {
            isysAddGroupWithLinkParam(last, man + 0x51C, 0, 0);
            _isysDeleteGroup(last, man + 0x518, 0);
            moved = 1;
        }
        if (moved) {
            changed = 1;
            if (!(w->flags & 0x20000)) {
                w->flags |= 0x10000;
                if (w->count >= 2) {
                    func_0007CDF8((LightTable *)w);
                }
            } else if (w->count >= 2) {
                func_0007CDF8((LightTable *)w);
            }
        }
    }
    if (last != 0) {
        isysGroupForExit(last, 0);
    }
    if (changed) {
        *(int *)(man + 0x52C) |= 1;
    }
}
