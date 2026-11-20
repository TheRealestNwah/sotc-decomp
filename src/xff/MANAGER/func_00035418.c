typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int types; /* track types: data2 in bits 0-7, data1 in 8-15, data0 in 16-23 */
    void *data0;
    void *data1;
    void *data2;
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


static void func_00035418(char *out, Track *trk, int n, float t)
{
    int i0;
    int i1;
    float frac;
    unsigned int c;
    union {
        s128 q;
        float f[4];
    } sc;

    setFrame(&i0, &i1, &frac, t, n);
    interpRot(out, (trk->types >> 8) & 0xFF, &trk->data1, i0, i1, frac);
    interpScale(&sc, trk->types & 0xFF, trk->data2, i0, i1, frac);
    sc.f[1] += 0.5f;
    *(float *)(out + 0x10) = sc.f[0];
    *(int *)(out + 0x14) = sc.f[1];
    if (0.0f <= sc.f[2]) {
        c = sc.f[2];
        *(float *)(out + 0x20) = (int)((c >> 16) & 0xFF);
        *(float *)(out + 0x1C) = (int)((c >> 8) & 0xFF);
        *(float *)(out + 0x18) = (int)(c & 0xFF);
    } else {
        *(float *)(out + 0x20) = ((unsigned char *)trk)[0x11];
        *(float *)(out + 0x1C) = ((unsigned char *)trk)[0x12];
        *(float *)(out + 0x18) = ((unsigned char *)trk)[0x13];
    }
    out[0x24] = trk->hi;
    out[0x25] = trk->lo;
}
