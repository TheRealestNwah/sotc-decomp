typedef struct {
    int active;
    int flags;
    int x8;
    float tx;
    float ty;
    float dx;
    float dy;
    char pad1C[0x60 - 0x1C];
    float cy;
    float cx;
    char pad68[0xC4 - 0x68];
} Ramp;
extern int DIntr(void);
extern void EIntr(void);
extern int Sg2CtrlGetTickMode(void);

static void func_0002E728(char *base, int i, int time, int cb, float x, float y)
{
    Ramp *r = (Ramp *)(base + i * 0xC4 + 0x14);
    int intr = DIntr();
    float cx = r->cx;
    float cy = r->cy;
    float t = 1000.0f / Sg2CtrlGetTickMode();
    t = time / t;
    if (t < 1.0f)
        t = 1.0f;
    if (cb) {
        r->flags |= 4;
        r->x8 = cb;
    }
    if ((int)x != -1000.0f) {
        r->flags |= 1;
        r->tx = x;
        r->dx = (x - cx) / t;
    }
    if ((int)y != -1000.0f) {
        r->flags |= 2;
        r->ty = y;
        r->dy = (y - cy) / t;
    }
    if (r->flags)
        r->active = 1;
    if (intr)
        EIntr();
}
