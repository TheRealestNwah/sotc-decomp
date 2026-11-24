#ifdef NONMATCHING /* Parked: 8 diffs (load the group with the call's result first, then an empty volatile asm before last = 0). Remaining: the two group-address lui/addiu pairs use a0/v0 in the opposite order, and gcc schedules a1 = 0 before the movn and swaps the s0/s1 setup after the call. Tried: inverted ternary, an if-assigned temp, +r on node. */
typedef struct FogColMan {
    char pad0[0x90];
    int flags;
    char pad94[4];
    char g98[4];
    char g9C[4];
} FogColMan;

extern FogColMan B_00148A40;
extern char B_00148AD8[];
extern char B_00148ADC[];

extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern int func_00071AF0(unsigned char *, void *, void *, int, unsigned char *, void *);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

unsigned char *AddCollMan(void *a, void *b, void *c)
{
    unsigned char *w = 0;
    char pc;
    int found;
    int pass;

    found = 0;
    for (pass = 0; pass < 2; pass++) {
        void **node;
        unsigned char *last;

        if (found) {
            continue;
        }
        node = isysGroupForFirst(pass != 0 ? B_00148AD8 : B_00148ADC, 0);
        __asm__ volatile("");
        last = 0;
        for (; node != 0; node = isysGroupForNext(node, 0)) {
            last = *node;
            w = GetObjWork(last, 0x18);
            if (w == 0) {
                continue;
            }
            if (func_00071AF0(w, a, b, pass, last, c) != 0) {
                found = 1;
                break;
            }
        }
        if (last != 0) {
            isysGroupForExit(last, 0);
        }
    }
    B_00148A40.flags |= 1;
    return found ? w : 0;
}
#endif
