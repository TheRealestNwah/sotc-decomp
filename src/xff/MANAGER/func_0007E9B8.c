/* Parked: 2 diffs, same size (338 words). Remaining: the three GetMotionNS_RootInfo argument moves are scheduled a0,a1,a2 instead of the Original's a2,a1,a0 (0x180/0x188). */
#ifdef NONMATCHING
typedef unsigned int qword __attribute__((mode(TI)));

typedef union {
    float v[4];
    qword q;
} Quat;

typedef struct {
    char pad0[0x10];
    char *nodes;
} AnimRes;

typedef struct {
    char pad0[0x34];
    int rot;
    char pad38[0x18];
    int res;
} AnimObj;

typedef struct {
    char pad0[8];
    float f8;
    float fC;
} FrameInfo;

extern int D_00136C08;
extern qword IdentityQuaternion;
extern AnimRes *getAnimObjResource(int *);
extern void getPosPQSAnimIntFrame(Quat *, int, int);
extern void GetMotionIntFrame(Quat *, int *, int, int);
extern void resourceRot(Quat *, Quat *, Quat *, int, int);
extern void GetMotionNS_RootInfo(Quat *, Quat *, AnimRes *, int, float, float, float);
extern void getMotionFloatFrame(Quat *, AnimRes *, int, float);
extern void DivQuaternion(Quat *, Quat *, Quat *);

static inline void vsub4(Quat *out, Quat *a, Quat *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vadd3(Quat *out, Quat *a, Quat *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scale3(Quat *out, Quat *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void lerp3(Quat *out, Quat *a, Quat *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline float dot4(Quat *a, Quat *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni $2, vf15\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void scale4(Quat *out, Quat *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void lerp4(Quat *out, Quat *a, Quat *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void normalize4(Quat *out, Quat *in)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

static inline void mulQuat(Quat *out, Quat *a, Quat *b)
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

static void func_0007E9B8(Quat *pos, Quat *rotOut, Quat *rots, FrameInfo *fi, AnimObj *obj, AnimObj *sub,
                          Quat *trans, Quat *root, Quat *out, int n, int idx, float t, float rs, float bt)
{
    Quat base;
    Quat diff;
    Quat rpos;
    Quat rrot;
    Quat q;
    AnimRes *res;
    int *src;
    char *node;
    int i;

    src = sub ? &sub->res : 0;
    {
        Quat cur[n];

        res = getAnimObjResource(&obj->res);
        node = res->nodes + idx * 12;
        if (src) {
            { char *sn = getAnimObjResource(src)->nodes + idx * 12; getPosPQSAnimIntFrame(&base, *(int *)(sn + 8), 0); }
            GetMotionIntFrame(cur, src, 0, n);
            resourceRot(cur, &base, 0, sub->rot, 0);
        } else {
            getPosPQSAnimIntFrame(&base, *(int *)(node + 8), 0);
            GetMotionIntFrame(cur, &obj->res, 0, n);
            resourceRot(cur, &base, 0, obj->rot, 0);
        }
        {
            Quat nxt[n];

            GetMotionNS_RootInfo(&rpos, &rrot, res, idx, fi->f8, fi->fC, t);
            getMotionFloatFrame(nxt, res, n, fi->f8);
            resourceRot(nxt, &rpos, &rrot, obj->rot, 0);
            vsub4(&diff, &rpos, &base);
            for (i = 0; i < n; i++) {
                DivQuaternion(&nxt[i], &cur[i], &nxt[i]);
            }
            if (bt < 1.0f && D_00136C08) {
                lerp3(trans, &diff, trans, bt);
                diff.q = trans->q;
                for (i = 0; i < n; i++) {
                    union { float f; int i; } d;
                    q.q = out[i].q;
                    d.f = dot4(&nxt[i], &q);
                    if (d.i < 0) {
                        scale4(&q, &q, -1.0f);
                    }
                    lerp4(&out[i], &nxt[i], &q, bt);
                    normalize4(&out[i], &out[i]);
                    nxt[i].q = out[i].q;
                }
            } else {
                trans->q = diff.q;
                for (i = 0; i < n; i++) {
                    ((Quat *)((i << 4) + (int)out))->q = ((Quat *)((i << 4) + (int)nxt))->q;
                }
            }
            root->q = rrot.q;
            if (rs < 1.0f) {
                scale3(&diff, trans, rs);
                scale3(&rrot, root, rs);
                for (i = 0; i < n; i++) {
                    union { float f; int i; } d;
                    Quat *po;
                    Quat *pn = (Quat *)((i << 4) + (int)nxt);
                    po = (Quat *)((i << 4) + (int)out);
                    q.q = IdentityQuaternion;
                    d.f = dot4(po, &q);
                    if (d.i < 0) {
                        scale4(&q, &q, -1.0f);
                    }
                    lerp4(pn, po, &q, rs);
                    normalize4(pn, pn);
                }
            }
            if (pos) {
                vadd3(pos, pos, &diff);
            }
            if (rotOut) {
                vadd3(rotOut, rotOut, &rrot);
            }
            if (rots) {
                for (i = 0; i < n; i++) {
                    mulQuat(&rots[i], &rots[i], &nxt[i]);
                }
            }
        }
    }
}
#else
typedef unsigned int qword __attribute__((mode(TI)));
typedef union { float v[4]; qword q; } Quat;
typedef struct FrameInfo FrameInfo;
typedef struct AnimObj AnimObj;
static void func_0007E9B8(Quat *pos, Quat *rotOut, Quat *rots, FrameInfo *fi, AnimObj *obj, AnimObj *sub, Quat *trans, Quat *root, Quat *out, int n, int idx, float t, float rs, float bt);
#endif
