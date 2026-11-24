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

/* Parked: 1 diff. The dead c.lt.s on t2 comes from setFrame's identical arms.
 * frac is forced back to memory after setFrame stores it, and
 * interpRot pins data to $s1 and type to $s0.
 * Remaining: in interpRot's frac == 0 path the Original has a plain beqz where
 * gcc 2.96 emits beql with the same delay-slot srl. */
#ifdef NONMATCHING
static void func_00035C78(char *out, Track *trk, int id, int n, float t, float t2)
{
    int i0;
    int i1;
    float frac;

    setFrame(&i0, &i1, &frac, t, n, t2);
    func_00033868(out, (trk->types >> 12) & 0xF, trk->data0, i0, i1, frac);
    interpRot(out + 0x10, (trk->types >> 8) & 0xF, &trk->data1, i0, i1, frac);
    interpScale(out + 0x20, (trk->types >> 4) & 0xF, trk->data2, i0, i1, frac);
    *(int *)(out + 0x30) = id;
    *(int *)(out + 0x34) = 0;
    *(int *)(out + 0x38) = ((unsigned char *)trk)[3];
}
#endif
