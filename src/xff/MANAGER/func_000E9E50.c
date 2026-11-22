typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
typedef struct { int a[4]; } V2 __attribute__((aligned(8)));

typedef struct {
    char pad0[8];
    unsigned int flags;
} TargetFuncs;

typedef struct {
    char *owner;
    float pos[3];
    float radius;
    TargetFuncs *funcs;
} TargetWork;

extern char *GetCharacterClass(char *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern int func_000EBC78();

static inline void mulMatVec(void *out, void *mat, void *vec)
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
                         : : "r"(out), "r"(mat), "r"(vec) : "memory");
}

static inline void quatMatrix(void *mat, void *quat, void *trans)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(mat), "r"(quat), "r"(trans));
}

static inline float dist2(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline int visible(TargetWork *w, char *obj, void *buf, void *vec, void *p)
{
    char *cc;
    if (w->funcs->flags & 0x10000) {
        cc = GetCharacterClass(obj);
        if (cc != 0 && ((*(unsigned int *)(*(char **)(cc + 0x1140) + 0x38) >> 2) & 1)) {
            if (ClipCollisionDirectCallBack(buf, vec, p, *(char **)(cc + 0xE38) + *(short *)(cc + 0x370) * 4, 0, 0, 0, func_000EBC78, 0) != 0)
                return 0;
        }
    }
    return 1;
}

static int func_000E9E50(TargetWork *w, char *dmg, char *tgt, char *obj)
{
    V2 vec __attribute__((aligned(16)));
    union { Vec4 f; V2 l; } pos;
    Vec4 mat[4];
    char buf[0x50];
    Vec4 *p;
    Vec4 *out;
    int idx;
    float r;
    char *cc;
    int ok;

    p = &pos.f;
    out = p;
    pos.f.x = w->pos[0];
    pos.f.y = w->pos[1];
    pos.f.z = w->pos[2];
    pos.f.w = 1.0f;
    vec = pos.l;
    idx = *(int *)(dmg + 0x6C);
    if (idx >= 0) {
        if (*(int *)(dmg + 0x70) != 0)
            mulMatVec(out, *(char **)(tgt + 0x158) + idx * 64, dmg + 0x80);
        else
            p = (Vec4 *)(*(char **)(tgt + 0x158) + idx * 64 + 0x30);
    } else {
        if (*(int *)(dmg + 0x70) != 0) {
            quatMatrix(mat, *(void **)(tgt + 0x13C), *(void **)(tgt + 0x134));
            mulMatVec(out, mat, dmg + 0x80);
        } else
            p = *(Vec4 **)(tgt + 0x134);
    }
    r = w->radius + *(float *)(dmg + 0x90);
    return dist2(&vec, p) < r * r && visible(w, obj, buf, &vec, p);
}
