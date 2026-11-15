/* Parked: 137 diffs, 145 words vs 150. Leo torch script loop: tracks the layout of the sub-thread's target, and while its position is within sqrt(2) of the anchor point runs the tool-coordinate quaternion (GetMotionNodeQuaternionPosToolCoord, rotate-by-axis, VU0 quaternion multiply), turns it into a basis (30-instruction run) at the 0.65-scaled ZUnitVector point and calls torchAttached when within 1.0 of the origin point; then scrRunM(1). Frame struct: p0 +0, p1 +0x10, q20, c30, q40, q50, saved target layout at +0x60. Remaining: five words (the Original reloads the layout pointer from sp+0x60 each loop and keeps the constants in fp/f20/f21; ours rematerialises), plus register choices. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern char gcGlobalVar[];
extern Vec ZUnitVector;
extern char YUnitVector[];
extern int *ScrParam_leoTorchLimit;
extern int isysGetThisSubThread(void);
extern int SCRGetFirstObj(void *);
extern char *GetLayoutClass(int);
extern void GetMotionNodeQuaternionPosToolCoord(void *, void *, int, int, int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, int, void *);
extern void torchAttached(int, float);
extern void scrRunM(int);

#define DIST2(a, b, q)                                  \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"          \
                         "lqc2 vf6, 0x0(%2)\n"          \
                         "vsub.xyzw vf7, vf5, vf6\n"    \
                         "vmul.xyz vf7, vf7, vf7\n"     \
                         "vmulax.w ACC, vf0, vf7x\n"    \
                         "vmadday.w ACC, vf0, vf7y\n"   \
                         "vmaddz.w vf7, vf0, vf7z\n"    \
                         ".word 0x4BA703BD\n"           \
                         "vwaitq\n"                     \
                         "cfc2.ni $2, $vi22\n"          \
                         "mtc1 $2, %0\n"                \
                         : "=f"(q)                      \
                         : "r"(a), "r"(b)               \
                         : "$2", "memory")

void leoTorch(void)
{
    struct {
        Vec p0;
        Vec p1;
        Vec q20;
        Vec c30;
        Vec q40;
        Vec q50;
        char *layTg;
    } L __attribute__((aligned(16)));
    int th;
    int tg;
    char *layTh;
    float d2;
    float two = 2.0f;
    float one = 1.0f;
    int k = 0x3F266666;
    Vec *cur;

    th = isysGetThisSubThread();
    tg = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    GetLayoutClass(th);
    layTh = GetLayoutClass(tg);
    L.layTg = layTh;
    cur = &L.c30;
    L.p0.q = **(s128 **)(layTh + 0x134);
    L.p0.q = **(s128 **)(layTh + 0x134);
    for (;;) {
        L.p1.q = **(s128 **)(L.layTg + 0x134);
        DIST2(&L.p0, &L.p1, d2);
        if (d2 < two) {
            GetMotionNodeQuaternionPosToolCoord(&L.q40, &L.q20, tg, 0x10000, 1);
            SetQuaternionByAxisRotateVWithNoRegularize(&L.q50, -0x8000, YUnitVector);
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
                                 "sqc2 vf13, 0x0(%0)\n"
                                 :
                                 : "r"(&L.q40), "r"(&L.q50)
                                 : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyz vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 :
                                 : "r"(&ZUnitVector), "r"(k), "r"(cur)
                                 : "memory");
            L.c30.w = one;
            __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                                 "lqc2 vf18, 0x0(%2)\n"
                                 "vmove.w vf18, vf0\n"
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
                                 "vmaddw.xyzw vf10, vf18, vf8w\n"
                                 "sqc2 vf10, 0x0(%0)\n"
                                 :
                                 : "r"(cur), "r"(&L.q40), "r"(&L.q20)
                                 : "memory");
            DIST2(&L.p0, cur, d2);
            if (d2 < one)
                torchAttached(tg, *(float *)(ScrParam_leoTorchLimit + 1));
        }
        scrRunM(1);
    }
}
#endif
