/* ~111 diffs, same length (170 words), frame 0x90 vs 0x70. Builds the visible-leaf list for the fallen-leaf/arrow effect (called from fallenLeafMain / arrowWaterMain): resolves the layout object for obj, its table of 0x14-byte entries (count from the module header, undef-safe: the dldCount helper matches the Original branch shape), and for each entry whose script object (SCRGetFirstObj of gcGlobalVar+0x2A8[e[4]]) and node exist and while fewer than 7 are stored, reads the node quaternion/position (GetMotionNodeQuaternionPos) and keeps it (position quad + e[8], e[0xC] floats, stride 0x20 from work+0x10) unless e[0x10] == 0 and the node y is below scale[0x24] + 0.05; finally stores the count in work[0]. The Original keeps work in $fp and scale in $s7 with the gcGlobalVar hi in $s6 and the DldSysUndefSymbol hi in $s5 (no spill); ours runs out of saved registers and spills work to $sp+0x20, growing the frame. */
typedef int s128 __attribute__((mode(TI)));
extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, void *, int);

static inline int dldCount(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(int *)(t + 0xC) : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

#ifdef NONMATCHING
static void func_00053058(char *obj, char *work, char *scale)
{
    char *p;
    char *list;
    int count = 0;
    int n = 0;
    char *e;
    char *out;
    int i;

    p = dldResolve((unsigned int *)(*(char **)(obj + 0x1C) + 0x1C));
    list = dldResolve((unsigned int *)(p + 0xC));
    if (list != 0)
        count = dldCount((unsigned int *)(p + 0xC));
    if (count > 0) {
        out = work + 0x10 + n * 0x20;
        e = list;
        for (i = count; i != 0; i--, e += 0x14) {
            char *node = dldResolve((unsigned int *)e);
            void *first = SCRGetFirstObj(gcGlobalVar + 0x2A8 + *(int *)(e + 4) * 4);
            s128 pos[2];

            if (first != 0 && node != 0 && n < 7) {
                GetMotionNodeQuaternionPos(&pos[1], &pos[0], first, *(void **)(node + 8), 1);
                if (*(int *)(e + 0x10) == 0 && !(((float *)pos)[1] <= *(float *)(scale + 0x24) + 0.05f))
                    continue;
                n++;
                *(s128 *)out = pos[0];
                *(float *)(out + 0x10) = *(float *)(e + 8);
                *(float *)(out + 0x14) = *(float *)(e + 0xC);
                out += 0x20;
            }
        }
    }
    *(int *)work = n;
}
#endif
