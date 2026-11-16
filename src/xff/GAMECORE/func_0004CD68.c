typedef struct {
    int busy;
    int b;
    int c;
    void *work;
} Slot;

typedef struct {
    int kind;
    int f4;
    int i8;
    float fC;
    float f10;
    float f14;
    float f18;
    Slot slot[4];
    char pad5C[0x6C - 0x5C];
    void *obj;
    char pad70[0x78 - 0x70];
} WeakPointEffect;

extern WeakPointEffect B_0018A9B0[8];
typedef struct { char pad0[0x178]; float time; } GcGlobal;
extern GcGlobal gcGlobalVar;

static inline void resetIdle(WeakPointEffect *w, int i)
{
    int k;

    w->obj = 0;
    for (k = 0; k < 4; k++) {
        if (w->slot[k].busy != 0)
            return;
    }
    w->f4 = 0;
    w->i8 = i;
    w->fC = 0.0f;
    w->f10 = 0.0f;
    w->f14 = 0.0f;
    w->f18 = gcGlobalVar.time;
}

static void func_0004CD68(void)
{
    int i, j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            Slot *s = &B_0018A9B0[i].slot[j];

            if (s->busy != 0) {
                s->busy = 0;
                s->b = 0;
                s->c = 0;
            }
            resetIdle(&B_0018A9B0[i], i);
        }
    }
}
