typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char XUnitVector[];
extern char YUnitVector[];
extern char *GetScriptCharacterClass(int);
extern char *GetLayoutClass(int);
extern char *GetCollisionDBPlane(char *);
extern void AI_GetNegaVector(void *, void *);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);

static inline void quatRotateVector(Vec4 *out0, float *quat0, Vec4 *vec0)
{
    register Vec4 *vec __asm__("$2") = vec0;
    register Vec4 *out __asm__("$4") = out0;
    register float *quat __asm__("$3") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
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
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}


/* Matched via the permuter: the second rotate sits in a do { } while (0), which changes how gcc orders its
   address setup (lui / lo-addiu / out / quat). */
static void gextailUpdateQuat(int obj)
{
    char sp[0x40] __attribute__((aligned(16)));
    char *s1;
    char *lc;
    float dot;
    char *n;

    s1 = *(char **)(GetScriptCharacterClass(obj) + 0x1200);
    lc = GetLayoutClass(obj);
    if (*(int *)(lc + 0x124) != 0) {
        n = GetCollisionDBPlane(lc + 0xC0);
        *(s128 *)sp = *(s128 *)n;
    } else {
        if (*(int *)(s1 + 0x2C) == 0)
            return;
        *(s128 *)sp = *(s128 *)(s1 + 0x40);
    }
    quatRotateVector((Vec4 *)(sp + 0x20), (float *)(s1 + 0x70), (Vec4 *)XUnitVector);
    do {
        quatRotateVector((Vec4 *)(sp + 0x30), (float *)(s1 + 0x70), (Vec4 *)YUnitVector);
    } while (0);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vopmula.xyz ACC, vf5, vf6
"
                         "vopmsub.xyz vf7, vf6, vf5
"
                         "vsub.w vf7, vf7, vf7
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(sp + 0x10), "r"(sp + 0x20), "r"(sp) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(sp + 0x10) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vaddw.x vf7, vf0, vf0w
"
                         "vmul.xyz vf6, vf5, vf6
"
                         "vaddax.x ACC, vf0, vf6x
"
                         "vmadday.x ACC, vf7, vf6y
"
                         "vmaddz.x vf6, vf7, vf6z
"
                         "qmfc2.ni $2, vf6
"
                         "mtc1 $2, %0
"
                         : "=f"(dot) : "r"(sp), "r"(sp + 0x30) : "$2");
    if (dot < 0.0f) {
        AI_GetNegaVector(sp + 0x10, sp + 0x10);
        AI_GetNegaVector(sp, sp);
    }
    GetQuaternionByAxisDirZY(s1 + 0x60, sp + 0x10, sp);
}
