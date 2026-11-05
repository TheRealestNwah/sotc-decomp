typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

extern void SCRGetCharNodePos(float *, void *, int);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);
extern void SCRSetupMissile1(void *, float *, float *, int);

static inline void vecDirection(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vsub.xyzw vf6, vf4, vf5\n"
                         "vmul.xyz vf5, vf6, vf6\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "vsqrt Q, vf5x\n"
                         "vwaitq\n"
                         "vaddq.x vf5, vf0, Q\n"
                         "vdiv Q, vf0w, vf5x\n"
                         "vsub.xyzw vf7, vf0, vf0\n"
                         "vwaitq\n"
                         "vmulq.xyz vf7, vf6, Q\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b));
}

extern char *GetSCRCharaAIWorkPtr(void *);
extern float iosGetRandom(void);

static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000D2438(void *obj, VecQ *tgt, int node)
{
    VecQ t;
    Vec4 q;
    Vec4 pos;
    Vec4 dir;
    float r;
    float r2;
    char *ai;

    ai = GetSCRCharaAIWorkPtr(obj);
    SCRGetCharNodePos(pos, obj, node);
    r = 0.0f;
    if (*(int *)(ai + 0x41D0) != 0) {
        if (*(int *)(ai + 0x41D4) != 0) {
            r = *(float *)(ai + 0x41DC);
        } else {
            r = *(float *)(ai + 0x41D8);
        }
    }
    if (r == 0.0f) {
        t.q = tgt->q;
    } else {
        r2 = r + r;
        t.f[0] = r2 * iosGetRandom() - r;
        t.f[1] = r2 * iosGetRandom() - r;
        t.f[2] = r2 * iosGetRandom() - r;
        t.f[3] = 1.0f;
        vecAddXYZ(t.f, t.f, tgt->f);
    }
    vecDirection(dir, t.f, pos);
    GetQuaternionByAxisDirZY(q, dir, dir);
    SCRSetupMissile1(obj, pos, q, 4);
}
