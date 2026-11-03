typedef float Vec4[4] __attribute__((aligned(16)));

typedef struct {
    char pad0[8];
    char *frames;
} IKAnim;

typedef struct {
    void *obj;
    char *quats;
    char pad8[8];
    IKAnim *anim;
    int node;
} IKLeg;

extern char *GetLayoutClass(void *);
extern void *GetCharacterClass(void *);
extern void GetCharacterClassOptionNodeLocalQuaternionPos(float *, float *, void *, int, int);

static inline void vecMulXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatPosApply(float *out, float *quat, float *pos, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%3)\n"
                         "lqc2 vf18, 0x0(%2)\n"
                         "vmove.w vf18, vf0\n"
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
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(quat), "r"(pos), "r"(v) : "memory");
}

void nico_IK_getAddSubPosition(float *out, IKLeg *leg, float *v)
{
    Vec4 tmp;
    Vec4 pos;
    void *obj = leg->obj;
    char *layout = GetLayoutClass(obj);
    int node = leg->node;

    if (node > 0 && (node & 0x10000)) {
        int n = node & ~0x10000;
        GetCharacterClassOptionNodeLocalQuaternionPos(tmp, out, GetCharacterClass(obj), n, 0);
        return;
    }
    vecMulXYZ(pos, (float *)(leg->anim->frames + node * 0x40 + 0x10), (float *)(layout + 0x90));
    quatPosApply(out, (float *)(leg->quats + leg->node * 0x10), pos, v);
}
