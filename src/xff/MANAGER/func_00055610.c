typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

typedef struct { float speed; float rate; float maxSpeed; float angle; float angleRate; float maxAngle; } JumpLimit;
typedef struct { char pad0[0x50]; float f50; } Motion;
extern char *GetCharacterClass(void *);

static inline float sqrtf_(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float lengthSquareXYZ(Vec4 *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline void scaleXYZ(Vec4 *out, Vec4 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void scaleXYZW(Vec4 *out, Vec4 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void normalizeXYZ(Vec4 *out, Vec4 *a)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a) : "memory");
}

static void func_00055610(void *obj, int *ref)
{
    JumpLimit *lim = dldElement(ref);
    char *cc;
    Vec4 *v;
    int n;
    float f;
    float len2;
    float ang;
    Motion *m;

    if (lim == 0) {
        return;
    }
    cc = GetCharacterClass(obj);
    n = (int)lim->speed;
    v = (Vec4 *)(cc + 0x30);
    if (n >= 0) {
        float lim2 = (float)(n * n);
        float rate;
        len2 = lengthSquareXYZ(v);
        rate = lim->rate;
        if (lim2 < len2) {
            float inv = 1.0f / rate;
            float scale;
            if (lim2 * (inv * inv) < len2) {
                scale = rate;
            } else {
                float len = sqrtf_(len2);
                float fn = (float)n;
                float t = (len - fn) / (fn * inv - fn);
                scale = (1.0f - t) + rate * t;
            }
            scaleXYZ(v, v, scale);
        }
    }
    f = lim->maxSpeed;
    len2 = lengthSquareXYZ(v);
    if (0.0f <= f && f * f < len2) {
        normalizeXYZ(v, v);
        scaleXYZW(v, v, f);
    }
    ang = lim->angle * 0.017453293f;
    if (cc[0x529]) {
        if (0.0f <= ang && ang < (*(Motion **)(cc + 0x19C))->f50) {
            float rate = lim->angleRate;
            float a = ang * (1.0f / rate);
            float scale;
            m = *(Motion **)(cc + 0x19C);
            if (a < m->f50) {
                scale = rate;
            } else {
                float t = (m->f50 - ang) / (a - ang);
                scale = (1.0f - t) + rate * t;
            }
            __asm__ __volatile__("" ::: "memory");
            m->f50 *= scale;
            __asm__ __volatile__("" ::: "memory");
        }
    }
    {
        float cur;
        f = lim->maxAngle;
        m = *(Motion **)(cc + 0x19C);
        cur = m->f50;
        if (0.0f <= f && f < cur) {
            m->f50 = f;
        }
    }
}
