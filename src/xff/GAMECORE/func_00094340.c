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

static void func_00094340(void *obj, float *tgt, int node)
{
    Vec4 q;
    Vec4 pos;
    Vec4 dir;

    SCRGetCharNodePos(pos, obj, node);
    vecDirection(dir, tgt, pos);
    GetQuaternionByAxisDirZY(q, dir, dir);
    SCRSetupMissile1(obj, pos, q, 1);
}
