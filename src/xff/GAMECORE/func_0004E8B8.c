typedef union { float f; int i; } FU;
extern char gcGlobalVar[];
extern void isysRequestDeleteObj(void *);

typedef struct {
    int busy;
    char pad4[0x10 - 0x4];
} Slot;

typedef struct {
    char pad0[4];
    float f4;
    int i8;
    float fC;
    float f10;
    float f14;
    float f18;
    Slot slot[4];
    char pad5C[0x6C - 0x5C];
    void *obj;
} Work;

static void func_0004E8B8(int *a)
{
    Work *w = (Work *)a[3];
    int keep;
    int i;

    if (a[0] != 0) {
        a[0] = 0;
        a[1] = 0;
        a[2] = 0;
    }
    keep = w->i8;
    if (w->obj != 0) {
        isysRequestDeleteObj(w->obj);
        w->obj = 0;
    }
    for (i = 0; i < 4; i++) {
        if (w->slot[i].busy != 0)
            return;
    }
    w->i8 = keep;
    w->f4 = 0.0f;
    w->fC = 0.0f;
    w->f10 = 0.0f;
    w->f14 = 0.0f;
    w->f18 = ((FU *)(gcGlobalVar + 0x178))->f;
}
