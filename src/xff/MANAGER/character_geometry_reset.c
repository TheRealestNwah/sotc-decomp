typedef int s128 __attribute__((mode(TI)));
/* dst = a * b */
#define VU_MUL_MATRIX(dst, a, b) \
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "lqc2 vf24, 0x0(%2)\n" \
                         "lqc2 vf25, 0x10(%2)\n" \
                         "lqc2 vf26, 0x20(%2)\n" \
                         "lqc2 vf27, 0x30(%2)\n" \
                         "vmulax.xyzw ACC, vf14, vf24x\n" \
                         "vmadday.xyzw ACC, vf15, vf24y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf24z\n" \
                         "vmaddw.xyzw vf24, vf17, vf24w\n" \
                         "vmulax.xyzw ACC, vf14, vf25x\n" \
                         "vmadday.xyzw ACC, vf15, vf25y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf25z\n" \
                         "vmaddw.xyzw vf25, vf17, vf25w\n" \
                         "vmulax.xyzw ACC, vf14, vf26x\n" \
                         "vmadday.xyzw ACC, vf15, vf26y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf26z\n" \
                         "vmaddw.xyzw vf26, vf17, vf26w\n" \
                         "vmulax.xyzw ACC, vf14, vf27x\n" \
                         "vmadday.xyzw ACC, vf15, vf27y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf27z\n" \
                         "vmaddw.xyzw vf27, vf17, vf27w\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf27, 0x30(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

extern void UpdateLayoutClassGeometry(char *);
extern void UpdateLayoutClassPastGeometry(char *);
extern void func_00041488(char *);

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

static inline unsigned char copyRootQuaternion(char *character)
{
    return character[0x1BC] & 1;
}

static inline void updateGeometry(char *character)
{
    UpdateLayoutClassGeometry(character);
    if (character[0x1BC] & 8) {
        int i;
        for (i = 0; i < *(short *)(character + 0x1B4); ++i) {
            VU_MUL_MATRIX((void *)(i * 64 + *(int *)(character + 0x160)),
                          (void *)(i * 64 + *(int *)(character + 0x15C)),
                          (void *)(i * 64 + *(int *)(character + 0x2D8)));
        }
    }
    if (copyRootQuaternion(character))
        *(s128 *)(character + 0x450) = **(s128 **)(character + 0x154);
}

void UpdateCharacterClassGeometry(char *character)
{
    updateGeometry(character);
}

void ResetCharacterObj4DDynamicsInfo(unsigned char *object)
{
    char *character = characterClass(object);
    *(s128 *)(character + 0x500) = **(s128 **)(character + 0x138);
    UpdateLayoutClassPastGeometry(character);
    *(s128 *)(character + 0x4D0) = *(s128 *)(character + 0x4C0);
    updateGeometry(character);
    func_00041488(character);
}
