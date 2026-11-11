extern char gcGlobalVar[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char *GetScriptCharacterClass(int);

#ifdef NONMATCHING /* 16 diffs: loop body and control flow match; the shared `v0 = a1 != 0` exit is built through a temporary ($a2) instead of directly in $v0 */
static int func_0009BC48(char *c)
{
    int ok;
    int last;
    int *node;
    char *t;
    int v0;
    int a0;
    int a1;
    char *o;

    if (*(int *)(c + 0x2C) != 0) {
        if (*(float *)(c + 0x1C4) < *(float *)(c + 0x1C0))
            return 0;
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
                        int x = *(int *)(c + 0x1AC) ^ *(int *)(o + 0x1AC);
                        int y = *(int *)(c + 0x500) ^ a3;
                    if (x != 0)
                        ok = 0;
                    if (y != 0)
                        ok = 0;
                    }
                }
            }
        }
        if (last != 0)
            isysGroupForExit(last, 0);
        return ok != 0;

    }
        a1 = 0;
    if (*(int *)(c + 0x28) != 0 && (t = *(char **)(c + 0x30)) != 0) {
        v0 = 0;
        if (*(int *)(c + 0x1A0) != 4) {
            v0 = 0;
            if (*(int *)(c + 0x19C) != 4) {
                a0 = *(int *)(c + 0x500);
                a1 = 1;
                if (*(int *)(t + 0x580) != a0 && (a1 = 0, *(int *)(t + 0x500) != a0)) {
                    v0 = 0;
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
