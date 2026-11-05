typedef int qword __attribute__((mode(TI)));

typedef struct {
    qword q0;
    qword pos;
    qword vel;
    char pad30[0x10];
    float f40;
    char pad44[0xC];
} WormNode;

typedef struct {
    void *obj;
    qword *rot;
    char *bones;
    int pad0C;
    int pad10;
    int idx;
} WormArg;

extern int D_0017B8C8;
extern char *GetSCRCharaAIWorkPtr(void *obj);
extern void *GetCharacterClass(void *obj);
extern void nico_calcWormGenealogicalNodeNextBase(WormArg *arg);
extern void func_00129E10(qword *node, WormArg *arg, void *obj, char *w, char *w2, void *cls, int zero);
extern void func_00128D00(qword *pos, WormArg *arg, qword *prevPos, char *bone, qword *hist, qword *nextPos, int zero, float len);

static inline void quatMul(qword *out, qword *a, qword *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatNormalize(qword *q)
{
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
}

void nico_calcWormGenealogicalNodeDownNext(WormArg *arg)
{
    void *obj;
    char *w;
    void *cls;
    WormNode *n;
    qword *p;

    obj = arg->obj;
    w = (char *)(((int)GetSCRCharaAIWorkPtr(obj) + 0x41B3) & ~0xF);
    cls = GetCharacterClass(obj);
    p = &((WormNode *)w)[D_0017B8C8 + 1].vel;
    if (w[0x129A] == 0) {
        func_00129E10(p, arg, obj, w, w, cls, 0);
        n = (WormNode *)w + D_0017B8C8;
        func_00128D00(&n->pos, arg, &n[-1].pos, arg->bones + arg->idx * 64 + 0x30,
                      (qword *)(w + 0xA10) + D_0017B8C8, &n[1].pos, 0, n->f40);
        quatMul((qword *)(w + 0xA20) + D_0017B8C8, (qword *)(w + 0xA10) + D_0017B8C8, arg->rot + arg->idx);
        quatNormalize((qword *)(w + 0xA20) + D_0017B8C8);
        D_0017B8C8++;
    } else {
        nico_calcWormGenealogicalNodeNextBase(arg);
        D_0017B8C8++;
    }
}
