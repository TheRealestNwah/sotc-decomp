#ifdef NONMATCHING /* 71 diffs: callee-saved register order differs, and the tail is split off as func_000CDC00 */
typedef struct McStep {
    int arg;
    int (*fn)(void *);
} McStep;

typedef struct McReq {
    char name[0x20];
    int port;
    int slot;
    int unk28;
    int size;
    int unk30;
} McReq;

extern McStep *B_0014DB3C;
extern McReq B_0014CAD0;
extern float D_00137708;
extern char RO_0011AA90[];
extern char RO_0011AAB8[];
extern int iosMcChDir(int, int, char *);
extern char *strcpy(char *, const char *);

typedef struct McWork {
    int unk0;
    int port;
    int slot;
    int unkC;
    int unk10;
    int count;
    char pad18[0x14];
    int result;
} McWork;

static void func_000CDAA8(McWork *w)
{
    McStep *s = B_0014DB3C;
    int port = w->port;
    int slot = w->slot;
    int n = 0;
    float step;
    int (*fn)(void *);

    while (s->fn != 0) {
        s++;
        n++;
    }
    step = 0.8f / n;
    if ((w->result = iosMcChDir(port, slot, RO_0011AA90)) != 0)
        return;
    D_00137708 = 0.1f;
    B_0014CAD0.port = port;
    B_0014CAD0.slot = slot;
    strcpy(B_0014CAD0.name, RO_0011AAB8);
    B_0014CAD0.unk28 = 0x5400;
    B_0014CAD0.unk30 = 0;
    B_0014CAD0.size = w->count * 0x5800 + 0xC00;
    for (s = B_0014DB3C; (fn = s->fn) != 0; s++) {
        if ((w->result = fn(&B_0014CAD0)) != 0)
            return;
        D_00137708 += step;
    }
    w->result = 0;
    D_00137708 = 1.0f;
}
#endif
