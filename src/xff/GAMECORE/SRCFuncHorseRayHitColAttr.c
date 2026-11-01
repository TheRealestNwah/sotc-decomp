typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;
typedef int u128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirect(void *, Vec4 *, Vec4 *, void *);
extern long GetGeometryPointerCharColAttr(void *);

void SRCFuncHorseRayHitColAttr(void *obj, float fwd, float side)
{
    Vec4 pos;
    Vec4 front;
    Vec4 base;
    Vec4 end;
    Vec4 tmp;
    char buf[0x50];
    Vec4 q;
    Vec4 right;
    char *ai = GetSCRCharaAIWorkPtr(obj);
    char *ch = GetCharacterClass(obj);
    char *l = GetLayoutClass(obj);

    *(u128 *)&pos = **(u128 **)(l + 0x134);
    *(u128 *)&q = *(u128 *)(ch + 0x470);
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&front), "r"(ch + 0x470) : "memory");
    if (side != 0.0f) {
        __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                             "vmul.xyzw vf5, vf4, vf4\n"
                             "vmr32.xyzw vf6, vf4\n"
                             "vmul.xyzw vf7, vf6, vf4\n"
                             "vaddy.z vf6, vf0, vf7y\n"
                             "vsubw.z vf6, vf6, vf7w\n"
                             "vsubx.y vf6, vf0, vf5x\n"
                             "vsubz.y vf6, vf6, vf5z\n"
                             "vaddz.x vf6, vf7, vf7z\n"
                             "vsub.w vf6, vf0, vf0\n"
                             "vadd.w vf5, vf0, vf0\n"
                             "vmulw.xyz vf6, vf6, vf5w\n"
                             "vaddw.y vf6, vf6, vf0w\n"
                             "sqc2 vf6, 0x0(%0)\n"
                             : : "r"(&right), "r"(&q) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&tmp), "r"(&right), "r"(side) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&base), "r"(&pos), "r"(&tmp) : "memory");
    } else {
        *(u128 *)&base = *(u128 *)&pos;
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&tmp), "r"(&front), "r"(fwd) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&end), "r"(&base), "r"(&tmp) : "memory");
    if (ClipCollisionDirect(buf, &base, &end, gcGlobalVar + 0x234) == 1) {
        *(long *)(ai + 0x4238) = GetGeometryPointerCharColAttr(buf);
    } else {
        *(long *)(ai + 0x4238) = 0;
    }
}
