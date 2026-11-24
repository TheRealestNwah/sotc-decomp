typedef int s128 __attribute__((mode(TI)));

typedef struct {
    unsigned int types;
    void *data0;
    void *data1;
    char data2[4];
    unsigned char *data3;
} Track;

typedef struct {
    char pad0[0x20];
    unsigned char flags[4];
    char pad24[0xC];
    int mode;
    char pad34[0xC];
    float f40;
} Out;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00031438(void *out, int type, void *data, int frame);
extern void func_000333C8(void *out, int type, void *data, float a, float b);

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

/* The empty asm reading frac from memory keeps the Original's store before the
 * first call's argument setup. The empty asm on `o` keeps out+0x10 out of the
 * first call's delay slot. The dead `(float)n < t2` test reproduces the
 * Original's unused c.lt.s. */
static void func_00034B30(Out *out, Track *trk, int n, float t, float t2)
{
    int i0;
    int i1;
    float frac;
    int m;

    setFrame(&i0, &i1, &frac, t, n, t2);
    if ((float)n < t2)
        m = 1;
    __asm__ ("" : : "m"(frac));
    func_00033868(out, (trk->types >> 12) & 0xF, trk->data0, i0, i1, frac);
    {
        char *o = (char *)out + 0x10;
        __asm__ ("" : "+r"(o));
        interpRot(o, (trk->types >> 8) & 0xF, &trk->data1, i0, i1, frac);
    }
    evalKey(out->flags, (trk->types >> 4) & 0xF, trk->data2, n, t, t2);
    out->f40 = trk->data3[(int)t] * (1.0f / 255.0f) * 2.0f + -1.0f;
    switch (((unsigned char *)trk)[3] & 6) {
    case 2:
        m = 1;
        break;
    case 4:
        m = 2;
        break;
    case 6:
        m = 3;
        break;
    default:
        m = 0;
        break;
    }
    out->mode = m;
}
