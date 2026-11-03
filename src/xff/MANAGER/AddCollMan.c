#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef struct FogColMan {
    char pad0[0x90];
    int flags;
} FogColMan;

extern FogColMan B_00148A40;
extern char B_00148AD8[];
extern char B_00148ADC[];

extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern int func_00071AF0(unsigned char *, int, int, int, int, int);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

unsigned char *AddCollMan(int a, int b, int c)
{
    unsigned char *w = 0;
    int found = 0;
    int pass;

    for (pass = 0; pass < 2; pass++) {
        void **node;
        unsigned char *last;

        if (found) {
            continue;
        }
        last = 0;
        for (node = isysGroupForFirst(pass ? B_00148AD8 : B_00148ADC, 0); node != 0;
             node = isysGroupForNext(node, 0)) {
            last = *node;
            w = GetObjWork(last, 0x18);
            if (w == 0) {
                continue;
            }
            if (func_00071AF0(w, a, b, pass, (int)last, c) != 0) {
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
