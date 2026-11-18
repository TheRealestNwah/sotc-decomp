typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0;
    char type1; /* track type of data1 (rotation) */
    char type0; /* track type of data0 */
    char pad3;
    void *data0;
    void *data1;
} Track;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00031438(void *out, int type, void *data, int frame);

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

static inline void interpRot(void *out, int type, void **data, int i0, int i1, float frac)
{
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

static void func_00034530(char *out, Track *trk, int n, float t)
{
    int i0;
    int i1;
    float frac;

    setFrame(&i0, &i1, &frac, t, n);
    func_00033868(out, trk->type0, trk->data0, i0, i1, frac);
    interpRot(out + 0x10, trk->type1, &trk->data1, i0, i1, frac);
}
