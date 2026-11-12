extern char gcGlobalVar[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char *GetScriptCharacterClass(int);

#ifdef NONMATCHING /* 41 diffs: second half now matches except layout; near-check result is booleanized (sltiu) where the original branches on it (bnel + shared exits) */
static inline float distSq(char *a, char *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline int near3(char *c)
{
    float r = *(float *)(*(char **)(c + 0x20) + 0x30);

    return distSq(c + 0x40, c + 0x4F0) <= r * r;
}

static int func_0009BFA0(char *c)
{
    int ok;
    int last;
    int *node;
    register char *t __asm__("$5");
    int a0;
    register int a1 __asm__("$4");
    register int x __asm__("$2");
    int nr;
    char *o;

    if (*(int *)(c + 0x2C) != 0) {
        ok = 1;
        last = 0;
        for (node = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); node != 0; node = isysGroupForNext(node, 0)) {
            last = *node;
            o = *(char **)(GetScriptCharacterClass(last) + 0x1200);
            if (o != 0 && *(int *)o == 4) {
                int id = *(int *)(o + 8);

                if (id == *(int *)(c + 8) && id != -1) {
                    int a3 = *(int *)(o + 0x500);

                    if (*(int *)(c + 0x540) != a3 && *(int *)(c + 0x560) != a3) {
                        int xx = *(int *)(c + 0x1AC) ^ *(int *)(o + 0x1AC);
                        int y = *(int *)(c + 0x500) ^ a3;

                        if (xx != 0)
                            ok = 0;
                        if (y != 0)
                            ok = 0;
                    }
                }
            }
        }
        if (last != 0)
            isysGroupForExit(last, 0);
        if (ok == 0)
            return 0;
        x = *(int *)(c + 0x270);
        if (x == 0)
            return 0;
        x = near3(c);
        nr = x;
        if (nr != 0)
            return 0;
        return 1;
    }
    a1 = 0;
    if (*(int *)(c + 0x28) != 0 && (t = *(char **)(c + 0x30)) != 0) {
        if (*(int *)(c + 0x1A0) != 4 && *(int *)(c + 0x19C) != 4) {
            a0 = *(int *)(c + 0x500);
            a1 = 1;
            if (*(int *)(t + 0x580) != a0) {
                a1 = 0;
                if (*(int *)(t + 0x500) != a0 && *(int *)(t + 0x540) != a0) {
                    x = *(int *)(t + 0x560) ^ a0;
                    a1 = x != 0;
                }
            }
        }
    }
    __asm__("" : "+r"(a1));
    if (a1 != 0)
        return 1;
    return 0;
}
#endif
