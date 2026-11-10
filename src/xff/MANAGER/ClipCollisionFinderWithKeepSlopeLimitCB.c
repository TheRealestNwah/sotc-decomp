/* ~127 diffs, 3 words longer (151 vs 148), frame 0xF0 vs 0xE0. Callback variant of ClipCollisionFinderWithKeep4DSlopeLimit (same keep-list loop with func_000A2B30 and finder loop with func_000A0DE8 / func_000A1580, but with the non-4D start pointer kept in memory at sp+0x70 and a per-entry filter at sp+0x74 that must accept the entry (filter(cur, user)); after recording a hit it also calls callback(cur, ret, user) when set). Args: out, start, end, finder, keep, filter, callback, user, f12. The Original has ret in $fp, n in $s1 (keep loop) / $s2 (finder loop), reuses $s4 (dead keep) as the constant 1 in the finder loop and keeps $s5 = user; ours spills ret ($sp+0x80) because the registers are not reused. */
typedef int s128 __attribute__((mode(TI)));

extern int func_000A2B30(void *, void *, void *, void *, void *, float, void *);
extern int func_000A0DE8(void *, void *, void *, void *, void *, float);
extern int func_000A1580(void *, void *, void *, void *, void *, float);

#ifdef NONMATCHING
int ClipCollisionFinderWithKeepSlopeLimitCB(char *out, s128 *start, s128 *end, int *finder, int *keep,
                                            int (*filter)(void *, void *), void (*callback)(void *, int, void *),
                                            void *user, float f12)
{
    struct { s128 e; s128 q10; s128 q20; s128 pad30; s128 pad40; s128 q50; s128 q60; s128 *start; int (*filter)(void *, void *); } L;
    int ret = 0;
    int n;
    char *cur;
    int r;
    int ok;

    L.start = start;
    L.filter = filter;
    *(s128 *)out = *end;
    if (keep != 0 && (n = keep[0x20 / 4]) != 0) {
        cur = (char *)keep[0x24 / 4];
        n--;
        L.e = *L.start;
        if (n != -1) {
            do {
                if (L.filter(cur, user) != 0) {
                    r = func_000A2B30(&L.q20, &L.q10, &L.e, out, cur, f12, keep);
                    if (r != 0) {
                        if (r - 5 < 2U)
                            L.e = L.q60;
                        ret = r;
                        *(s128 *)out = L.q60;
                        *(s128 *)(out + 0x10) = L.q10;
                        *(int *)(out + 0x20) = *(int *)cur;
                        *(int *)(out + 0x24) = *(int *)(cur + 4);
                        if (callback != 0)
                            callback(cur, ret, user);
                    }
                }
                cur += 0x14;
            } while (--n != -1);
        }
    }
    n = finder[0] < finder[1] ? finder[0] : finder[1];
    if (n != 0) {
        n--;
        if (n != -1) {
            cur = (char *)finder[3];
            do {
                if (*(int *)cur != 0 && L.filter(cur, user) != 0) {
                    L.q60 = *(s128 *)out;
                    ok = 0;
                    r = func_000A0DE8(&L.q10, &L.e, L.start, &L.q60, cur, f12);
                    if (r == 1) {
                        L.q60 = L.q50;
                        ok = 1;
                    }
                    if (r == 0) {
                        if (func_000A1580(&L.q10, &L.e, L.start, &L.q60, cur, f12) != 0)
                            ok = 1;
                    }
                    if (ok != 0) {
                        ret = ok;
                        *(s128 *)out = L.q50;
                        *(s128 *)(out + 0x10) = L.e;
                        *(int *)(out + 0x20) = *(int *)cur;
                        *(int *)(out + 0x24) = *(int *)(cur + 4);
                        if (callback != 0)
                            callback(cur, ret, user);
                    }
                }
                cur += 8;
            } while (--n != -1);
        }
    }
    return ret;
}
#endif
