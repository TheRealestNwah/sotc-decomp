#ifdef NONMATCHING /* 66 diffs: word count matches (134); saved-register numbering (idx s3, node s1, quat s0) differs; sp addresses via explicit asm addiu/daddu from $29 */
static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2 $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2 $8, vf24\n"
                         "qmtc2 $9, vf25\n"
                         "qmtc2 $10, vf26\n"
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
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    float pos[4];
    float q[4];
    int child;
    int sibling;
    char pad38[0x40 - 0x38];
} TreeNode;

typedef struct {
    char pad0[8];
    TreeNode *nodes;
} Tree;

extern void iosPushCurrentMatrix(void);
extern void iosPopCurrentMatrix(void);
extern void iosTransCurrentMatrix(float *);
extern void iosMulCurrentMatrixR(float *);
extern void iosGetCurrentMatrix(float *);
extern float All1Vector[];
extern void MultiCurrentQuaternion(float *);
extern void func_0003D828(int idx, Vec4 *out, Tree *tree)
{
    Vec4 buf[9];
    TreeNode *node = (TreeNode *)((char *)tree->nodes + idx * 64);
    int sibling = node->sibling;
    float *ones = All1Vector;
    int child;
    float *q = node->q;
    float *p = node->pos;
    float *m;
    float *dst;
    float *r4;
    float *r0;
    int idx2 = idx;
    int sib;

    iosPushCurrentMatrix();
    child = node->child;
    MultiCurrentQuaternion(q);
    __asm__ __volatile__(
        "lqc2 vf14, 0x0(%0)
"
        "vmul.xyzw vf15, vf14, vf14
"
        "vaddy.x vf15, vf15, vf15y
"
        "vaddz.x vf15, vf15, vf15z
"
        "vaddw.x vf15, vf15, vf15w
"
        "vrsqrt Q, vf0w, vf15x
"
        "vwaitq
"
        "vmulq.xyzw vf15, vf14, Q
"
        "sqc2 vf15, 0x0(%0)
"
        "vaddw.xyz vf12, vf0, vf0w
"
        "lqc2 vf11, 0x0(%0)
"
        "vmr32.w vf14, vf0
"
        "vmr32.w vf15, vf0
"
        "vmr32.w vf16, vf0
"
        "vopmula.xyz ACC, vf11, vf12
"
        "vmadd.xyz vf11, vf0, vf0
"
        "vmadd.xyz vf10, vf11, vf12
"
        "vmul.xyz vf13, vf11, vf10
"
        "vopmula.xyz ACC, vf11, vf10
"
        "vmaddw.xyz vf15, vf10, vf11w
"
        "vmsubw.xyz vf16, vf10, vf11w
"
        "vopmula.xyz ACC, vf13, vf12
"
        "vmadd.xyz vf17, vf13, vf12
"
        "vopmula.xyz ACC, vf15, vf12
"
        "vmadd.xyz vf15, vf0, vf0
"
        "vsub.xyz vf14, vf12, vf17
"
        "vmove.yz vf17, vf14
"
        "vmove.y vf14, vf16
"
        "vmove.y vf16, vf15
"
        "vmove.y vf15, vf17
"
        "vmove.z vf14, vf15
"
        "vmove.z vf15, vf16
"
        "vmove.z vf16, vf17
"
        "sqc2 vf14, 0x0(%1)
"
        "sqc2 vf15, 0x10(%1)
"
        "sqc2 vf16, 0x20(%1)
"
        : : "r"(q), "r"(&buf[4]) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(&buf[7]) : "memory");
    m = buf[8].f;
    __asm__ __volatile__(
        "lqc2 vf5, 0x0(%0)
"
        "lqc2 vf6, 0x0(%1)
"
        "vmul.xyz vf5, vf5, vf6
"
        "sqc2 vf5, 0x0(%2)
"
        : : "r"(p), "r"(ones), "r"(m) : "memory");
    m[3] = 1.0f;
    dst = (float *)((char *)out + idx2 * 64);
    iosTransCurrentMatrix(m);
    __asm__ __volatile__("addiu %0, $29, 0x40" : "=r"(r4));
    iosMulCurrentMatrixR(r4);
    __asm__ __volatile__("daddu %0, $29, $0" : "=r"(r0));
    iosGetCurrentMatrix(r0);
    matInverse(dst, r0);
    if (child != -1)
        func_0003D828(child, out, tree);
    iosPopCurrentMatrix();
    sib = sibling;
    if (sib == -1)
        return;
    func_0003D828(sib, out, tree);
}
#endif
