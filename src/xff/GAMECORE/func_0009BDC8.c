extern char gcGlobalVar[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char *GetScriptCharacterClass(int);

#ifdef NONMATCHING /* 24 diffs: structure and loop match (sibling of func_0009BC48); the first-half flag/value variables take different registers and the loop constants are hoisted in another order */
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
    float r = *(float *)(*(char **)(c + 0x20) + 0x28);

    return distSq(c + 0x40, c + 0x4F0) <= r * r;
}

static int func_0009BDC8(char *c)
{
    int ok;
    int last;
    int *node;
    char *t;
    register int v0 __asm__("$2");
    int a0;
    int a1;
    register int v1 __asm__("$3");
    char *o;

    if (*(int *)(c + 0x2C) != 0) {
        v1 = near3(c);
        v0 = 0;
        if (v1 != 0) {
            ok = 1;
            node = isysGroupForFirst(gcGlobalVar + 0x2BC, 0);
            last = 0;
            if (node != 0) {
                last = *node;
                for (;;) {
                    o = *(char **)(GetScriptCharacterClass(last) + 0x1200);
                    if (o != 0 && *(int *)o == 4) {
                        int id = *(int *)(o + 8);

                        if (id == *(int *)(c + 8) && id != -1) {
                            int a3 = *(int *)(o + 0x500);

                            if (*(int *)(c + 0x540) != a3 && *(int *)(c + 0x560) != a3) {
                                int x = *(int *)(c + 0x1AC) ^ *(int *)(o + 0x1AC);
                                int y = *(int *)(c + 0x500) ^ a3;

                                if (x != 0)
                                    ok = 0;
                                if (y != 0)
                                    ok = 0;
                            }
                        }
                    }
                    node = isysGroupForNext(node, 0);
                    if (node == 0)
                        break;
                    last = *node;
                }
            }
            if (last != 0)
                isysGroupForExit(last, 0);
            return ok != 0;
        }
        return v0;
    }
    a1 = 0;
    if (*(int *)(c + 0x28) != 0 && (t = *(char **)(c + 0x30)) != 0) {
        v0 = 0 != 0;
        if (*(int *)(c + 0x1A0) != 4) {
            v0 = 0 != 0;
            if (*(int *)(c + 0x19C) != 4) {
                a0 = *(int *)(c + 0x500);
                a1 = 1;
                if (*(int *)(t + 0x580) != a0 && (a1 = 0, *(int *)(t + 0x500) != a0)) {
                    v0 = 0 != 0;
                    if (*(int *)(t + 0x540) != a0) {
                        a1 = *(int *)(t + 0x560) != a0;
                        goto b30;
                    }
                } else {
                    goto b30;
                }
            }
        }
    } else {
b30:
        v0 = a1 != 0;
    }
    return v0;
}
#endif
