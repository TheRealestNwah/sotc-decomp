#ifdef NONMATCHING /* 21 diffs: s5/s6 swapped for 0x13C/0x138 pointers, lqc2 operand register order, mfc1 temp, late v1 */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x30];
    float v30[4];
    char pad40[0x60 - 0x40];
    float v60[4];
    s128 v70;
    char pad80[0xA0 - 0x80];
    float vA0[4];
    char padB0[0x4C0 - 0xB0];
    char pad4C0[0x1070 - 0x4C0];
    int mode;
    char pad1074[0x1080 - 0x1074];
    float v1080[4];
} Cls;

extern void *GetCharacterClass(void);
extern void ForceUnparentLayoutObj(int);
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);

static inline void zero(s128 *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

void directplay(int obj, float *vec, float t, float pad, float scale)
{
    s128 buf[3];
    Cls *c = (Cls *)GetCharacterClass();
    s128 *q70;
    float *q60;
    float *p134;
    float *p13c;
    float *p138;
    float *v1;
    float *bp;
    union { float f; int i; } ti, si;

    p13c = *(float **)((char *)c + 0x13C);
    q70 = &c->v70;
    p134 = *(float **)((char *)c + 0x134);
    q60 = c->v60;
    p138 = *(float **)((char *)c + 0x138);
    ForceUnparentLayoutObj(obj);
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n"
                         "sqc2 vf0, 0x0(%1)\n"
                         : : "r"(p13c), "r"(q60) : "memory");
    zero(q70);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(vec), "r"(c->vA0), "r"(&buf[1]) : "memory");
    if (c->mode == 1) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(c->v1080), "r"(&buf[1]), "r"(buf) : "memory");
    } else {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(c), "r"(&buf[1]), "r"(buf) : "memory");
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(buf), "r"(q70) : "memory");
    bp = (float *)buf;
    if (t >= 1.0f) {
        *(s128 *)p134 = buf[0];
    } else {
        ti.f = t;
        __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyzw ACC, vf5, vf7x\n"
                             "vmaddw.xyzw vf9, vf6, vf8w\n"
                             "sqc2 vf9, 0x0(%2)\n"
                             : : "r"(ti.i), "r"(bp), "r"(p134) : "memory");
    }
    p134[3] = 1.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         : : "r"(p134), "r"(p138), "r"(&buf[2]) : "memory");
    si.f = scale;
    v1 = c->v30;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(&buf[2]), "r"(si.i), "r"(v1) : "memory");
    v1[3] = 0;
    *(s128 *)p138 = *(s128 *)p134;
    charrootdyn_getRegularColFinderPosition((char *)c + 0x4C0, c, p13c, p134);
    if (*(char **)((char *)c + 0x19C))
        *(*(char **)((char *)c + 0x19C) + 0x8C) = 1;
}
#endif
