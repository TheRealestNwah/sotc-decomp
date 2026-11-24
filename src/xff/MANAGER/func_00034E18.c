typedef int s128 __attribute__((mode(TI)));

typedef struct {
    unsigned int types; /* track types: data2 in bits 0-3, data1 in 8-11, data0 in 16-19 */
    void *data0;
    void *data1;
    void *data2;
} Track;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00031438(void *out, int type, void *data, int frame);
extern int func_00032B78(void *out, int type, void *data, int frame);
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
static inline void setFrame(int *i0, int *i1, float *frac, float t, int n, float t2)
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
    {
        float f;
        if ((float)n < t2) {
            f = t - (float)*i0;
        } else {
            f = t - (float)*i0;
        }
        *frac = f;
        __asm__ __volatile__("" ::: "memory");
    }
}

static inline void lerp3(void *out, void *a, void *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void interpRot(void *out, int type_, void **data_, int i0, int i1, float frac)
{
    register void **data __asm__("$17") = data_;
    register int type __asm__("$16") = type_;
    s128 v[2];

    if (frac == 0.0f) {
        if (*data != 0) {
            func_00031438(out, type, *data, i0);
        }
    } else {
        /* The copy keeps gcc from threading the null test past the second check. */
        void *d = *data;
        if (d != 0) {
            func_00031438(&v[0], type, d, i0);
        }
        if (*data != 0) {
            func_00031438(&v[1], type, *data, i1);
        }
        lerp4(out, &v[1], &v[0], frac);
    }
}

static inline void interpScale(void *out, int type, void *data, int i0, int i1, float frac)
{
    s128 v[2];

    if (frac == 0.0f) {
        if (data != 0) {
            func_00032B78(out, type, data, i0);
        }
    } else {
        if (data != 0) {
            func_00032B78(&v[0], type, data, i0);
            func_00032B78(&v[1], type, data, i1);
        }
        lerp3(out, &v[1], &v[0], frac);
    }
}

extern void func_000333C8(void *out, int type, void *data, float a, float b);

static inline void evalKey(unsigned char *a, int type, void *data, int n, float t, float end)
{
    unsigned char b[16];

    if (end <= t) {
        func_000333C8(a, type, data, t, end);
    } else {
        func_000333C8(a, type, data, (float)(n - 1), end);
        func_000333C8(b, type, data, t, 0.0f);
        { int x = b[0]; a[1] = a[1] | b[1]; a[0] |= x; a[2] |= b[0]; }
    }
}

/* Parked: 1 diff (built on func_00035C78's and func_00034B30's inlines).
 * frac is forced back to memory after setFrame stores it, interpRot pins
 * data/type to $s1/$s0, and n is copied into $s5 after setFrame.
 * Remaining: interpRot's first null test becomes a beql instead of beqz. */
#ifdef NONMATCHING
static void func_00034E18(char *out, Track *trk, int n, float t, float t2)
{
    int i0;
    int i1;
    float frac;

    setFrame(&i0, &i1, &frac, t, n, t2);
    {
        register int nn __asm__("$21") = n;
        func_00033868(out, (trk->types >> 12) & 0xF, trk->data0, i0, i1, frac);
        interpRot(out + 0x10, (trk->types >> 8) & 0xF, &trk->data1, i0, i1, frac);
        interpScale(out + 0x20, (trk->types >> 4) & 0xF, trk->data2, i0, i1, frac);
        evalKey((unsigned char *)out + 0x30, trk->types & 0xF, (char *)trk + 0x10, nn, t, t2);
    }
}
#endif
