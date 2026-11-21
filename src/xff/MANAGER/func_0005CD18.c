/* Parked: 25 diffs. charrootdyn_slidecollision is inlined; empty asm barriers keep &rel and &fl out of CSE so the frame and length match.
   Remaining: register numbering only (rotate operands a0/v1/v0, p0/p1/fl addresses t6/t5/t7, o in v1, fl.b stored at 0xC4(sp)). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { int a, b; } Flags;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;
extern s128 ZeroVector;
extern int charrootdyn_slidecollisionCB(void *, void *, void *, void *, void *, void *, void *, Flags *, float, float);
extern int charrootdyn_slideExceptionJudgeCB();
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);

static inline void rotate(void *out, void *v, void *q)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%2)\n"
                         "vmr32.w vf14, vf00\n"
                         "vmr32.w vf15, vf00\n"
                         "vmr32.w vf16, vf00\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf00, vf00\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf00, vf00\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf00, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(q) : "memory");
}

static inline void add(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void sub(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline int slidecollision(void *a, void *b, void *c, void *d, void *e, void *f, char *o, Flags *fp, float g, float h)
{
    __asm__("" : "=r"(fp) : "0"(fp));
    if (o != 0) {
        fp->a = (*(unsigned int *)(o + 0x68) >> 11) & 1;
        fp->b = (*(unsigned int *)(o + 0x68) >> 15) & 1;
        return charrootdyn_slidecollisionCB(a, b, c, d, e, f, charrootdyn_slideExceptionJudgeCB, fp, g, h);
    }
    return charrootdyn_slidecollisionCB(a, b, c, d, e, f, o, 0, g, h);
}

void func_0005CD18(void *motion, char *c)
{
    struct { float v[4]; char rest[0x80]; } __attribute__((aligned(16))) out;
    V4 p0;
    V4 p1;
    V4 rel;
    Flags fl;
    s128 *pos = *(s128 **)(c + 0x134);
    s128 *prev = *(s128 **)(c + 0x138);
    void *q = *(void **)(c + 0x13C);
    float r = *(float *)(c + 0xE0C);

    {
        V4 *rp = &rel;
        __asm__("" : "=r"(rp) : "0"(rp));
        rotate(rp, c + 0xE00, q);
    }
    add(&p0, prev, &rel);
    add(&p1, pos, &rel);
    if (slidecollision(&out, &p0, &p1, &ZeroVector, c + 0xE20, 0, *(char **)(c + 0x1C0), &fl,
                       r, 0.01f)) {
        sub(pos, &out, &rel);
    }
    charrootdyn_getRegularColFinderPosition(c + 0x4D0, c, *(void **)(c + 0x13C), *(void **)(c + 0x138));
    *(s128 *)(c + 0x10B0) = **(s128 **)(c + 0x134);
}
#endif
