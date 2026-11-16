#ifdef NONMATCHING /* 44 diffs (128 vs 131 words): sp+0x20 address reload/rematerialization in the a2 branch, flag lifetimes; volatile pointer read forces the 0x134 reload */
typedef int s128 __attribute__((mode(TI)));
typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern char *GetLayoutClass(void *);
extern void SetGeometryPointerGlobalState(void *, void *, void *);
extern void GetGeometryPointerQuatPos(void *, void *);
extern void *GetGeometryPointerObject(void *);
extern unsigned char IdentityQuaternion[];
extern unsigned char ZeroPoint[];

int UnparentLayoutObj(void *obj, float *a1, float *a2)
{
    s128 buf[3];
    char *c = GetLayoutClass(obj);
    char *s3;
    char *c2;
    void *o2;
    int v1;
    int flag;
    int ret = 0;

    v1 = *(int *)(c + 0x124);
    if (v1 != 0) {
        if (*(char **)(c + 0x19C) != 0) {
            *(*(char **)(c + 0x19C) + 0x8C) = 0;
            v1 = *(int *)(c + 0x124);
        }
        s3 = c + 0xC0;
        if (v1 != 0) {
            GetGeometryPointerQuatPos(buf, s3);
            **(s128 **)(c + 0x134) = buf[1];
            if (a1 != 0) {
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                     "lqc2 vf6, 0x0(%1)\n"
                                     "vadd.xyz vf5, vf5, vf6\n"
                                     "sqc2 vf5, 0x0(%0)\n"
                                     : : "r"(*(float * volatile *)(c + 0x134)), "r"(a1) : "memory");
            }
            __asm__ __volatile__("lqc2 vf11, 0x0(%2)\n"
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
                                 : : "r"(*(float **)(c + 0x13C)), "r"(c + 0x60), "r"(buf) : "memory");
            if (a2 != 0) {
                __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                                     "vaddw.xyz vf12, vf0, vf0w\n"
                                     "lqc2 vf11, 0x0(%0)\n"
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
                                     "sqc2 vf10, 0x0(%1)\n"
                                     : : "r"(*(float **)(c + 0x13C)), "r"(&buf[2]), "r"(a2) : "memory");
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                     "lqc2 vf6, 0x0(%1)\n"
                                     "vadd.xyz vf5, vf5, vf6\n"
                                     "sqc2 vf5, 0x0(%0)\n"
                                     : : "r"(*(float **)(c + 0x134)), "r"(&buf[2]) : "memory");
            }
            o2 = GetGeometryPointerObject(s3);
            flag = 0;
            if (o2 != 0) {
                c2 = GetLayoutClass(o2);
                if (c2 != 0) {
                    if (*(char **)(c2 + 0x19C) != 0) {
                        if (*(*(char **)(c2 + 0x19C) + 0x8C) != 0) {
                            **(s128 **)(c + 0x138) = **(s128 **)(c + 0x134);
                            flag = 1;
                        } else {
                            flag = 0;
                        }
                    }
                }
            }
            if (flag != 0) {
                if (*(char **)(c + 0x19C) != 0)
                    *(*(char **)(c + 0x19C) + 0x8C) = 1;
            }
        }
        SetGeometryPointerGlobalState(s3, IdentityQuaternion, ZeroPoint);
        *(int *)(c + 0x124) = 0;
        DeleteTwoWayLink((Link *)(c + 0x100));
        ret = 1;
    }
    return ret;
}
#endif
