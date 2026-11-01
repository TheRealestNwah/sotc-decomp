extern char B_0018B7B0[], B_0018B7D0[];
extern char *GetLayoutClass(void *);
extern void *memset(void *, int, unsigned int);

typedef struct {
    void *actor;
    int pad[3];
    char *skel;
    int node;
} PendObj;

static inline void vecMul3(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd3(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void applyMatrix(void *out, void *m, void *v)
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

void nico_player_pendulum_FootEffector(PendObj *obj)
{
    float tmp[4] __attribute__((aligned(16)));
    void *actor = obj->actor;
    char *skel = obj->skel;
    int node = obj->node & ~0x10000;
    char *lc;

    lc = GetLayoutClass(actor);
    vecMul3(B_0018B7D0, *(char **)(skel + 0x24) + node * 64 + 0x10, lc + 0x90);
    memset(tmp, 0, 0x10);
    tmp[2] = -0.15f;
    lc = GetLayoutClass(actor);
    applyMatrix(tmp, *(char **)(lc + 0x158) + *(int *)(*(char **)(obj->skel + 0x24) + node * 64 + 0x30) * 64, tmp);
    vecAdd3(B_0018B7D0, B_0018B7D0, tmp);
    lc = GetLayoutClass(actor);
    applyMatrix(B_0018B7B0, *(char **)(lc + 0x158) + *(int *)(*(char **)(obj->skel + 0x24) + node * 64 + 0x30) * 64, B_0018B7D0);
}
