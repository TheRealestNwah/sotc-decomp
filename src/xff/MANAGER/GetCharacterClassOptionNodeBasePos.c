typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

static inline void loadPoint(void *point, void *position)
{
    __asm__ __volatile__("lqc2 vf08, 0x0(%0)\n"
                         "lqc2 vf18, 0x0(%1)\n"
                         "vmove.w vf18, vf00\n"
                         : : "r"(point), "r"(position));
}

static inline void quatMatrix(void *quaternion)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%0)\n"
                         "vmr32.w vf14, vf00\n"
                         "vmr32.w vf15, vf00\n"
                         "vmr32.w vf16, vf00\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf00, vf00\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf00, vf00\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         : : "r"(quaternion));
}

static inline void applyPoint(void *out)
{
    __asm__ __volatile__("vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf18, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out));
}

static inline void mulXYZ(void *v, void *s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s));
}

static inline void prepareTransform(void *quaternion, void *position, void *point)
{
    loadPoint(point, position);
    quatMatrix(quaternion);
}

static inline void transformPoint(void *out, void *quaternion, void *position, void *point)
{
    prepareTransform(quaternion, position, point);
    applyPoint(out);
}

extern int GetMotionOptionNodeParentId(void *, int);
extern void GetCharacterClassOptionNodeLocalQuaternionPos(Vec4 *, Vec4 *, char *, int, int);
extern void GetMotionNodeBaseQuaternion(Vec4 *, void *, void *, int);
extern void GetMotionNodeBasePos(Vec4 *, void *, void *, int);

void GetCharacterClassOptionNodeBasePos(Vec4 *out, void *motion, Vec4 *pos, Vec4 *quat, char *cls, int node)
{
    Vec4 lq;
    Vec4 lp;
    Vec4 q;
    Vec4 p;
    Vec4 *scale = (Vec4 *)(cls + 0x90);
    int parent;

    parent = GetMotionOptionNodeParentId(*(void **)(cls + 0x358), node);
    GetCharacterClassOptionNodeLocalQuaternionPos(&lq, &lp, cls, node, 1);
    if (parent < 0) {
        mulXYZ(&lp, scale);
        prepareTransform(quat, pos, &lp);
    } else {
        GetMotionNodeBaseQuaternion(&q, *(void **)(cls + 0x358), motion, parent);
        GetMotionNodeBasePos(&p, *(void **)(cls + 0x358), motion, parent);
        transformPoint(out, &q, &p, &lp);
        mulXYZ(out, scale);
        prepareTransform(quat, pos, out);
    }
    applyPoint(out);
}
