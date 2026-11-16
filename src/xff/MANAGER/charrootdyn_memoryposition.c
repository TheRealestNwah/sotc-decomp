#ifdef NONMATCHING /* 48 diffs: s4/s5 (result vs pos) swapped, buffer pointer regs v0/v1, early r copy; proto is (float t, int unused, q, pos, v) */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern void *GetCharacterClass(void);
extern void charrootdyn_getInterpPoint(float *, s128 *, float *, float);
extern void UnlinkSecureParentInfo(void *);
extern void LinkSecureParentInfoByDBPos(void *, void *, void *);
extern void SetGeometryPointerGlobalState(void *, void *, void *);

int charrootdyn_memoryposition(float t, int unused, float *q, float *pos, float *v)
{
    Vec4 buf[2];
    int r = 0;
    char *c = (char *)GetCharacterClass();
    char *a1020;
    char **pm = (char **)(c + 0x1C0);
    int m1;

    charrootdyn_getInterpPoint((float *)(c + 0x700), (s128 *)v, (float *)(c + 0x700), t);
    if ((*(unsigned int *)(*pm + 0x68) >> 25) & 1) {
        if (*(int *)(c + 0x106C) != 0)
            return r;
        if (t >= 1.0f) {
            __asm__("mfc1 %0, %1" : "=r"(m1) : "f"(-1.0f));
            __asm__ __volatile__(
                "lqc2 vf5, 0x0(%0)
"
                             "qmtc2.ni %1, vf6
"
                             "vmulx.xyz vf5, vf5, vf6x
"
                             "sqc2 vf5, 0x0(%2)
"
                             "lqc2 vf8, 0x0(%2)
"
                             "lqc2 vf18, 0x0(%3)
"
                             "vmove.w vf18, vf0
"
                             "vaddw.xyz vf12, vf0, vf0w
"
                             "lqc2 vf11, 0x0(%4)
"
                             "vmr32.w vf14, vf0
"
                             "vmr32.w vf15, vf0
"
                             "vmr32.w vf16, vf0
"
                             "vopmula.xyz ACC, vf11, vf12
"
                             "vmadd.xyz vf11, vf0, vf0
"
                             "vmadd.xyz vf10, vf11, vf12
"
                             "vmul.xyz vf13, vf11, vf10
"
                             "vopmula.xyz ACC, vf11, vf10
"
                             "vmaddw.xyz vf15, vf10, vf11w
"
                             "vmsubw.xyz vf16, vf10, vf11w
"
                             "vopmula.xyz ACC, vf13, vf12
"
                             "vmadd.xyz vf17, vf13, vf12
"
                             "vopmula.xyz ACC, vf15, vf12
"
                             "vmadd.xyz vf15, vf0, vf0
"
                             "vsub.xyz vf14, vf12, vf17
"
                             "vmove.yz vf17, vf14
"
                             "vmove.y vf14, vf16
"
                             "vmove.y vf16, vf15
"
                             "vmove.y vf15, vf17
"
                             "vmove.z vf14, vf15
"
                             "vmove.z vf15, vf16
"
                             "vmove.z vf16, vf17
"
                             "vmulax.xyzw ACC, vf14, vf8x
"
                             "vmadday.xyzw ACC, vf15, vf8y
"
                             "vmaddaz.xyzw ACC, vf16, vf8z
"
                             "vmaddw.xyzw vf10, vf18, vf8w
"
                             "sqc2 vf10, 0x0(%5)
"
                : : "r"(v), "r"(m1), "r"(&buf[1]), "r"(pos), "r"(q), "r"(buf) : "memory");
            r = 1;
            a1020 = c + 0x1020;
            if (*(int *)(c + 0x124) != 0 && (unsigned int)(*(int *)(c + 0xF0) - 2) < 2u) {
                UnlinkSecureParentInfo(a1020);
                LinkSecureParentInfoByDBPos(a1020, c + 0xC0, buf);
                return r;
            }
            SetGeometryPointerGlobalState(a1020, q, buf);
            *(int *)(c + 0x106C) = 1;
        }
        return r;
    }
    UnlinkSecureParentInfo(c + 0x1020);
    return r;
}
#endif
