typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int *isysGetThisSubThread(void);
extern char *GetLayoutClass(int *);
extern void *memset(void *, int, unsigned int);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern int InitCollisionFinder(void *, int, int);
extern void GetCollisionDB(void *, void *, int *, void *, void *, float);
extern int SlideCollisionFinder4D(void *, void *, void *, float, void *, int, float);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, void *);
extern void charrootdyn_getvelocity(void *, void *, void *, float);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void iosTransMatrixF(void *, void *, float, float, float);
extern void UpdateLayoutClassGeometry(char *);
extern void scrRun(void);
typedef struct { char pad[0x180]; float dt; float rate; char pad2[0xA8]; char col[1]; } GlobalVar;
extern GlobalVar gcGlobalVar;
extern char YUnitVector[];
extern float D_0017A9B8;

#define QUAT_MUL(dst, a, b)                                                                        \
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                                                    \
                         "lqc2 vf12, 0x0(%1)\n"                                                    \
                         "vmul.xyzw vf13, vf11, vf12\n"                                            \
                         "vaddy.x vf13, vf13, vf13y\n"                                             \
                         "vaddz.x vf13, vf13, vf13z\n"                                             \
                         "vsubx.w vf13, vf13, vf13x\n"                                             \
                         "vmulw.xyz vf14, vf12, vf11w\n"                                           \
                         "vmulw.xyz vf15, vf11, vf12w\n"                                           \
                         "vopmula.xyz ACC, vf12, vf11\n"                                           \
                         "vopmsub.xyz vf16, vf11, vf12\n"                                          \
                         "vadd.xyz vf13, vf14, vf15\n"                                             \
                         "vadd.xyz vf13, vf13, vf16\n"                                             \
                         "sqc2 vf13, 0x0(%2)\n"                                                    \
                         : : "r"(a), "r"(b), "r"(dst) : "memory")

void nico_balltest(void)
{
    char finder[0x20];
    Vec4 up;
    Vec4 step;
    Vec4 res[8];
    Vec4 rot;
    float spin = 0.0f;
    int *th = isysGetThisSubThread();
    char *lc = GetLayoutClass(th);
    int i;

    memset(&up, 0, 16);
    up.f[2] = 1.0f;
    UpdateLayoutClassPastSimpleGeometry(lc);
    InitCollisionFinder(finder, *th, 0x80);
    i = 300;
    while (--i != -1) {
        float dt;

        dt = gcGlobalVar.dt;
        UpdateLayoutClassPastSimpleGeometry(lc);
        *(float *)(lc + 0x34) += D_0017A9B8 * -14.6999989f * dt;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&step), "r"(lc + 0x30), "r"(dt) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(*(char **)(lc + 0x134)), "r"(*(char **)(lc + 0x134)), "r"(&step) : "memory");
        (*(Vec4 **)(lc + 0x134))->f[1] += D_0017A9B8 * -14.6999989f * 0.5f * dt * dt;
        GetCollisionDB(finder, gcGlobalVar.col, th, *(void **)(lc + 0x134), *(void **)(lc + 0x138), 0.5f);
        if (SlideCollisionFinder4D(res, *(void **)(lc + 0x138), *(void **)(lc + 0x134), 0.5f, finder, 0, 0.001f) != 0) {
            Vec4 diff;
            Vec4 q;
            float len;

            (*(Vec4 **)(lc + 0x134))->q = res[0].q;
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "sqc2 vf7, 0x0(%0)\n"
                                 : : "r"(&diff), "r"(*(char **)(lc + 0x134)), "r"(*(char **)(lc + 0x138)) : "memory");
            __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                                 "vmul.xyz vf7, vf7, vf7\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 ".word 0x4BA703BD\n"
                                 "vwaitq\n"
                                 "cfc2.ni $2, $vi22\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(len) : "r"(&diff) : "$2");
            len += len;
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "vmul.xyz vf7, vf5, vf5\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 "vrsqrt Q, vf0w, vf7w\n"
                                 "vwaitq\n"
                                 "vmulq.xyz vf5, vf5, Q\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(&diff) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vopmula.xyz ACC, vf5, vf6\n"
                                 "vopmsub.xyz vf7, vf6, vf5\n"
                                 "vsub.w vf7, vf7, vf7\n"
                                 "sqc2 vf7, 0x0(%0)\n"
                                 : : "r"(&rot), "r"(&diff), "r"(YUnitVector) : "memory");
            SetQuaternionByAxisRotateVWithNoRegularize(&q, (int)(len * 32768.0f / 3.14159262f), &rot);
            QUAT_MUL(*(char **)(lc + 0x13C), &q, *(char **)(lc + 0x13C));
            up.q = rot.q;
            spin = len * gcGlobalVar.rate;
        } else {
            SetQuaternionByAxisRotateVWithNoRegularize(&rot, (int)(spin * gcGlobalVar.dt * 32768.0f / 3.14159262f), &up);
            QUAT_MUL(*(char **)(lc + 0x13C), &rot, *(char **)(lc + 0x13C));
        }
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                             "vmul.xyzw vf15, vf14, vf14\n"
                             "vaddy.x vf15, vf15, vf15y\n"
                             "vaddz.x vf15, vf15, vf15z\n"
                             "vaddw.x vf15, vf15, vf15w\n"
                             "vrsqrt Q, vf0w, vf15x\n"
                             "vwaitq\n"
                             "vmulq.xyzw vf15, vf14, Q\n"
                             "sqc2 vf15, 0x0(%0)\n"
                             : : "r"(*(char **)(lc + 0x13C)) : "memory");
        charrootdyn_getvelocity(lc + 0x30, *(void **)(lc + 0x134), *(void **)(lc + 0x138), gcGlobalVar.rate);
        UpdateLayoutClassSimpleGeometry(lc, gcGlobalVar.rate);
        iosTransMatrixF(*(void **)(lc + 0x158), *(void **)(lc + 0x158), 0.0f, 0.5f, 0.0f);
        UpdateLayoutClassGeometry(lc);
        scrRun();
    }
}
