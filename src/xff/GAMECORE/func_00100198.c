#ifdef NONMATCHING /* 7 diffs: case 3 &a/w+0x170 in a1/a0 instead of a0/a1 */
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern void func_00100A48(char *, void *, void *, void *);
extern int chkAttainExecLayout(int, void *, void *, void *);
extern int getPathColiGroup(int);
extern int ClipCollisionDirect(void *, void *, void *, int);

#define SUB(d, a, b) __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyzw vf7, vf5, vf6\nsqc2 vf7, 0x0(%2)\n" : : "r"(a), "r"(b), "r"(d) : "memory")
#define ADD(d, a, b) __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n" : : "r"(a), "r"(b), "r"(d) : "memory")
#define NORM(d) __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nvmul.xyz vf7, vf5, vf5\nvmulax.w ACC, vf0, vf7x\nvmadday.w ACC, vf0, vf7y\nvmaddz.w vf7, vf0, vf7z\nvrsqrt Q, vf0w, vf7w\nvwaitq\nvmulq.xyz vf5, vf5, Q\nsqc2 vf5, 0x0(%0)\n" : : "r"(d) : "memory")
#define SCALE(d, a, s) __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nqmtc2.ni %1, vf6\nvmulx.xyz vf5, vf5, vf6x\nsqc2 vf5, 0x0(%2)\n" : : "r"(a), "r"(s), "r"(d) : "memory")

static inline float sqlen(void *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\nvmul.xyz vf7, vf7, vf7\nvaddy.x vf7, vf7, vf7y\nvaddz.x vf7, vf7, vf7z\nqmfc2.ni $2, vf7\nmtc1 $2, %0\n" : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline float dot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\nlqc2 vf6, 0x0(%2)\nvaddw.x vf7, vf0, vf0w\nvmul.xyz vf6, vf5, vf6\nvaddax.x ACC, vf0, vf6x\nvmadday.x ACC, vf7, vf6y\nvmaddz.x vf6, vf7, vf6z\nqmfc2.ni $2, vf6\nmtc1 $2, %0\n" : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline float distxz(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\nlqc2 vf6, 0x0(%2)\nvsub.xyzw vf7, vf5, vf6\nvmul.xz vf7, vf7, vf7\nvaddz.x vf7, vf7, vf7z\nvsqrt Q, vf7x\nvwaitq\ncfc2 $2, $vi22\nmtc1 $2, %0\n" : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void quatAxis(void *d, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         :
                         : "r"(d), "r"(q)
                         : "memory");
}

static inline void matVec(void *d, void *m, void *v)
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
                         :
                         : "r"(d), "r"(m), "r"(v)
                         : "memory");
}

static inline void vscale(void *out, void *a, float s){
 __asm__ __volatile__("mfc1 $3, %2
""lqc2 vf5, 0x0(%1)
""qmtc2.ni $3, vf6
""vmulx.xyz vf5, vf5, vf6x
""sqc2 vf5, 0x0(%0)
" : : "r"(out), "r"(a), "f"(s) : "$3", "memory");}
int func_00100198(void *out, char *o)
{
    Vec dir;
    Vec perp;
    Vec np;
    Vec a;
    Vec b;
    Vec s;
    char hit[0x50];
    char *w = *(char **)(o + 0xCC);
    char *pos = o + 0x130;

    SUB(&dir, pos, *(void **)(*(char **)(o + 0x18) + 0x134));
    dir.y = 0.0f;
    NORM(&dir);
    if (sqlen(&dir) == 0.0f) {
        SUB(&dir, pos, *(void **)(*(char **)(o + 0x18) + 0x138));
        dir.y = 0.0f;
        NORM(&dir);
    }
    quatAxis(&perp, o + 0xD0);
    perp.y = 0.0f;
    NORM(&perp);
    switch (*(int *)(w + 0x154)) {
    case 3:
        SUB(&a, w + 0x160, *(void **)(*(char **)(o + 0x18) + 0x134));
        SUB(&b, w + 0x160, w + 0x170);
        a.y = 0.0f;
        b.y = 0.0f;
        NORM(&a);
        NORM(&b);
        if (dot(&a, &b) < 0.049999998f) {
            func_00100A48(o, &dir, &perp, &np);
        }
        break;
    case 0:
        func_00100A48(o, &dir, &perp, &np);
        break;
    case 1:
        if (chkAttainExecLayout(*(int *)(o + 4), w + 0x160, *(void **)(o + 0x18), *(void **)(o + 0x14)) == 1) {
            vscale(&s, &dir, -*(float *)(w + 0x194));
            s.y += *(float *)(w + 0x198);
            ADD(&np, pos, &s);
            np.w = 1.0f;
            *(int *)(w + 0x154) = 2;
            ((Vec *)(w + 0x160))->q = np.q;
        }
        break;
    case 2:
        if (chkAttainExecLayout(*(int *)(o + 4), w + 0x160, *(void **)(o + 0x18), *(void **)(o + 0x14)) == 1) {
            *(int *)(w + 0x154) = 3;
            ((Vec *)(w + 0x160))->q = ((Vec *)pos)->q;
            ((Vec *)(w + 0x170))->q = (*(Vec **)(*(char **)(o + 0x18) + 0x134))->q;
            ((Vec *)(w + 0x180))->q = (*(Vec **)(*(char **)(o + 0x18) + 0x13C))->q;
            *(float *)(w + 0x190) = 0.0f;
        } else if (distxz(pos, *(void **)(*(char **)(o + 0x18) + 0x134)) < *(float *)(w + 0x194)
                   || ClipCollisionDirect(hit, *(void **)(*(char **)(o + 0x18) + 0x134), pos,
                                          getPathColiGroup(*(int *)(o + 4))) != 0) {
            func_00100A48(o, &dir, &perp, &np);
        } else {
            vscale(&s, &dir, -*(float *)(w + 0x194));
            s.y += *(float *)(w + 0x198);
            ADD(&np, pos, &s);
            np.w = 1.0f;
            ((Vec *)(w + 0x160))->q = np.q;
        }
        break;
    }
    matVec(out, o + 0x20, w + 0x160);
    return 1;
}
#endif
