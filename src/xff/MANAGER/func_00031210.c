typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern void GetCharacterClassOptionNodeGeo(Vec4 *, Vec4 *, Vec4 *, char *, int, int);
extern void GetCharacterClassNodeQuaternionPos(Vec4 **, Vec4 **, char *, int, int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(Vec4 *, int, Vec4 *);
extern Vec4 ZeroPoint;
extern Vec4 IdentityQuaternion;
extern Vec4 YUnitVector;

static void func_00031210(Vec4 *q, Vec4 *pos, Vec4 *opt, int id, int node, int e)
{
    Vec4 rot;
    Vec4 *qp;
    Vec4 *pp;
    char *cls = 0;
    char *cc = GetCharacterClass(id);

    if (cc != 0) {
        if (node > 0 && (node & 0x10000)) {
            GetCharacterClassOptionNodeGeo(q, pos, opt, cc, node & ~0x10000, e);
        } else {
            cls = cc;
            switch (node) {
            case -2:
                pos->q = (*(Vec4 **)(cls + 0x134))->q;
                q->q = (*(Vec4 **)(cls + 0x13C))->q;
                break;
            case -1:
                pos->q = (cls != 0 ? (Vec4 *)(cls + 0x460) : &ZeroPoint)->q;
                q->q = (cc != 0 ? *(Vec4 **)(cc + 0x13C) : &IdentityQuaternion)->q;
                break;
            case -3:
                pos->q = (*(Vec4 **)(cls + 0x134))->q;
                q->q = ((Vec4 *)(cls + 0x470))->q;
                SetQuaternionByAxisRotateVWithNoRegularize(&rot, -0x8000, &YUnitVector);
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
                                     : : "r"(q), "r"(&rot) : "memory");
                break;
            default:
                GetCharacterClassNodeQuaternionPos(&qp, &pp, cls, node, e);
                pos->q = pp->q;
                q->q = qp->q;
                break;
            }
        }
    } else {
        cls = GetLayoutClass(id);
        q->q = (*(Vec4 **)(cls + 0x13C))->q;
        pos->q = (*(Vec4 **)(cls + 0x134))->q;
    }
    if (opt != 0 && cls != 0) {
        opt->q = ((Vec4 *)(cls + 0x90))->q;
    }
}
