typedef int s128 __attribute__((mode(TI)));
typedef union { float f[4]; s128 q; } Vec4;
extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, void *, int, int);
extern void SendDamageLetter(void *, int, int, Vec4 *);
extern void SendDamageBoxLetter(void *, int, int, Vec4 *, Vec4 *, Vec4 *);
extern void SendDamageCylinderLetter(void *, int, int, Vec4 *, Vec4 *, Vec4 *);
extern int info[];
extern Vec4 All1Vector;
static inline void quatMatrix(void *dst0, void *q, void *t)
{
    void *dst = dst0;
    void *qq = q;
    void *tt = t;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(dst0), "r"(qq) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(tt) : "memory");
}
static inline void quatMatrix2(void *dst0, void *q, void *t)
{
    register void *tt __asm__("$2") = t;
    void *qq = q;
    void *dst = dst0;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(dst0), "r"(qq) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(tt) : "memory");
}
static inline void quatMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}
static inline void applyMatrix(void *dst, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(dst), "r"(m), "r"(v) : "memory");
}

static inline void scaleVec(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}
static inline void quatNormalize(void *dst, void *a)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(dst), "r"(a) : "memory");
}

static inline void calcNode(Vec4 *out, void *target, int node, Vec4 *v)
{
    Vec4 m[4];
    Vec4 p;
    Vec4 q;
    Vec4 *mtx;
    char *l = GetLayoutClass(target);

    if (node > 0 && !(node & 0x10000)) {
        mtx = *(Vec4 **)(l + 0x15C) + node * 4;
    } else {
        mtx = m;
        GetMotionNodeQuaternionPosToolCoord(&q, &p, target, node, 1);
        quatMatrix(m, &q, &p);
    }
    applyMatrix(out, mtx, v);
}

int updateDamageGeo(void *a0, void *obj, int node, char *geo, int power, int type)
{
    Vec4 size;
    Vec4 m[4];
    Vec4 a;
    Vec4 b;
    Vec4 v;
    Vec4 *scale = &All1Vector;
    int ret = 0;
    Vec4 *mtx;
    char *l;
    float *sf;

    if (obj) {
        l = GetLayoutClass(obj);
        if (l)
            scale = (Vec4 *)(l + 0x90);
    }
    if (type == 3) {
        Vec4 *pos = (Vec4 *)(geo + 0x10);
        if (((float *)pos)[5] > 0.001f) {
            Vec4 *out;
            scaleVec(&size, geo + 0x20, scale);
            out = *(Vec4 **)(GetLayoutClass(a0) + 0x134);
            sf = size.f;
            {
                Vec4 *mtx;
                char *l = GetLayoutClass(obj);

                if (node > 0 && !(node & 0x10000)) {
                    mtx = *(Vec4 **)(l + 0x15C) + node * 4;
                } else {
                    mtx = m;
                    { register Vec4 *bp __asm__("$4") = &b; __asm__("" : "=r"(bp) : "0"(bp)); GetMotionNodeQuaternionPosToolCoord(bp, &a, obj, node, 1); }
                    __asm__ __volatile__("" : : "r"(mtx));
                    quatMatrix(mtx, &b, &a);
                }
                applyMatrix(out, mtx, pos);
            }
            v.q = out->q;
            v.f[3] = sf[1] * 0.5f;
            ret = 1;
            SendDamageLetter(obj, info[2], power, &v);
        }
    } else {
        Vec4 *pos = (Vec4 *)(geo + 0x10);
        if (((float *)pos)[9] > 0.001f) {
            Vec4 *oq;
            Vec4 *op;
            Vec4 *gq;
            Vec4 *nq;
            Vec4 *sz;
            scaleVec(&size, geo + 0x30, scale);
            sz = &size;
            {
            char *la = GetLayoutClass(a0);
            op = *(Vec4 **)(la + 0x134);
            gq = (Vec4 *)(geo + 0x20);
            oq = *(Vec4 **)(la + 0x13C);
            }
            l = GetLayoutClass(obj);
            if (node >= 0 && (node <= 0 || !(node & 0x10000))) {
                nq = *(Vec4 **)(l + 0x154) + node;
                mtx = *(Vec4 **)(l + 0x15C) + node * 4;
            } else {
                nq = &a;
                GetMotionNodeQuaternionPosToolCoord(nq, &b, obj, node, 1);
                mtx = m;
                __asm__ __volatile__("" : : "r"(mtx));
                quatMatrix2(mtx, nq, &b);
            }
            quatMul(oq, nq, gq);
            quatNormalize(oq, oq);
            applyMatrix(op, mtx, pos);
            if (type != 10) {
                if (type == 13)
                    SendDamageBoxLetter(obj, info[2], power, op, oq, sz);
            } else
                SendDamageCylinderLetter(obj, info[2], power, op, oq, sz);
            ret = 1;
        }
    }
    return ret;
}
