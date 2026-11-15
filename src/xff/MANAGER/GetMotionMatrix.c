#ifdef NONMATCHING /* parked draft: 204 diffs, VU0 runs in place, wrapper over func_0003D300/func_0003D508 */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void SetCurrentQuaternion(float *);
extern void PushQuaternion(void);
extern void PopQuaternion(void);
extern float *GetCurrentQuaternion(void);
extern void iosUnitCurrentMatrix(void);
extern void iosPushCurrentMatrix(void);
extern void iosPopCurrentMatrix(void);
extern void iosTransCurrentMatrix(float *);
extern void iosMulCurrentMatrixR(float *);
extern void iosGetCurrentMatrix(float *);
extern void MultiCurrentQuaternion(float *);
extern float IdentityQuaternion[4];
extern void func_0003D300(int, int, int, int, int, int);
extern void func_0003D508(int, int, int, int, int);

void GetMotionMatrix(int out, float *qout, int tree, float *qin, float *trans, float *scale)
{
    Vec4 matrix[5];
    char *node;
    int idx = 0;
    int child, sib;
    float *p;
    float *m;
    float *q;

    SetCurrentQuaternion(IdentityQuaternion);
    iosUnitCurrentMatrix();
    iosTransCurrentMatrix(trans);
    if (qout != 0) {
        node = *(char **)(tree + 8);
        sib = *(int *)(node + 0x34);
        PushQuaternion();
        iosPushCurrentMatrix();
        child = *(int *)(node + 0x30);
        MultiCurrentQuaternion(qin);
        q = qin;
        p = (float *)(node + 0x10);
        __asm__ __volatile__(
        "lqc2 vf14, 0x0(%0)\n"
            "vmul.xyzw vf15, vf14, vf14\n"
            "vaddy.x vf15, vf15, vf15y\n"
            "vaddz.x vf15, vf15, vf15z\n"
            "vaddw.x vf15, vf15, vf15w\n"
            "vrsqrt Q, vf0w, vf15x\n"
            "vwaitq\n"
            "vmulq.xyzw vf15, vf14, Q\n"
            "sqc2 vf15, 0x0(%0)\n"
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
            "sqc2 vf14, 0x0(%1)\n"
            "sqc2 vf15, 0x10(%1)\n"
            "sqc2 vf16, 0x20(%1)\n"
            : : "r"(q), "r"(matrix) : "memory");
        m = matrix[3].f;
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(m) : "memory");
        m = matrix[4].f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)
" "lqc2 vf6, 0x0(%1)
" "vmul.xyz vf5, vf5, vf6
" "sqc2 vf5, 0x0(%2)
" : : "r"(p), "r"(scale), "r"(m) : "memory");
        m[3] = 1.0f;
        iosTransCurrentMatrix(m);
        iosMulCurrentMatrixR(matrix[0].f);
        iosGetCurrentMatrix((float *)(out + idx * 64));
        q = GetCurrentQuaternion();
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)
" "vmul.xyzw vf15, vf14, vf14
" "vaddy.x vf15, vf15, vf15y
" "vaddz.x vf15, vf15, vf15z
" "vaddw.x vf15, vf15, vf15w
" "vrsqrt Q, vf0w, vf15x
" "vwaitq
" "vmulq.xyzw vf15, vf14, Q
" "sqc2 vf15, 0x0(%1)
" : : "r"(q), "r"(qout + idx * 4) : "memory");
        if (child != -1)
            func_0003D300(child, out, (int)qout, tree, (int)qin, (int)scale);
        iosPopCurrentMatrix();
        PopQuaternion();
        if (sib != -1)
            func_0003D300(sib, out, (int)qout, tree, (int)qin, (int)scale);
    } else {
        node = *(char **)(tree + 8);
        sib = *(int *)(node + 0x34);
        iosPushCurrentMatrix();
        child = *(int *)(node + 0x30);
        MultiCurrentQuaternion(qin);
        q = qin;
        p = (float *)(node + 0x10);
        __asm__ __volatile__(
        "lqc2 vf14, 0x0(%0)\n"
            "vmul.xyzw vf15, vf14, vf14\n"
            "vaddy.x vf15, vf15, vf15y\n"
            "vaddz.x vf15, vf15, vf15z\n"
            "vaddw.x vf15, vf15, vf15w\n"
            "vrsqrt Q, vf0w, vf15x\n"
            "vwaitq\n"
            "vmulq.xyzw vf15, vf14, Q\n"
            "sqc2 vf15, 0x0(%0)\n"
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
            "sqc2 vf14, 0x0(%1)\n"
            "sqc2 vf15, 0x10(%1)\n"
            "sqc2 vf16, 0x20(%1)\n"
            : : "r"(q), "r"(matrix) : "memory");
        m = matrix[3].f;
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(m) : "memory");
        m = matrix[4].f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)
" "lqc2 vf6, 0x0(%1)
" "vmul.xyz vf5, vf5, vf6
" "sqc2 vf5, 0x0(%2)
" : : "r"(p), "r"(scale), "r"(m) : "memory");
        m[3] = 1.0f;
        iosTransCurrentMatrix(m);
        iosMulCurrentMatrixR(matrix[0].f);
        iosGetCurrentMatrix((float *)(out + idx * 64));
        if (child != -1)
            func_0003D508(child, out, tree, (int)qin, (int)scale);
        iosPopCurrentMatrix();
        if (sib != -1)
            func_0003D508(sib, out, tree, (int)qin, (int)scale);
    }
}
#endif
