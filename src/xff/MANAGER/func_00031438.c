/* func_00031438 and the motion-track samplers that call it (func_00033DE0 to
 * func_00035C78). They share one file because the samplers only match with
 * func_00031438 defined in the same translation unit: with its body known,
 * reorg fills interpRot's null-test branch as a plain beqz instead of beql.
 * Each sampler's helpers carry its address as a suffix until the group's
 * Source cleanup merges them. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void iosGetSinCosf(float *out, float angle);

typedef struct { int w:9; int z:9; int y:9; int i:4; unsigned s:1; } P3;
typedef struct { int w:9; int z:9; int i:4; unsigned s:1; int x:9; } P4;
typedef struct { int w:9; int i:4; unsigned s:1; int y:9; int x:9; } P5;
typedef struct { int i:4; unsigned s:1; int z:9; int y:9; int x:9; } P6;
typedef struct { unsigned s:1; int z:10; int y:10; int x:11; } P14;

typedef struct {
    float m0, r0, m1, r1, m2, r2;
    void *p18;
    void *p1C;
    void *p20;
} Rng;

typedef struct {
    float m0, r0, m1, r1, m2, r2, m3, r3;
    void *p20;
} Rng4;

static inline void scale3(Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s) : "memory");
}

static inline float lenSq3(Vec4 *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

static inline float sqrtf_(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x) : "memory");
    return r;
}

static inline void sqrtStart(float x)
{
    __asm__ __volatile__("mfc1 $6, %0\n"
                         "qmtc2.ni $6, vf1\n"
                         "vsqrt Q, vf1x\n"
                         : : "f"(x) : "$6");
}

static inline float sqrtEnd(void)
{
    float r;
    __asm__ __volatile__("vwaitq\n"
                         "cfc2.ni $7, $vi22\n"
                         "mtc1 $7, %0\n"
                         : "=f"(r) : : "$7");
    return r;
}

#define K9 0x1.0101p-8f
#define K7 0x1.249248p-3f
#define KS 0x1.0002p-15f

static int func_00031438(Vec4 *o, int type, void *data, int idx)
{
    switch (type) {
    default:
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(o) : "memory");
        return 1;
    case 1: {
        float *k = (float *)((char *)data + idx * 16);
        float s = k[1] * k[1] + k[2] * k[2] + k[3] * k[3];
        float m;
        float w;
        if (1.0f < s)
            m = 1.0f;
        else
            m = s;
        w = sqrtf_(1.0f - m);
        o->f[3] = w;
        o->f[0] = k[1];
        o->f[1] = k[2];
        o->f[2] = k[3];
        if (((signed char *)k)[1] < 0)
            o->f[3] = -w;
        break;
    }
    case 10: {
        float *k = (float *)((char *)data + idx * 12);
        float w;
        o->f[0] = k[0];
        o->f[1] = k[1];
        o->f[2] = k[2];
        w = sqrtf_(1.0f - lenSq3(o));
        if (*(int *)k & 1)
            w = -w;
        o->f[3] = w;
        break;
    }
    case 11: {
        short *k = (short *)((char *)data + idx * 6);
        float w;
        o->f[0] = (float)k[0];
        o->f[1] = (float)k[1];
        o->f[2] = (float)k[2];
        scale3(o, KS);
        w = sqrtf_(1.0f - lenSq3(o));
        if ((unsigned short)k[0] & 1)
            w = -w;
        o->f[3] = w;
        break;
    }
    case 12: {
        Rng *d = data;
        short *k = (short *)d->p18 + idx * 3;
        float w;
        o->f[0] = (float)k[0] * d->r0 * KS + d->m0;
        o->f[1] = (float)k[1] * d->r1 * KS + d->m1;
        o->f[2] = (float)k[2] * d->r2 * KS + d->m2;
        w = sqrtf_(1.0f - lenSq3(o));
        if ((unsigned short)k[0] & 1)
            w = -w;
        o->f[3] = w;
        break;
    }
    case 3: {
        P3 *k = (P3 *)((Rng4 *)data)->p20 + idx;
        float a, b, c, t, base, r;
        a = (float)k->y * ((Rng4 *)data)->r0 * K9 + ((Rng4 *)data)->m0;
        o->f[1] = a;
        b = (float)k->z * ((Rng4 *)data)->r1 * K9 + ((Rng4 *)data)->m1;
        o->f[2] = b;
        c = (float)k->w * ((Rng4 *)data)->r2 * K9 + ((Rng4 *)data)->m2;
        o->f[3] = c;
        t = 1.0f - (a * a + b * b + c * c);
        sqrtStart(t);
        base = (float)k->i * ((Rng4 *)data)->r3 * K7 + ((Rng4 *)data)->m3;
        if (t < 0.0f) {
            o->f[0] = base + 0.0f;
        } else {
            r = sqrtEnd();
            if (k->s)
                r = -r;
            o->f[0] = r + base;
        }
        break;
    }
    case 4: {
        P4 *k = (P4 *)((Rng4 *)data)->p20 + idx;
        float a, b, c, t, base, r;
        a = (float)k->x * ((Rng4 *)data)->r0 * K9 + ((Rng4 *)data)->m0;
        o->f[0] = a;
        b = (float)k->z * ((Rng4 *)data)->r1 * K9 + ((Rng4 *)data)->m1;
        o->f[2] = b;
        c = (float)k->w * ((Rng4 *)data)->r2 * K9 + ((Rng4 *)data)->m2;
        o->f[3] = c;
        t = 1.0f - (a * a + b * b + c * c);
        sqrtStart(t);
        base = (float)k->i * ((Rng4 *)data)->r3 * K7 + ((Rng4 *)data)->m3;
        if (t < 0.0f) {
            o->f[1] = base + 0.0f;
        } else {
            r = sqrtEnd();
            if (k->s)
                r = -r;
            o->f[1] = r + base;
        }
        break;
    }
    case 5: {
        P5 *k = (P5 *)((Rng4 *)data)->p20 + idx;
        float a, b, c, t, base, r;
        a = (float)k->x * ((Rng4 *)data)->r0 * K9 + ((Rng4 *)data)->m0;
        o->f[0] = a;
        b = (float)k->y * ((Rng4 *)data)->r1 * K9 + ((Rng4 *)data)->m1;
        o->f[1] = b;
        c = (float)k->w * ((Rng4 *)data)->r2 * K9 + ((Rng4 *)data)->m2;
        o->f[3] = c;
        t = 1.0f - (a * a + b * b + c * c);
        sqrtStart(t);
        base = (float)k->i * ((Rng4 *)data)->r3 * K7 + ((Rng4 *)data)->m3;
        if (t < 0.0f) {
            o->f[2] = base + 0.0f;
        } else {
            r = sqrtEnd();
            if (k->s)
                r = -r;
            o->f[2] = r + base;
        }
        break;
    }
    case 6: {
        P6 *k = (P6 *)((Rng4 *)data)->p20 + idx;
        float a, b, c, t, base, r;
        a = (float)k->x * ((Rng4 *)data)->r0 * K9 + ((Rng4 *)data)->m0;
        o->f[0] = a;
        b = (float)k->y * ((Rng4 *)data)->r1 * K9 + ((Rng4 *)data)->m1;
        o->f[1] = b;
        c = (float)k->z * ((Rng4 *)data)->r2 * K9 + ((Rng4 *)data)->m2;
        o->f[2] = c;
        t = 1.0f - (a * a + b * b + c * c);
        sqrtStart(t);
        base = (float)k->i * ((Rng4 *)data)->r3 * K7 + ((Rng4 *)data)->m3;
        if (t < 0.0f) {
            o->f[3] = base + 0.0f;
        } else {
            r = sqrtEnd();
            if (k->s)
                r = -r;
            o->f[3] = r + base;
        }
        break;
    }
    case 14: {
        Rng *d = data;
        P14 *k = (P14 *)d->p18 + idx;
        float t;
        o->f[0] = (float)k->x * d->r0 * 0x1.00401p-10f + d->m0;
        o->f[1] = (float)k->y * d->r1 * 0x1.00804p-9f + d->m1;
        o->f[2] = (float)k->z * d->r2 * 0x1.00804p-9f + d->m2;
        t = 1.0f - lenSq3(o);
        if (t < 0.0f) {
            o->f[3] = 0.0f;
        } else {
            float w = sqrtf_(t);
            if (k->s)
                w = -w;
            o->f[3] = w;
        }
        break;
    }
    case 2: {
        float sc[2];
        o->q = ((Vec4 *)data)->q;
        iosGetSinCosf(sc, ((float **)data)[3][idx]);
        scale3(o, sc[1]);
        o->f[3] = sc[0];
        break;
    }
    case 13: {
        Rng *d = data;
        float sc[2];
        iosGetSinCosf(sc, ((float)(*(short **)((char *)d + 0x14))[idx] * d->r0 * KS + d->m0) * 0.5f);
        o->f[0] = d->m1;
        o->f[1] = d->r1;
        o->f[2] = d->m2;
        scale3(o, sc[1]);
        o->f[3] = sc[0];
        break;
    }
    case 0:
        o->q = ((Vec4 *)data)->q;
        break;
    }
    return 0;
}


typedef struct {
    int types; /* track types: data2 in bits 0-3, data1 in 8-11, data0 in 16-19 */
    void *data0;
    void *data1;
    void *data2;
} Track_33DE0;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00032B78(void *out, int type, void *data, int frame);
static inline void lerp4_33DE0(void *out, void *a, void *b, float t)
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
static inline void setFrame_33DE0(int *i0, int *i1, float *frac, float t, int n)
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

static inline void lerp3_33DE0(void *out, void *a, void *b, float t)
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

static inline void interpRot_33DE0(void *out, int type, void **data, int i0, int i1, float frac)
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
        lerp4_33DE0(out, &v[1], &v[0], frac);
    }
}

static inline void interpScale_33DE0(void *out, int type, void *data, int i0, int i1, float frac)
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
        lerp3_33DE0(out, &v[1], &v[0], frac);
    }
}

static void func_00033DE0(char *out, Track_33DE0 *trk, int n, float t)
{
    int i0;
    int i1;
    float frac;

    setFrame_33DE0(&i0, &i1, &frac, t, n);
    func_00033868(out, (trk->types >> 16) & 0xF, trk->data0, i0, i1, frac);
    interpRot_33DE0(out + 0x10, (trk->types >> 8) & 0xF, &trk->data1, i0, i1, frac);
    interpScale_33DE0(out + 0x20, trk->types & 0xF, trk->data2, i0, i1, frac);
}


typedef struct {
    int types; /* track types: data2 in bits 0-3, data1 in 8-11, data0 in 16-19 */
    void *data0;
    void *data1;
    void *data2;
    float value;
} Track_34010;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00032B78(void *out, int type, void *data, int frame);
static inline void lerp4_34010(void *out, void *a, void *b, float t)
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
static inline void setFrame_34010(int *i0, int *i1, float *frac, float t, int n)
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

static inline void lerp3_34010(void *out, void *a, void *b, float t)
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

static inline void interpRot_34010(void *out, int type, void **data, int i0, int i1, float frac)
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
        lerp4_34010(out, &v[1], &v[0], frac);
    }
}

static inline void interpScale_34010(void *out, int type, void *data, int i0, int i1, float frac)
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
        lerp3_34010(out, &v[1], &v[0], frac);
    }
}

static void func_00034010(char *out, Track_34010 *trk, int n, float t)
{
    int i0;
    int i1;
    float frac;

    setFrame_34010(&i0, &i1, &frac, t, n);
    func_00033868(out, (trk->types >> 16) & 0xF, trk->data0, i0, i1, frac);
    interpRot_34010(out + 0x10, (trk->types >> 8) & 0xF, &trk->data1, i0, i1, frac);
    interpScale_34010(out + 0x20, trk->types & 0xF, trk->data2, i0, i1, frac);
    *(float *)(out + 0x30) = trk->value;
}


typedef struct {
    unsigned int types; /* track types: data2 in bits 0-3, data1 in 8-11, data0 in 16-19 */
    void *data0;
    void *data1;
    void *data2;
} Track_34E18;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00032B78(void *out, int type, void *data, int frame);
static inline void lerp4_34E18(void *out, void *a, void *b, float t)
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
static inline void setFrame_34E18(int *i0, int *i1, float *frac, float t, int n, float t2)
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

static inline void lerp3_34E18(void *out, void *a, void *b, float t)
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

static inline void interpRot_34E18(void *out, int type_, void **data_, int i0, int i1, float frac)
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
        lerp4_34E18(out, &v[1], &v[0], frac);
    }
}

static inline void interpScale_34E18(void *out, int type, void *data, int i0, int i1, float frac)
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
        lerp3_34E18(out, &v[1], &v[0], frac);
    }
}

extern void func_000333C8(void *out, int type, void *data, float a, float b);

static inline void evalKey_34E18(unsigned char *a, int type, void *data, int n, float t, float end)
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

/* Built on func_00035C78's and func_00034B30's inlines.
 * frac is forced back to memory after setFrame_34E18 stores it, interpRot_34E18 pins
 * data/type to $s1/$s0, and n is copied into $s5 after setFrame_34E18. */
static void func_00034E18(char *out, Track_34E18 *trk, int n, float t, float t2)
{
    int i0;
    int i1;
    float frac;

    setFrame_34E18(&i0, &i1, &frac, t, n, t2);
    {
        register int nn __asm__("$21") = n;
        func_00033868(out, (trk->types >> 12) & 0xF, trk->data0, i0, i1, frac);
        interpRot_34E18(out + 0x10, (trk->types >> 8) & 0xF, &trk->data1, i0, i1, frac);
        interpScale_34E18(out + 0x20, (trk->types >> 4) & 0xF, trk->data2, i0, i1, frac);
        evalKey_34E18((unsigned char *)out + 0x30, trk->types & 0xF, (char *)trk + 0x10, nn, t, t2);
    }
}


typedef struct {
    int types; /* track types: data2 in bits 0-7, data1 in 8-15, data0 in 16-23 */
    void *data0;
    void *data1;
    void *data2;
    unsigned int lo : 4;
    unsigned int hi : 4;
    unsigned int pad8 : 24;
} Track_35120;


extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00032B78(void *out, int type, void *data, int frame);
static inline void lerp4_35120(void *out, void *a, void *b, float t)
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
static inline void setFrame_35120(int *i0, int *i1, float *frac, float t, int n)
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

static inline void lerp3_35120(void *out, void *a, void *b, float t)
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

static inline void interpRot_35120(void *out, int type, void **data, int i0, int i1, float frac)
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
        lerp4_35120(out, &v[1], &v[0], frac);
    }
}

static inline void interpScale_35120(void *out, int type, void *data, int i0, int i1, float frac)
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
        lerp3_35120(out, &v[1], &v[0], frac);
    }
}


static void func_00035120(char *out, Track_35120 *trk, int n, float t)
{
    int i0;
    int i1;
    float frac;
    unsigned int c;

    setFrame_35120(&i0, &i1, &frac, t, n);
    func_00033868(out, (trk->types >> 16) & 0xFF, trk->data0, i0, i1, frac);
    interpRot_35120(out + 0x10, (trk->types >> 8) & 0xFF, &trk->data1, i0, i1, frac);
    {
    union {
        s128 q;
        float f[4];
    } sc_35120;
    interpScale_35120(&sc_35120, trk->types & 0xFF, trk->data2, i0, i1, frac);
    *(float *)(out + 0x20) = sc_35120.f[0];
    *(float *)(out + 0x24) = sc_35120.f[1];
    if (0.0f <= sc_35120.f[2]) {
        c = sc_35120.f[2];
        *(float *)(out + 0x30) = (int)((c >> 16) & 0xFF);
        *(float *)(out + 0x2C) = (int)((c >> 8) & 0xFF);
        *(float *)(out + 0x28) = (int)(c & 0xFF);
    } else {
        *(float *)(out + 0x30) = ((unsigned char *)trk)[0x11];
        *(float *)(out + 0x2C) = ((unsigned char *)trk)[0x12];
        *(float *)(out + 0x28) = ((unsigned char *)trk)[0x13];
    }
    }
    out[0x34] = trk->hi;
    out[0x35] = trk->lo;
}


typedef struct {
    int types; /* track types: data2 in bits 0-7, data1 in 8-15, data0 in 16-23 */
    void *data0;
    void *data1;
    void *data2;
    float pos[3];
    unsigned int lo : 4;
    unsigned int hi : 4;
    unsigned int pad8 : 24;
} Track_35710;


extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00032B78(void *out, int type, void *data, int frame);
static inline void lerp4_35710(void *out, void *a, void *b, float t)
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
static inline void setFrame_35710(int *i0, int *i1, float *frac, float t, int n)
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

static inline void lerp3_35710(void *out, void *a, void *b, float t)
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

static inline void interpRot_35710(void *out, int type, void **data, int i0, int i1, float frac)
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
        lerp4_35710(out, &v[1], &v[0], frac);
    }
}

static inline void interpScale_35710(void *out, int type, void *data, int i0, int i1, float frac)
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
        lerp3_35710(out, &v[1], &v[0], frac);
    }
}


static void func_00035710(char *out, Track_35710 *trk, int n, float t)
{
    int i0;
    int i1;
    float frac;
    unsigned int c;

    setFrame_35710(&i0, &i1, &frac, t, n);
    func_00033868(out, (trk->types >> 16) & 0xFF, trk->data0, i0, i1, frac);
    interpRot_35710(out + 0x10, (trk->types >> 8) & 0xFF, &trk->data1, i0, i1, frac);
    {
    union {
        s128 q;
        float f[4];
    } sc_35710;
    interpScale_35710(&sc_35710, trk->types & 0xFF, trk->data2, i0, i1, frac);
    *(float *)(out + 0x20) = sc_35710.f[0];
    *(float *)(out + 0x24) = sc_35710.f[1];
    if (0.0f <= sc_35710.f[2]) {
        c = sc_35710.f[2];
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


typedef struct {
    unsigned int types; /* track types: data2 in bits 0-3, data1 in 8-11, data0 in 16-19 */
    void *data0;
    void *data1;
    void *data2;
} Track_35C78;

extern void func_00033868(void *out, int type, void *data, int i0, int i1, float frac);
extern int func_00032B78(void *out, int type, void *data, int frame);
static inline void lerp4_35C78(void *out, void *a, void *b, float t)
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
static inline void setFrame_35C78(int *i0, int *i1, float *frac, float t, int n, float t2)
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

static inline void lerp3_35C78(void *out, void *a, void *b, float t)
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

static inline void interpRot_35C78(void *out, int type_, void **data_, int i0, int i1, float frac)
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
        lerp4_35C78(out, &v[1], &v[0], frac);
    }
}

static inline void interpScale_35C78(void *out, int type, void *data, int i0, int i1, float frac)
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
        lerp3_35C78(out, &v[1], &v[0], frac);
    }
}

/* The dead c.lt.s on t2 comes from setFrame_35C78's identical arms.
 * frac is forced back to memory after setFrame_35C78 stores it, and
 * interpRot_35C78 pins data to $s1 and type to $s0. */
static void func_00035C78(char *out, Track_35C78 *trk, int id, int n, float t, float t2)
{
    int i0;
    int i1;
    float frac;

    setFrame_35C78(&i0, &i1, &frac, t, n, t2);
    func_00033868(out, (trk->types >> 12) & 0xF, trk->data0, i0, i1, frac);
    interpRot_35C78(out + 0x10, (trk->types >> 8) & 0xF, &trk->data1, i0, i1, frac);
    interpScale_35C78(out + 0x20, (trk->types >> 4) & 0xF, trk->data2, i0, i1, frac);
    *(int *)(out + 0x30) = id;
    *(int *)(out + 0x34) = 0;
    *(int *)(out + 0x38) = ((unsigned char *)trk)[3];
}
