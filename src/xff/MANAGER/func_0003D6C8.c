typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    float pos[4];
    char pad20[0x30 - 0x20];
    int right;
    int left;
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

static inline void QuatToMatrix(float *out, float *q)
{
    __asm__ __volatile__(".set noreorder\n"
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
        ".set reorder\n"
        : : "r"(q), "r"(out));
}

static void func_0003D6C8(int idx, Vec4 *pos, Tree *tree, Vec4 *quats)
{
    Vec4 matrix[4];
    TreeNode *node = &tree->nodes[idx];
    int left = node->left;
    int right;
    float *out;

    iosPushCurrentMatrix();
    right = node->right;
    iosTransCurrentMatrix(node->pos);
    out = matrix[0].f;
    QuatToMatrix(out, quats[idx].f);
    out += 12;
    __asm__ __volatile__("sqc2 vf0, 0(%0)\n" : : "r"(out) : "memory");
    iosMulCurrentMatrixR(matrix[0].f);
    iosGetCurrentMatrix(matrix[0].f);
    pos[idx].q = matrix[3].q;
    if (right != -1)
        func_0003D6C8(right, pos, tree, quats);
    iosPopCurrentMatrix();
    if (left != -1)
        func_0003D6C8(left, pos, tree, quats);
}
