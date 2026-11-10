/* ~140 diffs, 168 vs 170 words. Arrow-water ripple effect update over a 25-entry table B_0018AD70 (stride 0x14: on, prev, pad, t, handle): spawns new entries (on && !prev) via func_00054388, round-robins one new handle via func_00054598 from the cursor at work+0x150, steps live ones (func_00052A38, func_000540D0), runs the group list (func_00052D18, stride 0x40), func_00053AE0, then copies on->prev and advances t by gcGlobalVar+0x190. Original builds the spawn predicate with two branches (v1 = 0 / 1 in delay slots) and keeps the table pointer in s0 with the work pointer in s1; ours uses sltiu and the opposite saved registers. */
typedef struct {
    int on;
    int prev;
    int pad8;
    float t;
    int handle;
} ArrowWater;

extern ArrowWater B_0018AD70[25];
extern char gcGlobalVar[];
extern int *getSpecialEffectObjWork(void *);
extern char *getEditWorkInitData(int);
extern void func_00054388(void *, int);
extern int func_00054598(void *, int);
extern void func_00053058(void *, void *, void *);
extern void func_00052A38(void *);
extern void func_000540D0(void *, int);
extern void func_00052D18(void *, void *);
extern void func_00053AE0(void *, void *, void *, void *, void *);

static inline int pending(ArrowWater *e)
{
    if (e->on == 0)
        return 0;
    if (e->prev == 0)
        return 1;
    return 0;
}

#ifdef NONMATCHING
void arrowWaterMain(char *obj)
{
    int i;
    int n;
    int *w = getSpecialEffectObjWork(obj);
    int *s2 = (int *)w[0];
    char *fp = (char *)w[2];
    char *s6 = (char *)w[1];
    char *d = getEditWorkInitData(*(int *)(*(char **)(obj + 0x1C) + 8));
    char *s5 = fp;
    ArrowWater *e;
    char *s1;
    int s0;

    i = 0;
    n = s2[0xF4 / 4];
    s2[0x118 / 4] = 0;
    s2[0x11C / 4] = 0;
    if (n > 0) {
        s1 = s6;
        e = B_0018AD70;
        do {
            if (pending(e)) {
                func_00054388(s1, i);
                n = s2[0xF4 / 4];
            }
            i++;
            s1 += 0x80;
            e++;
        } while (i < n);
    }
    func_00053058(obj, s2, s6);
    *(float *)((char *)s2 + 0xFC) = *(float *)(d + 0x10);
    n = s2[0xF4 / 4];
    s0 = s2[0x150 / 4];
    *(float *)((char *)s2 + 0x100) = *(float *)(d + 0x14);
    *(float *)((char *)s2 + 0x104) = *(float *)(d + 0x18);
    *(float *)((char *)s2 + 0x108) = *(float *)(d + 0x1C);
    *(float *)((char *)s2 + 0x10C) = *(float *)(d + 0x20);
    *(float *)((char *)s2 + 0x110) = *(float *)(d + 0x24);
    for (i = 0; i < n; i++, s0++) {
        if (!(s0 < n))
            s0 = 0;
        if (B_0018AD70[s0].on != 0 && B_0018AD70[s0].handle == 0) {
            B_0018AD70[s0].handle = func_00054598(s6 + (s0 << 7), s0);
            s2[0x150 / 4] = s0 + 1;
            break;
        }
    }
    n = s2[0xF4 / 4];
    s1 = s6;
    e = B_0018AD70;
    for (i = 0; i < n; i++, s1 += 0x80, e++) {
        if (e->on != 0) {
            func_00052A38(s1);
            func_000540D0(s1, i);
            s2[0x118 / 4]++;
            n = s2[0xF4 / 4];
        }
    }
    for (i = 0; i < s2[0x120 / 4]; i++, s5 += 0x40)
        func_00052D18(s2 + 0x120 / 4, s5);
    func_00053AE0(obj, s2, s6, d, fp);
    for (e = B_0018AD70, i = 24; i >= 0; i--, e++) {
        e->prev = e->on;
        if (e->on != 0)
            e->t = e->t + *(float *)(gcGlobalVar + 0x190);
    }
}
#endif
