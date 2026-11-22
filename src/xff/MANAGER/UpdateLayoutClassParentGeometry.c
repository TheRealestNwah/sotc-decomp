typedef int s128 __attribute__((mode(TI)));
typedef struct { s128 quat; s128 pos; } QuatPos;
typedef union { s128 q; char *p[4]; } QU;
extern void GetGeometryPointerQuatPos(void *, void *);
extern void *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);

#define VU_ADD_XYZ(dst, v) \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n" \
                         "lqc2 vf6, 0x0(%1)\n" \
                         "vadd.xyz vf5, vf5, vf6\n" \
                         "sqc2 vf5, 0x0(%0)\n" \
                         : : "r"(dst), "r"(v) : "memory")

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%1)
"                          "lqc2 vf12, 0x0(%2)
"                          "vmul.xyzw vf13, vf11, vf12
"                          "vaddy.x vf13, vf13, vf13y
"                          "vaddz.x vf13, vf13, vf13z
"                          "vsubx.w vf13, vf13, vf13x
"                          "vmulw.xyz vf14, vf12, vf11w
"                          "vmulw.xyz vf15, vf11, vf12w
"                          "vopmula.xyz ACC, vf12, vf11
"                          "vopmsub.xyz vf16, vf11, vf12
"                          "vadd.xyz vf13, vf14, vf15
"                          "vadd.xyz vf13, vf13, vf16
"                          "sqc2 vf13, 0x0(%0)
"                          : : "r"(dst), "r"(a), "r"(b) : "memory")

static inline void quatRotate(float *out, float *quat, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
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
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(quat), "r"(v));
}

int UpdateLayoutClassParentGeometry(char *l, float *offset, float *local)
{
    QuatPos qp;
    s128 tmp;
    int ok;
    void *obj;
    char *lay;

    if (*(char **)(l + 0x19C) != 0)
        *(char *)(*(char **)(l + 0x19C) + 0x8C) = 0;
    if (*(int *)(l + 0x124) != 0) {
        GetGeometryPointerQuatPos(&qp, l + 0xC0);
        (*(QU **)(l + 0x134))->q = qp.pos;
        if (offset != 0)
            VU_ADD_XYZ(*(char **)(l + 0x134), offset);
        VU_QUAT_MUL(*(char **)(l + 0x13C), &qp.quat, l + 0x60);
        if (local != 0) {
            quatRotate((float *)&tmp, *(float **)(l + 0x13C), local);
            {
                register char *d asm("$2") = *(char **)(l + 0x134);
                register s128 *t asm("$3") = &tmp;
                VU_ADD_XYZ(d, t);
            }
        }
        obj = GetGeometryPointerObject(l + 0xC0);
        if (obj != 0) {
            lay = GetLayoutClass(obj);
            if (lay != 0) {
                char *st = *(char **)(lay + 0x19C);
                if (st != 0) {
                    if (*(char *)(st + 0x8C) != 0) {
                        **(s128 **)(l + 0x138) = **(s128 **)(l + 0x134);
                        ok = 1;
                    } else
                        ok = 0;
                } else
                    ok = 0;
            } else
                ok = 0;
        } else
            ok = 0;
        if (ok != 0) {
            if (*(char **)(l + 0x19C) != 0)
                *(char *)(*(char **)(l + 0x19C) + 0x8C) = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}
