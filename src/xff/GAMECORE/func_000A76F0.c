/* 15 diffs, same size (134 words). Static (alabel) thread-binding update for a script character: types 6/8 bind to the current sub thread; otherwise it searches the character group (gcGlobalVar+0x2BC) for a matching live object (type 1, same +8/+4, state != 0x24, +0x26C < 0x12), then either activates (0x22, calls func_000A7630 when it was inactive) or drops (0x23, frees +0x360). Remaining: register numbering only (Original keeps self in s7, prev in s4, the 1 and 0x24 constants in s6/s5; ours s6/s7/s5/s4). `register ... asm` pinning adds extra moves; permuter queued. */
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern char *GetScriptCharacterClass(int);
extern void iosFree(int);
extern void func_000A7630(char *);


#ifdef NONMATCHING
void func_000A76F0(char *a0)
{
    int type;
    int self = isysGetThisSubThread();
    int prev = *(int *)(a0 + 0x38);
    int target;
    char *cls;

    type = *(int *)a0;
    if (type == 8 || type == 6) {
        *(int *)(a0 + 0x3C) = 0x22;
        *(int *)(a0 + 0x38) = 1;
        *(int *)(a0 + 0x28) = self;
        *(char **)(a0 + 0x2C) = a0;
        return;
    }
    target = isysGetThisSubThread();
    if (*(int *)(a0 + 8) != -1) {
        int found = 0;
        int *g;
        for (g = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); g != 0; g = isysGroupForNext(g, 0)) {
            char *o;
            found = *g;
            o = *(char **)(GetScriptCharacterClass(found) + 0x1200);
            if (o != 0 && *(int *)o == 1 && *(int *)(o + 8) == *(int *)(a0 + 8) && *(int *)(o + 4) == *(int *)(a0 + 4)
                && *(int *)(o + 0x3C) != 0x24 && *(int *)(o + 0x26C) < 0x12) {
                target = found;
                break;
            }
        }
        if (found != 0) {
            isysGroupForExit(found, 0);
        }
    }
    *(int *)(a0 + 0x28) = target;
    cls = *(char **)(GetScriptCharacterClass(target) + 0x1200);
    *(char **)(a0 + 0x2C) = cls;
    if (*(int *)(a0 + 0x26C) < 0x12) {
        if (*(int *)(a0 + 0x3C) == 0x24) {
            *(int *)(a0 + 0x38) = 0;
        } else if (*(int *)(a0 + 0x28) == self || *(int *)(a0 + 0x28) == 0 || cls == 0) {
            *(int *)(a0 + 0x3C) = 0x22;
            *(int *)(a0 + 0x38) = 1;
            *(int *)(a0 + 0x584) = 1;
            if (prev == 0) {
                func_000A7630(a0);
            }
        } else {
            goto drop;
        }
    } else {
drop:
        *(int *)(a0 + 0x38) = 0;
        *(int *)(a0 + 0x3C) = 0x23;
        if (prev != 0 && *(int *)(a0 + 0x374) >= 0) {
            int h = *(int *)(a0 + 0x360);
            if (h != 0) {
                iosFree(h);
                *(int *)(a0 + 0x360) = 0;
            }
        }
    }
}
#endif
