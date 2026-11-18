typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

extern void iosRotMatrixY(void *, float);
extern int getPathColiGroup(int);
extern int ClipCollisionDirect(void *, void *, void *, int);
extern int addPassageInsertPos(int, Vec4 *);
extern void setRayCutPassageWork(int, int, int);
extern void func_00103860(char *, float *, Vec4 *);

static const float RO_00181420[8] = { 0.0f, 45.0f, -45.0f, 90.0f, -90.0f, 135.0f, -135.0f, 180.0f };

static inline float dot(float *a, float *b)
{
    float r;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline float distXZ(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void applyMatrix(void *d, void *m, void *v)
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
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

#define CF(o) (*(float *)(c + (o)))

static void func_00100A48(char *o, float *dir, float *v, Vec4 *out)
{
    Vec4 tmp;
    Vec4 rot;
    char clip[0x50];
    char mtx[0x40] __attribute__((aligned(16)));
    char *c;
    float d;
    float r;
    int i;
    const float *ang;

    c = *(char **)(o + 0xCC);
    d = dot(dir, v);
    if (0.0f <= d) {
        if (CF(0x194) + CF(0x19C) <= distXZ(c + 0x160, *(void **)(*(char **)(o + 0x18) + 0x134)) && 0.8660254f <= d) {
            *(int *)(c + 0x154) = 2;
            func_00103860(o, dir, out);
            goto search;
        }
        vecScale(tmp.f, dir, CF(0x194) + CF(0x19C));
    } else {
        r = CF(0x194) + CF(0x19C);
        if (r <= distXZ(c + 0x160, *(void **)(*(char **)(o + 0x18) + 0x134)))
            vecScale(tmp.f, dir, -r);
        else
            vecScale(tmp.f, dir, r);
    }
search:
    ang = RO_00181420;
    for (i = 0; i < 8; i++) {
        iosRotMatrixY(mtx, *ang * 0.017453293f);
        applyMatrix(rot.f, mtx, tmp.f);
        rot.f[1] += CF(0x198) / CF(0x194) * (CF(0x194) + CF(0x19C));
        vecAdd(out->f, (float *)(o + 0x130), rot.f);
        out->f[3] = 1.0f;
        ang++;
        if (ClipCollisionDirect(clip, *(void **)(*(char **)(o + 0x18) + 0x134), out, getPathColiGroup(*(int *)(o + 4))) != 0)
            continue;
        if (ClipCollisionDirect(clip, out, o + 0x130, getPathColiGroup(*(int *)(o + 4))) == 0)
            break;
    }
    if (i == 8) {
        tmp.f[1] += CF(0x198) / CF(0x194) * (CF(0x194) + CF(0x19C));
        vecAdd(out->f, (float *)(o + 0x130), tmp.f);
        out->f[3] = 1.0f;
    }
    *(int *)(c + 0x154) = 1;
    ((Vec4 *)(c + 0x160))->q = out->q;
    if (addPassageInsertPos(*(int *)(o + 4), out))
        setRayCutPassageWork(*(int *)(o + 4), 0, 0);
}
