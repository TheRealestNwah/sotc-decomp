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
    float quat[4];
    float ext[3];
    TargetFuncs *funcs;
} TargetWork;

extern int CheckCubeVolume(void *, void *, void *);
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

static inline void quatMatrix2(void *quat, void *mat, void *trans)
{
    register void *m asm("$4") = mat;
    register void *q asm("$5") = quat;
    register void *t asm("$6") = trans;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%1)\n"
                         : : "r"(q), "r"(m), "r"(t));
}

static inline float dist2xz(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "vmul.xz vf7, vf7, vf7
"
                         "vaddz.x vf7, vf7, vf7z
"
                         "qmfc2.ni $2, vf7
"
                         "mtc1 $2, %0
"
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

/* Box test for the damage-box letters: like func_000E9E50, finds the hit point (a joint matrix times an offset, the root quaternion matrix times it, or a joint or root position), rejects it by an XZ distance against the largest padded half-extent, then tests it against the box oriented by the sender's quaternion with CheckCubeVolume and checks the line of sight. */
static int func_000EAB40(TargetWork *w, char *dmg, char *tgt, char *obj)
{
    V2 vec __attribute__((aligned(16)));
    union { Vec4 f; V2 l; } pos;
    Vec4 mat[4];
    V2 qv __attribute__((aligned(16)));
    union { Vec4 f; V2 l; } tmp;
    char buf[0x50];
    Vec4 *p;
    Vec4 *out;
    int idx;
    float r, ex, ey, ez, m;
    int ok;
    Vec4 *q;
    void *vp;

    ok = 0;
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
    q = p;
    r = *(float *)(dmg + 0x90);
    ex = w->ext[0] + r;
    ey = w->ext[1] + r;
    ez = w->ext[2] + r;
    if (ey < ex) {
        m = ez;
        if (ez < ex)
            m = ex;
    } else {
        m = ey;
        if (!(ez < ey))
            m = ez;
    }
    vp = &vec;
    if (dist2xz(vp, q) < m * m) {
        tmp.f.x = w->quat[0];
        tmp.f.y = w->quat[1];
        tmp.f.z = w->quat[2];
        tmp.f.w = w->quat[3];
        qv = tmp.l;
        tmp.f.x = ex;
        tmp.f.y = ey;
        tmp.f.z = ez;
        tmp.f.w = 0;
        quatMatrix2(&qv, mat, vp);
        ok = 0;
        if (CheckCubeVolume(mat, p, &tmp.f))
            ok = visible(w, obj, buf, &vec, p) != 0;
    }
    return ok;
}
