/* NONMATCHING: func_00033B88 (2 diffs, same size). The tail OR-merge
 * loads o[1] and b[1] into swapped registers ($a0/$v0). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int types;
    void *data0;
    void *data1;
    void *data2;
} BTrack;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00031438(void *out, int type, void *data, int frame);
extern int func_000333C8(unsigned char *out, int type, void **data, float t, float end);

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

static inline void interpBool(unsigned char *o, int type, void **data, int n, float t, float end)
{
    if (end <= t) {
        func_000333C8(o, type, data, t, end);
    } else {
        unsigned char b[4];

        func_000333C8(o, type, data, (float)(n - 1), end);
        func_000333C8(b, type, data, t, 0.0f);
        {
            int x = b[0];

            o[1] = b[1] | o[1];
            o[0] |= x;
            o[2] |= b[0];
        }
    }
}

void func_00033B88(char *out, BTrack *trk, int n, float t, float end)
{
    int i0;
    int i1;
    float frac;

    setFrame(&i0, &i1, &frac, t, n);
    if ((float)n < end) {
        int z = i1;
        i1 = z;
    }
    func_00033868(out, (trk->types >> 16) & 0xFF, trk->data0, i0, i1, frac);
    interpRot(out + 0x10, (trk->types >> 8) & 0xFF, &trk->data1, i0, i1, frac);
    interpBool((unsigned char *)out + 0x20, trk->types & 0xFF, &trk->data2, n, t, end);
}
#endif
