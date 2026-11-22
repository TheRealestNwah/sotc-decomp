#ifdef NONMATCHING /* Parked: 1 diff (was 3; zero-store pointer pinned to v0). Remaining: the permuter shape reads an uninitialized sib (sp+0x54) where the Original reloads the spilled sibling (sp+0x50); reading sibling directly hoists the sibling call args above the beq (21 diffs). */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    float pos[4];
    char pad20[0x30 - 0x20];
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
extern void MultiCurrentQuaternion(float *);
extern void func_0003D508(int idx, Vec4 *out, Tree *tree, Vec4 *quats, Vec4 *scale);

void func_0003D508(int idx, Vec4 *out, Tree *tree, Vec4 *quats, Vec4 *scale)
{
    Vec4 matrix[5];
    TreeNode *node = (TreeNode *)((char *)tree->nodes + idx * 64);
    volatile int sibling = node->sibling;
    int child;
    float *q = (float *)((idx << 4) + (int)quats);
    float *p = node->pos;
    float *m;
    int sib;
    int idx2 = idx;

    iosPushCurrentMatrix();
    child = node->child;
    MultiCurrentQuaternion(q);
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
    { register float *z asm("$2") = matrix[3].f; __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(z) : "memory"); }
    m = matrix[4].f;
    __asm__ __volatile__(
        "lqc2 vf5, 0x0(%0)\n"
        "lqc2 vf6, 0x0(%1)\n"
        "vmul.xyz vf5, vf5, vf6\n"
        "sqc2 vf5, 0x0(%2)\n"
        : : "r"(p), "r"(scale), "r"(m) : "memory");
    m[3] = 1.0f;
    iosTransCurrentMatrix(m);
    iosMulCurrentMatrixR(matrix[0].f);
    __asm__("" : "+r"(idx2));
    iosGetCurrentMatrix((float *)((char *)out + idx2 * 64));
    if (child != -1)
        func_0003D508(child, out, tree, quats, scale);
    iosPopCurrentMatrix();
    if (sib == -1) {
        return;
        sib = sibling;
    }
    func_0003D508(sib, out, tree, quats, scale);
}
#endif
