typedef struct {
    char pad0[0x58];
    int ready;
} BossCore;

typedef struct {
    char pad0[4];
    BossCore *core;
    char pad8[0x384 - 8];
    int state;
} BossWork;

extern void scrRunM(int);
extern int func_0004A150(BossWork *);

static void func_0004B128(BossWork *w)
{
    BossCore *c = w->core;

    while (c->ready == 0)
        scrRunM(1);
    for (;;) {
        w->state = func_0004A150(w);
        scrRunM(1);
    }
}
