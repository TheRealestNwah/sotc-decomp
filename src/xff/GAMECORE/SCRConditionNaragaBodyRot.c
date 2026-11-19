typedef float Vec4[4] __attribute__((aligned(16)));

extern int *DldSysUndefSymbol;
extern float iosGetCosf(float);
extern void GetMotionNodeQuaternionPos(void *, void *, int, int, int);

static inline void quatDirZ(float *dst, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(q) : "memory");
}

static inline void vecNormalize(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "memory");
}

static inline float vecDot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline char *resolveElem(unsigned int *p)
{
    unsigned int w = *p;
    int off = w & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)p - off) : 0;

    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((w >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static inline int resolveCount(unsigned int *p)
{
    unsigned int w = *p;
    int off = w & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)p - off) : 0;

    if (t != 0 && t != DldSysUndefSymbol)
        return t[3];
    return 0;
}

int SCRConditionNaragaBodyRot(int a0, int a1, int a2, int a3, int t0, int t1, int t2, unsigned int *ref)
{
    Vec4 base;
    Vec4 q;
    Vec4 pos;
    Vec4 dir;
    unsigned int *list;
    int n;
    int i;
    int j;
    float c1;
    float c2;

    list = (unsigned int *)resolveElem(ref);
    n = resolveCount(ref);
    c1 = iosGetCosf(0x1.4f1a6cp+1f);
    c2 = iosGetCosf(0x1.921fb4p-1f);
    GetMotionNodeQuaternionPos(q, pos, a0, *(int *)(resolveElem(list) + 8), 1);
    quatDirZ(base, q);
    base[1] = 0.0f;
    vecNormalize(base, base);
    for (i = 1; i < n; i++) {
        GetMotionNodeQuaternionPos(q, pos, a0, *(int *)(resolveElem(&list[i]) + 8), 1);
        quatDirZ(dir, q);
        dir[1] = 0.0f;
        vecNormalize(dir, dir);
        if (vecDot(dir, base) < c1) {
            for (j = i + 1; j < n; j++) {
                GetMotionNodeQuaternionPos(q, pos, a0, *(int *)(resolveElem(&list[j]) + 8), 1);
                quatDirZ(dir, q);
                dir[1] = 0.0f;
                vecNormalize(dir, dir);
                if (c2 < vecDot(dir, base))
                    return 1;
            }
            return 0;
        }
    }
    return 0;
}
