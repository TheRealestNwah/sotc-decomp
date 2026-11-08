typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));

extern char *D_00136C00;
extern void globalLightCalcLightNum(void *, int);
extern void CalcColorParamDistantLight(void *);
extern void CalcColorParamAmbientLight(void *);
extern void GetQuaternionByDegEulerYXZ(void *, float, float, float);
extern void ExchangeLWQuaternion(void *, void *);
extern void *memset(void *, int, unsigned int);

/* Parked: ~76 words differ (switch/branch layout and the order of the s128 copy against the float swap). */
#ifdef NONMATCHING
void InitStageLightColMan(s128 *q, float *col, int type)
{
    struct { Vec4 v0; Vec4 v10; } L;
    char *base = D_00136C00;
    char *s0 = base + 0xF0;
    char *other;
    int flag;
    float t0;
    float t1;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.v0), "r"(col), "r"(255.0f) : "memory");
    *(s128 *)L.v10 = *q;
    t0 = L.v10[1];
    t1 = L.v10[0];
    t0 = -t0;
    L.v10[1] = t1;
    L.v10[0] = t0;
    switch (type) {
    case 0:
        globalLightCalcLightNum(s0, 0x1A);
        *(int *)(s0 + 0x110) |= 0x40;
        *(float *)(s0 + 0x24) = 1.0f;
        *(s128 *)(s0 + 0x10) = *(s128 *)L.v0;
        CalcColorParamDistantLight(s0);
        GetQuaternionByDegEulerYXZ(s0, L.v10[0], L.v10[1], L.v10[2]);
        ExchangeLWQuaternion(s0, s0);
        *(int *)(s0 + 0x2C) |= 0x40000;
        break;
    case 1:
        globalLightCalcLightNum(s0, 0x1A);
        other = base + 0x130;
        flag = *(int *)(s0 + 0x110) | 0x80;
        goto tail;
    case 2:
        globalLightCalcLightNum(s0, 0x1A);
        other = base + 0x170;
        flag = *(int *)(s0 + 0x110) | 0x100;
    tail:
        *(int *)(s0 + 0x110) = flag;
        *(float *)(other + 0x24) = 1.0f;
        *(s128 *)(other + 0x10) = *(s128 *)L.v0;
        CalcColorParamDistantLight(other);
        GetQuaternionByDegEulerYXZ(other, L.v10[0], L.v10[1], L.v10[2]);
        ExchangeLWQuaternion(other, other);
        break;
    case 3:
        memset(s0, 0, 0x150);
        *(float *)(s0 + 0x11C) = 1.0f;
        *(int *)(s0 + 0x110) |= 0x40000;
        globalLightCalcLightNum(s0, 0x19);
        *(float *)(s0 + 0x12C) = 1.0f;
        *(s128 *)(s0 + 0x100) = *(s128 *)L.v0;
        CalcColorParamAmbientLight(s0);
        break;
    }
}
#else
extern void InitStageLightColMan(s128 *q, float *col, int type);
#endif
