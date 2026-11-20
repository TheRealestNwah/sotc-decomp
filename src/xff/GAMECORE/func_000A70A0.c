typedef int s128 __attribute__((mode(TI)));

extern char ZUnitVector[];
extern char YUnitVector[];
extern int *ScriptCtrlDef_SCRPlayerAnimalLandHit;
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern void CharaCtrlSetOutsideScriptCtrlStatus(int, int);
extern void AI_GetRandomVelocity(void *, void *, void *, float, float, float, float);
extern void GetDifferencialQuaternionWithNoRegularize(void *, void *, void *, void *);
extern void func_000A6450(char *);

#define QMATRIX                                                 \
    "vaddw.xyz vf12, vf0, vf0w\n"                               \
    "lqc2 vf11, 0x0(%1)\n"                                      \
    "vmr32.w vf14, vf0\n"                                       \
    "vmr32.w vf15, vf0\n"                                       \
    "vmr32.w vf16, vf0\n"                                       \
    "vopmula.xyz ACC, vf11, vf12\n"                             \
    "vmadd.xyz vf11, vf0, vf0\n"                                \
    "vmadd.xyz vf10, vf11, vf12\n"                              \
    "vmul.xyz vf13, vf11, vf10\n"                               \
    "vopmula.xyz ACC, vf11, vf10\n"                             \
    "vmaddw.xyz vf15, vf10, vf11w\n"                            \
    "vmsubw.xyz vf16, vf10, vf11w\n"                            \
    "vopmula.xyz ACC, vf13, vf12\n"                             \
    "vmadd.xyz vf17, vf13, vf12\n"                              \
    "vopmula.xyz ACC, vf15, vf12\n"                             \
    "vmadd.xyz vf15, vf0, vf0\n"                                \
    "vsub.xyz vf14, vf12, vf17\n"                               \
    "vmove.yz vf17, vf14\n"                                     \
    "vmove.y vf14, vf16\n"                                      \
    "vmove.y vf16, vf15\n"                                      \
    "vmove.y vf15, vf17\n"                                      \
    "vmove.z vf14, vf15\n"                                      \
    "vmove.z vf15, vf16\n"                                      \
    "vmove.z vf16, vf17\n"

#define ROTATE(v, quat)                                         \
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n" QMATRIX          \
                         "vmulax.xyzw ACC, vf14, vf8x\n"        \
                         "vmadday.xyzw ACC, vf15, vf8y\n"       \
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"       \
                         "vmaddw.xyzw vf10, vf0, vf8w\n"        \
                         "sqc2 vf10, 0x0(%0)\n"                 \
                         :                                      \
                         : "r"(v), "r"(quat)                    \
                         : "memory")

#define NORM(v)                                        \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"         \
                         "vmul.xyz vf7, vf5, vf5\n"    \
                         "vmulax.w ACC, vf0, vf7x\n"   \
                         "vmadday.w ACC, vf0, vf7y\n"  \
                         "vmaddz.w vf7, vf0, vf7z\n"   \
                         "vrsqrt Q, vf0w, vf7w\n"      \
                         "vwaitq\n"                    \
                         "vmulq.xyz vf5, vf5, Q\n"     \
                         "sqc2 vf5, 0x0(%0)\n"         \
                         :                             \
                         : "r"(v)                      \
                         : "memory")

static void func_000A70A0(char *w)
{
    struct {
        float d1[4];
        float d2[4];
        float q[4];
    } L __attribute__((aligned(16)));
    char *cc;
    char *x;
    int v;
    float f;

    *(int *)(w + 0x7B8) = -1;
    switch (*(unsigned int *)(w + 0x274)) {
    case 0:
        break;
    case 1:
        if (*(int *)(w + 0x38) == 0) {
            f = *(float *)(*(char **)(w + 0x20) + 0x14);
            AI_GetRandomVelocity(w + 0x5D4, w + 0x2B4, w + 0x2C4, -f, f, 1.0f, 5.0f);
        }
        break;
    case 2:
    case 4:
    case 6:
        if (*(int *)(w + 0x260) != 0x1C)
            *(int *)(w + 0x298) = 0;
        break;
    case 13:
        cc = GetCharacterClass(isysGetThisSubThread());
        if (*(int *)(cc + 0xFF0) != 0)
            CharaCtrlSetOutsideScriptCtrlStatus(*(int *)(w + 0x24), ScriptCtrlDef_SCRPlayerAnimalLandHit[1]);
        /* fall through */
    case 12:
        *(int *)(w + 0x7B4) = 0;
        *(int *)(w + 0x7B8) = *(int *)(w + 0x610);
        break;
    case 9:
        if (*(int *)(w + 0x38) != 0) {
            register float *d2p __asm__("$16");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "sqc2 vf7, 0x0(%2)\n"
                                 : : "r"(w + 0x590), "r"(w + 0x5A0), "r"(L.d1) : "memory");
            d2p = L.d2;
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "sqc2 vf7, 0x0(%2)\n"
                                 : : "r"(w + 0x5B0), "r"(w + 0x590), "r"(d2p) : "memory");
            *(int *)&L.d1[1] = 0;
            *(int *)&L.d2[1] = 0;
            NORM(L.d1);
            NORM(d2p);
            GetDifferencialQuaternionWithNoRegularize(L.q, ZUnitVector, L.d1, YUnitVector);
            ROTATE(d2p, L.q);
            if (0.0f < L.d2[0])
                *(int *)(w + 0x794) = -1;
            else
                *(int *)(w + 0x794) = 1;
        } else {
            x = *(char **)(w + 0x2C);
            if (x == 0)
                break;
            *(int *)(w + 0x794) = *(int *)(x + 0x794);
        }
        break;
    }
    if (*(int *)w == 6)
        func_000A6450(w);
    cc = GetCharacterClass(isysGetThisSubThread());
    if ((unsigned int)(*(int *)(w + 0x274) - 0xC) >= 2 && *(float *)(w + 0x7B4) < 1.0f)
        goto one;
    if (*(int *)(w + 0x26C) >= 0x12) {
one:
        *(char *)(cc + 0x53C) = 1;
    } else
        *(char *)(cc + 0x53C) = 0;
}
