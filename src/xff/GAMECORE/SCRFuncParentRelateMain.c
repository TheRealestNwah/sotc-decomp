extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *getSCRDataCtrlWork(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsColStatus(void *, long, long);
extern void setSCRGazeStatus(void *, void *, void *);

typedef struct {
    int pad0;
    int pad4;
    long m;
    long v;
    char gaze[4];
    float time;
} RelEntry;

typedef struct {
    float timer;
    RelEntry *cur;
} RelState;

static inline int *dldObj(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
}

static inline int dldCount(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
}

void SCRFuncParentRelateMain(void *obj, int a1, int a2, int a3, int a4, int *h)
{
    char *w = getSCRDataCtrlWork(obj);
    RelState *st = (RelState *)(w + 0x40D8);
    RelEntry *e;
    RelEntry *found;
    int count;
    int i;

    st->timer += *(float *)(gcGlobalVar + 0x190);
    if (st->cur != 0 && !(st->cur->time <= st->timer))
        return;
    e = (RelEntry *)dldObj(h);
    found = 0;
    count = dldCount(h);
    for (i = 0; i < count; i++, e++) {
        if (e->m == -1 && e->v == -1) {
            found = e;
            break;
        }
        if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(w + 0x4078)), e->m, e->v)) {
            found = e;
            break;
        }
    }
    if (found != 0 && found != st->cur) {
        st->cur = found;
        st->timer = 0;
        setSCRGazeStatus(obj, w, found->gaze);
    }
}
