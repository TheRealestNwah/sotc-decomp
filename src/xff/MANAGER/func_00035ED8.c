/* Parked: 2 diffs. Samples one animation track at time t: setFrame splits t into two frames and a
   fraction, then the position (func_00033868), rotation and two vector channels (func_00032B78,
   lerped on VU0) are written to out, with the channel types packed in trk->types. The tr alias
   and the o30 temporary (from the permuter) give the Original's reload pattern. Remaining: the
   Original schedules the last channel's andi (type) before the addiu for out + 0x30. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    unsigned int types;
    void *data0;
    void *data1;
    void *data2;
    void *data3;
} FTrack;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00031438(void *out, int type, void *data, int frame);
extern void func_00032B78(void *out, int type, void *data, int frame);

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

static inline void interpVec(void *out, int type, void *d, int i0, int i1, float frac)
{
    s128 v[2];

    if (frac == 0.0f) {
        if (d != 0) {
            func_00032B78(out, type, d, i0);
        }
    } else {
        if (d != 0) {
            func_00032B78(&v[0], type, d, i0);
            func_00032B78(&v[1], type, d, i1);
        }
        lerp3(out, &v[1], &v[0], frac);
    }
}

static void func_00035ED8(char *out, FTrack *trk, int n, float t)
{
    int i0, i1;
    float frac;
    FTrack *tr;
    char *o30;

    setFrame(&i0, &i1, &frac, t, n);
    tr = trk;
    func_00033868(out, (tr->types >> 15) & 0x1F, tr->data0, i0, i1, frac);
    interpRot(out + 0x10, (tr->types >> 10) & 0x1F, &tr->data1, i0, i1, frac);
    interpVec(out + 0x20, (trk->types >> 5) & 0x1F, trk->data2, i0, i1, frac);
    o30 = out + 0x30;
    interpVec(o30, tr->types & 0x1F, trk->data3, i0, i1, frac);
    *(int *)(out + 0x40) = tr->types >> 20;
}
#endif
