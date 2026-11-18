typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int type2 : 4; /* track type of data2 */
    int typeB : 4; /* key type of dataB */
    int type1 : 4; /* track type of data1 (rotation) */
    int type0 : 4; /* track type of data0 */
    void *data0;
    void *data1;
    void *dataB;
    void *data2;
} Track;

typedef struct {
    int i0;
    int i1;
    float frac;
} Frame;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00031438(void *out, int type, void *data, int frame);
extern int func_000333C8(void *out, int type, void **data, float t, float end);

static inline void lerp4(void *out, void *a, void *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void setFrame(int *i0, int *i1, float *frac, float t, int n)
{
    if ((float)n < t) {
        if (n == 1) {
            t -= (float)(int)t;
        } else {
            t -= (float)((n - 1) * (int)(t / (float)(n - 1)));
        }
    }
    *i0 = (int)t;
    *i1 = *i0 + 1;
    *frac = t - (float)*i0;
}

static inline int getRot(void *out, int type, void **data, int frame)
{
    if (*data != 0) {
        return func_00031438(out, type, *data, frame);
    }
    return 0;
}

static inline int interpRot(void *out, int type, void **data, int i0, int i1, float frac)
{
    s128 v[2];
    int r0;
    int r1;

    if (frac == 0.0f) {
        return getRot(out, type, data, i0);
    }
    r0 = getRot(&v[0], type, data, i0);
    r1 = getRot(&v[1], type, data, i1);
    lerp4(out, &v[1], &v[0], frac);
    return r0 | r1;
}

static inline int evalKey(unsigned char *a, int type, void **data, int n, float t, float end)
{
    unsigned char b[16];
    int k;
    float f;

    if (end <= t) {
        k = func_000333C8(a, type, data, t, end);
    } else {
        k = func_000333C8(a, type, data, (float)(n - 1), end);
        f = (float)func_000333C8(b, type, data, t, 0.0f);
        if (f < 0.0f) {
            k = (int)(float)k;
        } else {
            k = (int)f;
        }
        a[0] |= b[0];
        a[1] |= b[1];
        a[2] |= b[0]; /* b[0] again in the Original */
    }
    return k;
}

static int func_00034850(char *out, Track *trk, int n, float t, float end)
{
    unsigned char a[16];
    int k;
    int i0;
    int i1;
    float frac;

    k = evalKey(a, trk->typeB, &trk->dataB, n, t, end);
    if (k < 0) {
        setFrame(&i0, &i1, &frac, t, n);
    } else {
        i1 = k;
        i0 = k;
        frac = 0.0f;
    }
    func_00033868(out, trk->type0, trk->data0, i0, i1, frac);
    func_00033868(out + 0x20, trk->type2, trk->data2, i0, i1, frac);
    return interpRot(out + 0x10, trk->type1, &trk->data1, i0, i1, frac);
}
