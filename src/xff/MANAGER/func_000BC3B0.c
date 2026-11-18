/* Parked at 7 diffs: the Original keeps &d (sp+0x10) in s4 and a copy in s5,
 * using s5 for subXYZ/length and s4 for normalize/GetQuaternionByAxisDirZY;
 * gcc 2.96 swaps them. A 25-minute permuter run found nothing. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { char pad0[4]; float len; } ClothParam;
typedef struct { short type; short pad2; int count; int n; char padC[0x1C]; ClothParam *param; } ClothHeader;
typedef struct { char pad0[8]; Vec4 *dst; char padC[4]; Vec4 *a; Vec4 *b; } ClothStrand;
typedef struct { ClothHeader *header; char pad4[4]; char group[4]; ClothStrand *strands; char pad10[0x60]; signed char first; } Cloth;

extern float ZUnitVector[];
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern char *GetLayoutClass(void *);
extern void GetQuaternionByAxisDirZY(void *, Vec4 *, float *);
extern void UpdateLayoutClassSimpleGeometry(char *, float);

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scaleXYZ(Vec4 *out, Vec4 *src, float k)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(src), "r"(k) : "memory");
}

static inline float length(Vec4 *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline void normalize(Vec4 *a)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(a) : "memory");
}

static void func_000BC3B0(Cloth *cloth, void *work, float t0, float t1)
{
    ClothHeader *h = cloth->header;
    ClothStrand *s = cloth->strands;
    int n = h->count;
    int m = h->n;

    while (n-- != 0) {
        Vec4 *a = s->a;
        Vec4 *b = s->b;
        Vec4 *dst = s->dst;
        int k = m;
        while (k-- != 0) {
            Vec4 tmp;
            subXYZ(&tmp, a, b);
            scaleXYZ(dst, &tmp, t1);
            dst->f[3] = 0.0f;
            a++;
            b++;
            dst++;
        }
        s++;
    }
    switch (h->type) {
    case 0:
        break;
    case 1: {
        Vec4 *p = cloth->strands->a;
        int first = cloth->first;
        void *last = 0;
        void **node;
        for (node = isysGroupForFirst(cloth->group, 0); node != 0; node = isysGroupForNext(node, 0)) {
            Vec4 d;
            Vec4 *next = p + 1;
            char *lc;
            last = *node;
            lc = GetLayoutClass(last);
            subXYZ(&d, p, next);
            if (first) {
                float l = length(&d);
                first = 0;
                *(float *)(lc + 0x98) = l / h->param->len;
            }
            normalize(&d);
            GetQuaternionByAxisDirZY(*(void **)(lc + 0x13C), &d, ZUnitVector);
            (*(Vec4 **)(lc + 0x134))->q = p->q;
            p = next;
            UpdateLayoutClassSimpleGeometry(lc, 0.0f);
        }
        if (last)
            isysGroupForExit(last, 0);
        break;
    }
    }
}
#endif
