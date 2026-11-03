extern int *DldSysUndefSymbol;
extern char IdentityQuaternion[], YUnitVector[];
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern void SetObjectGeo(void *, float *, float *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")

static inline void quatMul(float *d, float *a, float *b)
{
    VU_QUAT_MUL(d, a, b);
}

static inline void rotQuatY(float *d, float *a, int ang)
{
    float r[4] __attribute__((aligned(16)));

    SetQuaternionByAxisRotateVWithNoRegularize(r, ang, YUnitVector);
    quatMul(d, a, r);
}

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void SCRFuncSetGeoAndSendKey(void *obj, int a1, int a2, int a3, int a4, int a5, int a6, int a7, unsigned int *h,
                             float x, float y, float z, float deg)
{
    float pos[4] __attribute__((aligned(16)));
    float q2[4] __attribute__((aligned(16)));
    char *e;

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    pos[3] = 1.0f;
    rotQuatY(q2, (float *)IdentityQuaternion, -((int)(deg * 32768.0f / 180.0f) << 16) >> 16);
    SetObjectGeo(obj, q2, pos);
    e = dldElem(h);
    if (e != 0)
        CharaCtrlSetScriptCtrlStatus(obj, *(int *)(e + 4));
}
