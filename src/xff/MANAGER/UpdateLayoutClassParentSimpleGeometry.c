typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct { s128 quat; s128 pos; } QuatPos;
extern void GetGeometryPointerQuatPos(void *, void *);
extern void *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);
#define QCOPY(dst, src) __asm__ __volatile__("lq $2, 0x0(%1)
 sq $2, 0x0(%0)
" : : "r"(dst), "r"(src) : "$2", "memory")

static inline void quatPosApply(float *out, float *quat, float *pos, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%3)\n"
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
                         : : "r"(out), "r"(quat), "r"(pos), "r"(v) : "memory");
}

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")

#ifdef NONMATCHING
/* Parked: ~100 words differ (Original keeps only $s0 live; CSE of l+0xC0 and the object pointers adds s1/s2). */
int UpdateLayoutClassParentSimpleGeometry(char *l)
{
    QuatPos qp;
    int ok;
    void *obj;
    char *lay;

    if (*(char **)(l + 0x19C) != 0)
        *(char *)(*(char **)(l + 0x19C) + 0x8C) = 0;
    if (*(int *)(l + 0x124) == 0)
        return 0;
    GetGeometryPointerQuatPos(&qp, l + 0xC0);
    QCOPY(*(char **)(l + 0x134), &qp.pos);
    QCOPY(*(char **)(l + 0x13C), &qp.quat);
    quatPosApply(*(float **)(l + 0x134), *(float **)(l + 0x13C), *(float **)(l + 0x134), (float *)(l + 0x70));
    VU_QUAT_MUL(*(float **)(l + 0x13C), &qp.quat, l + 0x60);
    ok = 0;
    obj = GetGeometryPointerObject(l + 0xC0);
    if (obj != 0) {
        lay = GetLayoutClass(obj);
        if (lay != 0) {
            char *st = *(char **)(lay + 0x19C);
            if (st != 0) {
                if (*(char *)(st + 0x8C) != 0) {
                    QCOPY(*(char **)(l + 0x138), *(char **)(l + 0x134));
                    ok = 1;
                } else
                    ok = 0;
            }
        }
    }
    if (ok == 0)
        return 0;
    if (*(char **)(l + 0x19C) != 0)
        *(char *)(*(char **)(l + 0x19C) + 0x8C) = 1;
    return 1;
}
#else
int UpdateLayoutClassParentSimpleGeometry(char *l);
#endif
