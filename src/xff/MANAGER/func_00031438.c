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
