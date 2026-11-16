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
    register float *p13c __asm__("$21");
    register float *p138 __asm__("$22");
    float *v1;
    float *bp;
    register s128 qq __asm__("$2");
    register void *a0r __asm__("$4");
    register void *a1r __asm__("$5");
    register void *a2r __asm__("$6");
    register void *a3r __asm__("$7");
    register int tb __asm__("$8");
    register float *pb2 __asm__("$2");
    float onef;
    register float *pv30 __asm__("$3");
    register float *pb1 __asm__("$5");
    register float *pva __asm__("$2");
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
    __asm__ __volatile__("addiu %0, $29, 0x10" : "=r"(pb1));
    __asm__ __volatile__("addiu %0, %1, 0xA0" : "=r"(pva) : "r"(c));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(vec), "r"(pva), "r"(pb1) : "memory");
    if (c->mode == 1) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(c->v1080), "r"(pb1), "r"(buf) : "memory");
    } else {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(c), "r"(pb1), "r"(buf) : "memory");
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
        __asm__ __volatile__("mfc1 %0, %1" : "=r"(tb) : "f"(t));
        __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyzw ACC, vf5, vf7x\n"
                             "vmaddw.xyzw vf9, vf6, vf8w\n"
                             "sqc2 vf9, 0x0(%2)\n"
                             : : "r"(tb), "r"(bp), "r"(p134) : "memory");
    }
    onef = 1.0f;
    __asm__ __volatile__("" : "+f"(onef));
    pv30 = c->v30;
    __asm__ __volatile__("" : "+r"(pv30));
    __asm__ __volatile__("addiu %0, $29, 0x20" : "=r"(pb2));
    p134[3] = onef;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         : : "r"(p134), "r"(p138), "r"(pb2) : "memory");
    si.f = scale;
    v1 = pv30;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(pb2), "r"(si.i), "r"(v1) : "memory");
    v1[3] = 0;
    a2r = p13c;
    a3r = p134;
    __asm__ __volatile__("" : "+r"(a3r));
    a0r = (char *)c + 0x4C0;
    __asm__ __volatile__("lq %0, 0x0(%1)" : "=r"(qq) : "r"(p134));
    a1r = c;
    __asm__ __volatile__("" : "+r"(a1r) : : "memory");
    *(s128 *)p138 = qq;
    charrootdyn_getRegularColFinderPosition(a0r, a1r, a2r, a3r);
    if (*(char **)((char *)c + 0x19C))
        *(*(char **)((char *)c + 0x19C) + 0x8C) = 1;
}
