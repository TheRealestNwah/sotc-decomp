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
        ((union { float f; unsigned int u; } *)frac)->f = f;
    }
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

extern void func_000333C8(void *out, int type, void **data, float t, float t2);

static inline void evalKey(unsigned char *a, int type, void **data, int n, float t, float end)
{
    unsigned char b[16];
    int x;

    if (end <= t) {
        func_000333C8(a, type, data, t, end);
    } else {
        func_000333C8(a, type, data, (float)(n - 1), end);
        func_000333C8(b, type, data, t, 0.0f);
        x = b[0];
        a[1] = a[1] | b[1];
        a[0] |= x;
        a[2] |= b[0];
    }
}

/* The empty asm reading frac from memory keeps the Original's store before
 * the call setup and its reload into $f12; setFrame stores frac through a
 * union so the store may alias the track loads. */
static void func_00035A20(char *out, unsigned int *trk, int n, float t, float t2)
{
    int i0;
    int i1;
    float frac;

    setFrame(&i0, &i1, &frac, t, n, t2);
    __asm__ ("" : : "m"(frac));
    func_00033868(out, (trk[0] >> 16) & 0xFF, (void *)trk[1], i0, i1, frac);
    interpRot(out + 0x10, (trk[0] >> 8) & 0xFF, (void **)&trk[2], i0, i1, frac);
    evalKey(out + 0x20, trk[0] & 0xFF, (void **)&trk[3], n, t, t2);
}
