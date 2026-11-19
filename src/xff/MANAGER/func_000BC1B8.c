typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { short type; short pad2; int count; int n; char padC[0x1C]; float *param; } ClothHeader;
typedef struct { char pad0[0x10]; Vec4 *pts; char pad14[4]; } ClothStrand;
typedef struct { char pad[0x40]; char flag; } ClothGeo;
typedef struct { ClothHeader *header; char pad4[8]; ClothStrand *strands; char pad10[0x20]; ClothGeo geo; } Cloth;

static inline float subRsqrt(Vec4 *out, Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf8, vf5, vf6\n"
                         "vmul.xyz vf7, vf8, vf8\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vrsqrt Q, vf0w, vf7x\n"
                         "sqc2 vf8, 0x0(%3)\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b), "r"(out) : "$2", "memory");
    return r;
}

static inline void scaleAdd(Vec4 *out, Vec4 *base, Vec4 *dir, float k)
{
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "vadd.xyz vf7, vf7, vf5\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(base), "r"(dir), "f"(k) : "$8", "memory");
}

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float dot3(Vec4 *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline void scaleXYZW(Vec4 *out, Vec4 *src, float k)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(src), "r"(k) : "memory");
}

static inline void addXYZ(Vec4 *out, Vec4 *a)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a) : "memory");
}

static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline void limitLen(Vec4 *out, Vec4 *base, float len, float lim)
{
    Vec4 g;
    float r = subRsqrt(&g, out, base);
    if (r < lim) {
        scaleAdd(out, base, &g, len * r);
    }
}

/* Parked at 8 diffs: the Original passes &tmp in a3 and &d in t1 to the
 * subRsqrt/scaleAdd pair; gcc swaps the two registers. */
#ifdef NONMATCHING
static void func_000BC1B8(Cloth *cloth, void *work)
{
    ClothHeader *h = cloth->header;
    ClothStrand *s = cloth->strands;
    float len = h->param[1];
    float lim = h->param[2];
    float len2 = len * len;
    int n = h->count;

    while (n-- != 0) {
        Vec4 *p = s->pts;
        int j;
        for (j = 1; j < h->n; j++) {
            Vec4 tmp;
            Vec4 d;
            Vec4 *next = p + 1;
            float r = subRsqrt(&d, next, p);
            if (r < lim) {
                scaleAdd(&tmp, p, &d, len * r);
            } else {
                tmp.q = next->q;
            }
            if (j < h->n - 1) {
                Vec4 e;
                float l2;
                subXYZ(&e, p + 2, &tmp);
                l2 = dot3(&e);
                if (len2 < l2) {
                    Vec4 f;
                    float l = sqrtF(l2);
                    float k = 1.0f - (l - len) / l;
                    scaleXYZW(&f, &e, 1.0f - k * k);
                    addXYZ(&tmp, &f);
                    limitLen(&tmp, p, len, lim);
                }
            }
            p[1].q = tmp.q;
            p = next;
        }
        s++;
    }
}
#endif

#ifdef NONMATCHING
extern void GetGeometryPointerPosition(Vec4 *, ClothGeo *);
extern void clothmath_doubleTensionMove(Vec4 *p, Vec4 *q, Vec4 *anchor, float maxSq, float k, float lim);

static void func_000BC5C8(Cloth *cloth, void *work, int unused)
{
    ClothHeader *h = cloth->header;

    switch (h->type) {
    case 0:
    default: {
        int n = h->count;
        ClothStrand *s = cloth->strands;
        float len = h->param[1];
        float lim = h->param[2];

        int m = h->n - 1;

        while (n--) {
            Vec4 *p = s->pts;
            int j = m;
            while (j--) {
                limitLen(p + 1, p, len, lim);
                p++;
            }
            s++;
        }
        break;
    }
    case 1: {
        ClothGeo *geo = &cloth->geo;
        if (geo->flag != 0) {
            int n = h->n;
            ClothStrand *s = cloth->strands;
            float len = h->param[1];
            float lim = h->param[2];
            float len2;
            Vec4 *p;
            int j;
            int m;

            {
                int k = n - 1;
                GetGeometryPointerPosition(&s->pts[k], geo);
            }
            len2 = len * len;
            p = s->pts + 1;
            m = n - 2;
            j = m;
            while (j--) {
                Vec4 *q = p;
                p++;
                clothmath_doubleTensionMove(q, p, q - 1, len2, len, lim);
            }
            p = s->pts + m;
            j = m;
            while (j--) {
                Vec4 *q = p;
                p--;
                clothmath_doubleTensionMove(q, p, q + 1, len2, len, lim);
            }
        } else {
            func_000BC1B8(cloth, work);
        }
        break;
    }
    }
}
#endif
