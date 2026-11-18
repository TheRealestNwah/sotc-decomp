typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int types; /* track types: data2 in bits 0-7, data1 in 8-15, data0 in 16-23 */
    void *data0;
    void *data1;
    void *data2;
    float pos[3];
    unsigned int lo : 4;
    unsigned int hi : 4;
    unsigned int pad8 : 24;
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


/* Parked at 1 diff: in interpRot's frac == 0 path the Original has a plain beqz with
 * the scale type's andi in its delay slot; gcc 2.96 emits beql here instead. */
#ifdef NONMATCHING
static void func_00035710(char *out, Track *trk, int n, float t)
{
    int i0;
    int i1;
    float frac;
    unsigned int c;

    setFrame(&i0, &i1, &frac, t, n);
    func_00033868(out, (trk->types >> 16) & 0xFF, trk->data0, i0, i1, frac);
    interpRot(out + 0x10, (trk->types >> 8) & 0xFF, &trk->data1, i0, i1, frac);
    {
    union {
        s128 q;
        float f[4];
    } sc;
    interpScale(&sc, trk->types & 0xFF, trk->data2, i0, i1, frac);
    *(float *)(out + 0x20) = sc.f[0];
    *(float *)(out + 0x24) = sc.f[1];
    if (0.0f <= sc.f[2]) {
        c = sc.f[2];
        *(float *)(out + 0x30) = (int)((c >> 16) & 0xFF);
        *(float *)(out + 0x2C) = (int)((c >> 8) & 0xFF);
        *(float *)(out + 0x28) = (int)(c & 0xFF);
    } else {
        *(float *)(out + 0x30) = ((unsigned char *)trk)[0x1D];
        *(float *)(out + 0x2C) = ((unsigned char *)trk)[0x1E];
        *(float *)(out + 0x28) = ((unsigned char *)trk)[0x1F];
    }
    }
    out[0x34] = trk->hi;
    out[0x35] = trk->lo;
    *(float *)(out + 0x38) = trk->pos[0];
    *(float *)(out + 0x3C) = trk->pos[1];
    *(float *)(out + 0x40) = trk->pos[2];
}
#endif
