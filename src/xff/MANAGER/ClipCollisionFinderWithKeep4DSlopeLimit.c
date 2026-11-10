/* ~126 diffs, 6 words longer (141 vs 135). Clips a 4D segment against the keep list (keep[0x20] entries of stride 0x14 at keep[0x24], via func_0009D8F8 + func_000A2B30) and then against the finder entries (min(f[0], f[1]) entries of stride 8 at f[3], via func_0009D8F8 + func_000A0DE8, falling back to func_000A1580 when the first returns 0), keeping the nearest hit in out (quad, quad, and the 2-int tag at out+0x20) and returning the last hit code. The Original keeps keep=$s3, out=$s4, finder=$s5, start=$s6, ret=$s7, cur=$s0, n=$s1 and the out+0x20 tag pointer in $s2 with -1 in $fp; ours allocates a different order (register pins for all of them made it worse: 133). */
typedef int s128 __attribute__((mode(TI)));

extern void func_0009D8F8(void *, void *, void *, int);
extern int func_000A2B30(void *, void *, void *, void *, void *, float, void *);
extern int func_000A0DE8(void *, void *, void *, void *, void *, float);
extern int func_000A1580(void *, void *, void *, void *, void *, float);

#ifdef NONMATCHING
int ClipCollisionFinderWithKeep4DSlopeLimit(char *out, s128 *start, s128 *end, int *finder, int *keep, float f12)
{
    struct { s128 e; s128 q10; s128 q20; s128 pad30; s128 pad40; s128 q50; s128 q60; s128 q70; } L;
    int ret = 0;
    int n;
    char *cur;
    int r;
    int ok;
    int one;

    *(s128 *)out = *end;
    if (keep != 0 && (n = keep[0x20 / 4]) != 0) {
        cur = (char *)keep[0x24 / 4];
        n--;
        if (n != -1) {
            L.e = *start;
            do {
                func_0009D8F8(&L.q70, cur, &L.e, 1);
                r = func_000A2B30(&L.q20, &L.q10, &L.q70, out, cur, f12, keep);
                if (r != 0) {
                    if (r - 5 < 2U)
                        L.e = L.q60;
                    ret = r;
                    *(s128 *)out = L.q60;
                    *(s128 *)(out + 0x10) = L.q10;
                    *(int *)(out + 0x20) = *(int *)cur;
                    *(int *)(out + 0x24) = *(int *)(cur + 4);
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
                if (*(int *)cur != 0) {
                    func_0009D8F8(&L.q60, cur, start, 1);
                    L.q70 = *(s128 *)out;
                    r = func_000A0DE8(&L.q10, &L.e, &L.q60, &L.q70, cur, f12);
                    one = 1;
                    ok = 0;
                    if (r == 1) {
                        L.q70 = L.q50;
                        ok = 1;
                    }
                    if (r == 0) {
                        if (func_000A1580(&L.q10, &L.e, &L.q60, &L.q70, cur, f12) != 0)
                            ok = one;
                    }
                    if (ok != 0) {
                        ret = ok;
                        *(s128 *)out = L.q50;
                        *(s128 *)(out + 0x10) = L.e;
                        *(int *)(out + 0x20) = *(int *)cur;
                        *(int *)(out + 0x24) = *(int *)(cur + 4);
                    }
                }
                cur += 8;
            } while (--n != -1);
        }
    }
    return ret;
}
#endif
