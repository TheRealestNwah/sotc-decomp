typedef struct {
    int obj;
    int p0;
    int p1;
    int p2;
    int f10;
    int p3;
    int bgm;
    int f1C;
    int p4;
    int p7;
    float fp;
    int f2C;
    int flag;
    int p6;
    int p8;
    char pad3C[8];
    int f44;
    int p9;
    int f4C;
    int f50;
    int done;
} DemoSlot;

typedef struct Ptn Ptn;

extern int D_0017B8B8;
extern DemoSlot B_001A5A78[2];
extern Ptn rootPtn;
extern char RO_001816F8[];
extern void _gameFlagSet(int);
extern void *getNowExecEventScriptObj(void);
extern int _gcCreateChildScriptObj(void (*)(void *), void *, Ptn *, int, int, int, char *, void *);
extern void isysSetObjImmediateDeleteFunc(int, void (*)(int));
extern void func_00120978(void *);
extern void func_001212C8(int);

static inline DemoSlot *getSlot(int p0, int p1, int p2, int p3, int p4, int flag, int p6, int p7, float fp, int p8, int p9)
{
    DemoSlot *p;
    DemoSlot *q;
    int i;

    for (i = 0, p = B_001A5A78; i < 2; i++, p++) {
        if (p->obj == 0)
            continue;
        if (p1 != 0) {
            if (p->p1 == p1)
                return 0;
        } else if (p3 != 0) {
            if (p->p3 == p3)
                return 0;
        } else if (p8 != 0) {
            if (p->p8 != 0)
                return 0;
        }
    }
    for (i = 0; i < 2; i++) {
        q = &B_001A5A78[i];
        if (q->obj == 0 && q->done == 0) {
            q->p0 = p0;
            q->p1 = p1;
            q->p2 = p2;
            q->p3 = p3;
            q->p4 = p4;
            q->fp = fp;
            q->p6 = p6;
            q->p7 = p7;
            q->p8 = p8;
            q->p9 = p9;
            q->f10 = 0;
            q->bgm = 0;
            q->f1C = 0;
            q->f2C = 0;
            q->flag = flag;
            q->f44 = 0;
            q->done = 0;
            q->f4C = 0;
            if (flag)
                _gameFlagSet(flag);
            return q;
        }
    }
    return 0;
}

void createScrEventDemoManager(int p0, int p1, int p2, int p3, int p4, int flag, int p6, int p7, float fp, int p8, int p9)
{
    DemoSlot *slot;

    if (D_0017B8B8 > 0)
        return;
    slot = getSlot(p0, p1, p2, p3, p4, flag, p6, p7, fp, p8, p9);
    if (slot) {
        slot->obj = _gcCreateChildScriptObj(func_00120978, slot, &rootPtn, 0x4000, 0, 4,
                                            RO_001816F8, getNowExecEventScriptObj());
        isysSetObjImmediateDeleteFunc(slot->obj, func_001212C8);
    }
}
