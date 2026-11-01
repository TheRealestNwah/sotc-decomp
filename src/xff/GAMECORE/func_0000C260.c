typedef struct {
    unsigned long t;
    char pad8[0x148 - 0x8];
    unsigned long d148;
    char pad150[0x158 - 0x150];
    unsigned long d158;
    unsigned long d160;
    char pad168[0x1A0 - 0x168];
    float rate;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;

static void func_0000C260(void)
{
    GcGlobalVar *g = &gcGlobalVar;
    unsigned long r;
    float f = g->rate * 256.0f;
    g->d160 = g->d148 + g->d160;
    r = ((g->t << 8) >> 8) * (long)(int)f;
    g->d148 = 0;
    g->d158 = r >> 8;
}
