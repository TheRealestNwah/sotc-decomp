#ifdef NONMATCHING
/* Close: v0/v1 swapped for the nodes pointer in the position add. */
typedef unsigned int qword __attribute__((mode(TI)));

typedef struct {
    char pad0[0x10];
    float pos[4];
    char pad20[0x18];
    int parent;
    char pad3c[4];
} Node;

typedef struct {
    char pad0[8];
    Node *nodes;
} Motion;

extern qword ZeroPoint;

static inline void RotVec(qword *v, qword *q)
{
        __asm__ __volatile__(".set noreorder\n"
            "lqc2 vf8, 0x0(%0)\n"
            "vaddw.xyz vf12, vf0, vf0w\n"
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
            "vmulax.xyzw ACC, vf14, vf8x\n"
            "vmadday.xyzw ACC, vf15, vf8y\n"
            "vmaddaz.xyzw ACC, vf16, vf8z\n"
            "vmaddw.xyzw vf10, vf0, vf8w\n"
            "sqc2 vf10, 0x0(%0)\n"
            ".set reorder\n"
            : : "r"(v), "r"(q) : "memory");
}

static inline void AddVec(qword *v, float *t)
{
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
            "lqc2 vf6, 0x0(%1)\n"
            "vadd.xyz vf5, vf5, vf6\n"
            "sqc2 vf5, 0x0(%0)\n"
            : : "r"(v), "r"(t) : "memory");
}

void GetMotionNodeBasePos(qword *out, Motion *m, qword *quats, int node)
{
    *out = ZeroPoint;
    while (node != -1) {
        RotVec(out, &quats[node]);
        AddVec(out, m->nodes[node].pos);
        node = m->nodes[node].parent;
    }
}
#endif
