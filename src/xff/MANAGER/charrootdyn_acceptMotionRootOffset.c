/* 17 diffs. Moves the character's pending motion-root offset (cleared after reading) into out, limited by
   the dld limit table from the parent node (node+0x20) or the motion (motion+0xB0): rotates the stab XZ
   vector into the stab Y-rotation frame, scales it, clamps Z and X by the per-sign limits and rotates back.
   Remaining: in quatPosToMatrix the Original holds the matrix pointer in $v1 and the quaternion in $v0,
   then recomputes &mat[3] from $sp; ours swaps them and derives &mat[3] from the matrix pointer. The
   second block's X clamp branch is laid out inverted (bc1tl vs bc1fl). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
/* Inverse of a rigid transform: transposed rotation, rotated negated translation. */
#define VU_INVERSE_MATRIX(dst, src) \
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n" \
                         "vsubw.x vf25, vf0, vf0w\n" \
                         "vmulx.xyz vf28, vf24, vf25x\n" \
                         "vsub.w vf28, vf28, vf28\n" \
                         "lq $8, 0x0(%1)\n" \
                         "lq $9, 0x10(%1)\n" \
                         "lq $10, 0x20(%1)\n" \
                         "qmfc2 $11, vf0\n" \
                         "pextlw $12, $9, $8\n" \
                         "pextuw $13, $9, $8\n" \
                         "pextlw $14, $11, $10\n" \
                         "pextuw $15, $11, $10\n" \
                         "pcpyld $8, $14, $12\n" \
                         "pcpyud $9, $12, $14\n" \
                         "pcpyld $10, $15, $13\n" \
                         "pcpyud $11, $13, $15\n" \
                         "qmtc2 $8, vf24\n" \
                         "qmtc2 $9, vf25\n" \
                         "qmtc2 $10, vf26\n" \
                         "vmulax.xyzw ACC, vf24, vf28x\n" \
                         "vmadday.xyzw ACC, vf25, vf28y\n" \
                         "vmaddaz.xyzw ACC, vf26, vf28z\n" \
                         "vmaddw.xyzw vf29, vf0, vf28w\n" \
                         "vsub.w vf29, vf29, vf29\n" \
                         "vadd.w vf29, vf29, vf0\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf29, 0x30(%0)\n" \
                         : : "r"(dst), "r"(src) \
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory")


static inline void quatPosToMatrix(Vec4 *out, Vec4 *quat, Vec4 *pos)
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
                         : : "r"(out), "r"(quat));
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(&out[3]));
}
typedef struct DldType { char pad[0xC]; int size; } DldType;
typedef struct DldTable { char pad[8]; DldType *type; char pad2[4]; char *data; } DldTable;
extern int DldSysUndefSymbol;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline float vecLenSq(Vec4 *a)
{
    float d;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a) : "$2");
    return d;
}

static inline void matApply(Vec4 *out, Vec4 *m, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

extern void iosGetStabXZVector(Vec4 *, Vec4 *);
extern void GetStabYRotQuaternion(Vec4 *, int);

typedef struct {
    char pad0[0x13C];
    int stab;
    char pad140[0x1C0 - 0x140];
    char *node;
    char pad1C4[0xC80 - 0x1C4];
    Vec4 rootOffset;
    char padC90[0x1140 - 0xC90];
    char *motion;
} Chara;

#define SCALE_RES() do { \
        if (res.f[2] >= 0) res.f[2] *= lim[1]; else res.f[2] *= lim[2]; \
        if (res.f[0] >= 0) res.f[0] *= lim[3]; else res.f[0] *= lim[4]; \
    } while (0)

#define APPLY_OFFSET()                                                  \
    do {                                                                \
        s = obj->stab;                                                  \
        iosGetStabXZVector(&stab, &v);                                  \
        GetStabYRotQuaternion(&quat, s);                                \
        __asm__ __volatile__("" : : "f"(scale));                        \
        { Vec4 *mp = mat; quatPosToMatrix(mp, &quat, 0); }                                 \
        VU_INVERSE_MATRIX(inv, mat);                                    \
        vecScale(stab.f, stab.f, lim[0] * scale);                       \
        matApply(&res, inv, &stab);                                     \
        SCALE_RES();                                                    \
        matApply(out, mat, &res);                                       \
    } while (0)

void charrootdyn_acceptMotionRootOffset(Vec4 *out, Chara *obj, float scale)
{
    Vec4 v;
    Vec4 stab;
    Vec4 mat[4];
    Vec4 inv[4];
    Vec4 quat;
    Vec4 res;
    float *lim;
    int s;
    Vec4 *ro = &obj->rootOffset;

    v.q = ro->q;
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(ro));
    if (vecLenSq(&v) > 0) {
        if (obj->node != 0) {
            lim = dldElement((int *)(obj->node + 0x20));
            if (lim != 0) {
                APPLY_OFFSET();
                return;
            }
        }
        lim = dldElement((int *)(obj->motion + 0xB0));
        if (lim != 0) {
            APPLY_OFFSET();
            return;
        }
    }
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(out));
}
#endif
