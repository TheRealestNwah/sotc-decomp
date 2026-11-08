typedef int s128 __attribute__((mode(TI)));
typedef struct { long long x, y; } Pair;
typedef float Vec4[4] __attribute__((aligned(16)));

extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern Vec4 YUnitVector;
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void func_00119338(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

/* Parked: 59 words differ (register assignment and scheduling after the first VU block). */
#ifdef NONMATCHING
void SCRFuncAttackCancelForOneBoneRay(void *obj, int u1, int u2, long long mask, long long ex, int u3, unsigned int *bone, int u4, unsigned int *key, float limit, float x, float y, float z)
{
    struct { char buf[0x50]; Pair held; Vec4 p70; Vec4 v80; Vec4 q90; Vec4 a0; Vec4 b0; } L;
    char *node;
    char *res;
    float *pq;
    float *pp;

    unsigned int *k = key;
    L.held.x = mask;
    L.held.y = ex;
    L.v80[0] = x;
    L.v80[1] = y;
    L.v80[2] = z;
    L.v80[3] = 1.0f;
    node = dldResolve(bone);
    pp = L.p70;
    pq = L.q90;
    GetMotionNodeQuaternionPos(pq, pp, obj, *(int *)(node + 8), 1);
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf18, 0x0(%0)\n"
                         "vmove.w vf18, vf0\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%1)\n"
                         : : "r"(pp), "r"(L.v80), "r"(pq) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.a0), "r"(YUnitVector), "r"(limit), "r"(L.v80) : "memory");
    L.a0[3] = 1.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.b0), "r"(YUnitVector), "r"(-limit), "r"(L.v80) : "memory");
    L.b0[3] = 1.0f;
    if (ClipCollisionDirectCallBack(L.buf, L.a0, L.b0, gcGlobalVar + 0x238, 0, 0, 0, func_00119338, &L.held) != 0) {
        res = dldResolve(k);
        if (res != 0)
            CharaCtrlSetScriptCtrlStatus(obj, *(int *)(res + 4));
    }
}
#else
extern void SCRFuncAttackCancelForOneBoneRay(void *obj, int u1, int u2, long long mask, long long ex, int u3, unsigned int *bone, int u4, unsigned int *key, float limit, float x, float y, float z);
#endif
