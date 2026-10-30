typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0xFF0];
    int target;
    char padFF4[0xFF8 - 0xFF4];
    int targetId;
    char padFFC[0x1000 - 0xFFC];
    Vec4 targetPos;
} CharWork;

typedef struct {
    int state;
    char pad4[0x44 - 4];
    int id;
    char pad48[0x1D4 - 0x48];
    int hit;
    char pad1D8[0x1E0 - 0x1D8];
    Vec4 dir;
} Actor;

extern Vec4 ZUnitVectorInv;
extern void *isysGetThisSubThread(void);
extern CharWork *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern unsigned long *GetCollisionDBAttributeAdr(char *);

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatConj(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void quatRotate(float *out, float *q, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(q), "r"(v));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

static void func_000B0F90(Actor *a)
{
    void *th = isysGetThisSubThread();
    CharWork *ch = GetCharacterClass(th);

    a->hit = 0;
    if (a->state == 7 && (a->hit = ch->target) != 0) {
        char *lay = GetLayoutClass(th);
        Vec4 pos;
        Vec4 d;
        Vec4 q;
        int id;

        id = ch->targetId;
        pos.q = ch->targetPos.q;
        vecSub(d.f, pos.f, *(float **)(lay + 0x134));
        quatConj(q.f, *(float **)(lay + 0x13C));
        quatRotate(d.f, q.f, d.f);
        a->dir.q = d.q;
        if (id == a->id)
            a->hit = 0;
    } else if (a->state == 2) {
        char *lay = GetLayoutClass(th);

        if (*(int *)(lay + 0x124) != 0
            && (*GetCollisionDBAttributeAdr(lay + 0xC0) & (0xF800UL << 20)) == (0xE000UL << 18)) {
            a->dir.q = ZUnitVectorInv.q;
            a->hit = 1;
        }
    }
}
