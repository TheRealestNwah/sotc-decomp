typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char XUnitVector[];
extern int ControlMode_NAMAZU_DEFAULT, ControlMode_NAMAZU_MOVE, ControlMode_NAMAZU_TURN, ControlMode_NAMAZU_DEATH;
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern int AI_PlayerParentFlag(int, int);
extern void func_000B78C8(char *);
extern void AI_GetSmallAnimalAIParam(void *, void *, void *, void *, void *, void *);

static inline void quatRotateVector(Vec4 *out, float *quat, Vec4 *vec)
{
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

static void func_000BA290(char *w)
{
    register char *a0 __asm__("$4");
    int th = isysGetThisSubThread();
    char *tl = GetLayoutClass(*(int *)(w + 0x40));
    char *lc = GetLayoutClass(th);
    char *cc = GetCharacterClass(th);
    char *ndir;
    char *conj;
    char *dirq;
    int mode;
    int c;
    float len;
    register int b __asm__("$3");

    if (AI_PlayerParentFlag(th, *(int *)(w + 0x40)) != 0) {
        char *d = *(char **)(w + 0x64);
        *(int *)(w + 0x2F4) = 1;
        *(float *)(w + 0x2FC) = *(float *)(d + 0xB8);
        *(float *)(w + 0x2F8) = *(float *)(d + 0xBC);
        *(float *)(w + 0x300) = *(float *)(d + 0xC0);
    } else {
        *(int *)(w + 0x2F4) = 0;
        *(float *)(w + 0x2FC) = 0.0f;
        *(float *)(w + 0x2F8) = 1.0f;
        *(float *)(w + 0x300) = 1.0f;
    }
    mode = *(int *)(GetCharacterClass(isysGetThisSubThread()) + 0x750);
    if (mode == ControlMode_NAMAZU_DEFAULT)
        c = 0x21;
    else if (mode == ControlMode_NAMAZU_MOVE)
        c = 0x22;
    else if (mode == ControlMode_NAMAZU_TURN)
        c = 0x23;
    else
        c = (mode == ControlMode_NAMAZU_DEATH) ? 0x25 : 0x21;
    *(int *)(w + 0x150) = c;
    quatRotateVector((Vec4 *)(w + 0x130), (float *)*(char **)(lc + 0x13C), (Vec4 *)XUnitVector);
    *(s128 *)(w + 0x140) = *(s128 *)(w + 0x130);
    ndir = w + 0x140;
    __asm__ __volatile__("" : : : "memory");
    *(int *)(w + 0x144) = 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(ndir) : "memory");
    conj = w + 0x1B0;
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%1)\n"
                         : : "r"(*(char **)(lc + 0x13C)), "r"(conj) : "memory");
    dirq = w + 0x130;
    AI_GetSmallAnimalAIParam(w + 0x70, *(char **)(tl + 0x134), *(char **)(lc + 0x134), conj, dirq, ndir);
    AI_GetSmallAnimalAIParam(w + 0xD0, w + 0x20, *(char **)(lc + 0x134), conj, dirq, ndir);
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(tl + 0x30) : "$2");
    *(float *)(w + 0x1A0) = len;
    __asm__ __volatile__("" : : : "memory");
    /* The call argument and the 0x362 byte are pinned to $a0 and $v1, as in the Original. */
    a0 = w;
    __asm__ __volatile__("" : "+r"(a0) : : "memory");
    *(int *)(w + 0x244) = *(int *)(cc + 0xFF0);
    b = *(signed char *)(cc + 0x362);
    __asm__("" : "+r"(b));
    *(int *)(w + 0x248) = b;
    if (b != 0) {
        *(float *)(w + 0x24C) = *(float *)(cc + 0x10C8);
    }
    func_000B78C8(a0);
}
