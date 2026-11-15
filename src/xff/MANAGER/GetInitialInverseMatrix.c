#ifdef NONMATCHING /* parked draft: 133 diffs, VU0 runs in place; original keeps All1Vector/idx/dst base in s2/s3/s5 (loop-like) */
typedef int s128 __attribute__((mode(TI)));

extern float IdentityQuaternion[4];
extern float All1Vector[4];
extern void SetCurrentQuaternion(float *);
extern void MultiCurrentQuaternion(float *);
extern void iosUnitCurrentMatrix(void);
extern void iosPushCurrentMatrix(void);
extern void iosPopCurrentMatrix(void);
extern void iosTransCurrentMatrix(float *);
extern void iosMulCurrentMatrixR(float *);
extern void iosGetCurrentMatrix(float *);
extern void func_0003D828(int, int, void *);

void GetInitialInverseMatrix(int a0, void *a1)
{
    float cur[16];
    float tmp[16];
    float trans[4];
    float *base;
    float *q;
    float *s;
    float *dst;
    int next;
    int child;
    int idx = 0;
    float *pa;
    register float *pr __asm__("$3");
    register float *pz __asm__("$2");
    register float *pt __asm__("$4");

    SetCurrentQuaternion(IdentityQuaternion);
    iosUnitCurrentMatrix();
    base = *(float **)((char *)a1 + 8);
    q = base + 8;
    child = *(int *)((char *)base + 0x34);
    iosPushCurrentMatrix();
    next = *(int *)((char *)base + 0x30);
    MultiCurrentQuaternion(q);
    s = base + 4;
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(q) : "memory");
    __asm__ __volatile__("addiu %0, $29, 0x40" : "=r"(pr));
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
                         : : "r"(q), "r"(pr) : "memory");
    __asm__ __volatile__("addiu %0, $29, 0x70" : "=r"(pz));
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(pz) : "memory");
    __asm__ __volatile__("addiu %0, $29, 0x80" : "=r"(pt));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(s), "r"(All1Vector), "r"(pt) : "memory");
    trans[3] = 1.0f;
    dst = (float *)(a0 + idx * 64);
    iosTransCurrentMatrix(trans);
    iosMulCurrentMatrixR(tmp);
    iosGetCurrentMatrix(cur);
    __asm__ __volatile__("addiu %0, $29, 0" : "=r"(pa));
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(pa) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
    if (next != -1)
        func_0003D828(next, a0, a1);
    iosPopCurrentMatrix();
    if (child != -1)
        func_0003D828(child, a0, a1);
}
#endif
