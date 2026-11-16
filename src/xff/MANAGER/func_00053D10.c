typedef int s128 __attribute__((mode(TI)));

extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);
extern void SetQuaternionByAxisRotate(float *, short, float, float, float);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern int GetRootRotStatus(void *, float *, float);
extern void EnableCharacterObjMotionRootRotDynamics(void *);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline void quatMul(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(dst) : "memory");
}

static void func_00053D10(void *obj, unsigned int *h)
{
    float buf[16];
    char *s1 = resourceData(h);
    char *cls;
    short ang;

    if (s1 != 0) {
        cls = GetCharacterClass(obj);
        ang = (short)(int)(*(float *)(s1 + 0xC) * 32768.0f / 180.0f);
        SetQuaternionByAxisRotate(&buf[4], (short)(int)((float)ang * 0.033333333f), *(float *)s1, *(float *)(s1 + 4), *(float *)(s1 + 8));
        quatMul(buf, *(float **)(cls + 0x13C), &buf[4]);
        __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                             "vsubw.x vf5, vf0, vf0w\n"
                             "vmulx.xyz vf11, vf11, vf5x\n"
                             "sqc2 vf11, 0x0(%0)\n"
                             : : "r"(&buf[8]), "r"(*(float **)(cls + 0x13C)) : "memory");
        quatMul(buf, buf, &buf[8]);
        if (*(char *)(cls + 0x529) != 0) {
            char *r = *(char **)(cls + 0x19C);
            ang = (short)(int)(*(float *)(r + 0x50) * 32768.0f / 3.14159274f);
            SetQuaternionByAxisRotateVWithNoRegularize(&buf[12], (short)(int)((float)ang * 0.033333333f), r + 0x40);
            quatMul(buf, &buf[12], buf);
        }
        *(char *)(cls + 0xA26) = GetRootRotStatus(cls + 0xA30, buf, 30.0f);
        EnableCharacterObjMotionRootRotDynamics(obj);
    }
}
