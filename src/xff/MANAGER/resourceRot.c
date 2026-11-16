#ifdef NONMATCHING /* parked draft: 128 diffs, VU0 runs in place */
typedef int s128 __attribute__((mode(TI)));

extern float XUnitVector[4];
extern float YUnitVector[4];
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);
extern void MultiGlobalQuaternionToRootSkeleton(int, float *, int);

void resourceRot(int root, float *v1, float *v2, int mode, int extra)
{
    float q[4];
    float m[16];
    float r1[4];
    float r2[4];
    float *pq;
    float *pq2;
    float *pm;
    float *pz;
    int ang;

    ang = 0;
    if (mode != 0) {
        switch (mode) {
        case 1:
        case 3:
            ang = 0x4000;
            break;
        case 2:
            ang = -0x4000;
            break;
        }
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n"
                             : : "r"(q) : "memory");
        SetQuaternionByAxisRotateVWithNoRegularize(r1, (short)-ang, XUnitVector);
        pq = q;
        pq2 = q;
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
                         "sqc2 vf13, 0x0(%2)\n"
                             : : "r"(pq), "r"(r1), "r"(pq2) : "memory");
        if (mode == 3) {
            SetQuaternionByAxisRotateVWithNoRegularize(r2, -0x8000, YUnitVector);
            pq = q;
            pq2 = q;
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
                         "sqc2 vf13, 0x0(%2)\n"
                             : : "r"(pq), "r"(r2), "r"(pq2) : "memory");
        }
        __asm__ __volatile__("addiu %0, $29, 0x10" : "=r"(pm));
        __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "sqc2 vf14, 0x0(%1)\n"
                         "sqc2 vf15, 0x10(%1)\n"
                         "sqc2 vf16, 0x20(%1)\n"
                             : : "r"(q), "r"(pm) : "memory");
        __asm__ __volatile__("addiu %0, $29, 0x40" : "=r"(pz));
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n"
                             : : "r"(pz) : "memory");
        if (v1 != 0) {
        __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                             : : "r"(v1), "r"(pm) : "memory");
        }
        if (v2 != 0) {
        __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                             : : "r"(v2), "r"(pm) : "memory");
        }
        if (root != 0)
            MultiGlobalQuaternionToRootSkeleton(root, q, extra);
    }
}
#endif
