extern char B_0018B7B0[], B_0018B7C0[], B_0018B7D0[];
extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPosToolCoord(void *, void *, void *, int, int);

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

void nico_player_colfit_HandEffector(PendObj *obj)
{
    float q[4] __attribute__((aligned(16)));
    void *actor = obj->actor;
    int node;
    char *skel;
    char *lc;

    GetMotionNodeQuaternionPosToolCoord(q, B_0018B7C0, actor, obj->node, 0);
    GetMotionNodeQuaternionPosToolCoord(q, B_0018B7B0, actor, obj->node, 1);
    node = obj->node & ~0x10000;
    skel = obj->skel;
    lc = GetLayoutClass(actor);
    vecMul3(B_0018B7D0, *(char **)(skel + 0x24) + node * 64 + 0x10, lc + 0x90);
}
