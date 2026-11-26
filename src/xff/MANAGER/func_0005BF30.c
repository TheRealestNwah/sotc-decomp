#ifdef NONMATCHING
/* Parked attempt: 18 differing words (register allocation). */
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;
extern void iosSetCurrentMatrix(void *);
extern void iosApplyCurrentMatrix(void *, void *);
extern int ClipCollisionFinderCallBack(char *, Vec4 *, Vec4 *, int, int (*)(), int);
extern void iosAbsVector(void *, void *);
extern float iosGetTableCos(short);
extern float iosGetTableSin(short);
extern float *GetGeometryPointerSurfacePlane(char *);
extern int func_00064660();
static const float T_0013EC90[10] = { 0.0f, 0.707f, 1.0f, 0.707f, -0.0f, -0.707f, -1.0f, -0.707f, 0.0f, 0.707f };
inline static void applyMatrix(float *out, float *m, float *v)
{
__asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}
inline static void normalizeXYZ(float *output, const float *input)
{
__asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}
inline static float vecDot(float *a, float *b)
{
  float dot;
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
  return dot;
}
static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static int func_0005BF30(char *obj, float *out, int arg, int flags, void *mtx, float x, float y, float z)
{
    Vec4 v0, v1, p0, p1, d, ad, n;
    float sx, sz;
    int i;
    int odd;
    int k;
    float *pq;
    float *pr;
    int ang;
    float c;
    const float *cosT;
    const float *sinT;

    odd = flags & 1;
    flags >>= 1;
    sx = 0.0f;
    if (odd) {
        sx = x;
        if (flags)
            sx = -sx;
    }
    sz = 0.0f;
    if (!odd) {
        sz = z;
        if (flags)
            sz = -sz;
    }
    cosT = &T_0013EC90[2];
    i = 0;
    sinT = cosT - 2;
    for (; i < 8; i++) {
        int j0 = (i + 6) & 7;
        int j1 = (i + 7) & 7;
        v0.w = 1.0f;
        v1.w = 1.0f;
        v1.x = cosT[j0] * sx;
        v1.y = -sinT[j0] * y;
        v1.z = cosT[j0] * sz;
        v0.x = cosT[j1] * sx;
        v0.y = -sinT[j1] * y;
        v0.z = cosT[j1] * sz;
        iosSetCurrentMatrix(mtx);
        iosApplyCurrentMatrix(&p0, &v1);
        iosApplyCurrentMatrix(&p1, &v0);
        if (ClipCollisionFinderCallBack(obj, &p0, &p1, arg, func_00064660, 0)) {
            float *pd = (float *)&d;
            float *pp0 = (float *)&p0;
            subXYZ((Vec4 *)pd, &p1, (Vec4 *)pp0);
            iosAbsVector(&ad, pd);
            if (ad.x > ad.y) {
                k = 2;
                if (ad.x > ad.z)
                    k = 0;
            } else {
                k = 1;
                if (!(ad.y > ad.z))
                    k = 2;
            }
            pq = &pd[k];
            pr = &pp0[k];
            ang = (short)(int)(((float)i + (((float *)(obj + 0x40))[k] - *pr) / *pq) * 8192.0f);
            c = -iosGetTableCos(ang);
            n.y = iosGetTableSin(ang) * y;
            n.w = 0;
            n.x = c * sx;
            n.z = c * sz;
            applyMatrix((float *)&n, mtx, (float *)&n);
            normalizeXYZ((float *)&n, (float *)&n);
            *out = vecDot(GetGeometryPointerSurfacePlane(obj), (float *)&n);
            return 1;
        }
    }
    return 0;
}

#endif
