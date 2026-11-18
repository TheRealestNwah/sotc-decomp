typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct { char pad0[0xC]; int stride; } SymTab;
typedef struct { char pad0[8]; SymTab *tab; char padC[4]; char *base; } SymMod;
typedef struct { char pad0[8]; float lim; } PendObj;
typedef struct { char pad0[4]; float lim; } PendParam;

extern int *DldSysUndefSymbol;
extern void GetGeometryPointerPosition(Vec4 *, void *);

static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static void func_00069B70(void *object, char *c, PendParam *params)
{
    Vec4 pos;
    Vec4 *vel = (Vec4 *)(c + 0x30);
    Vec4 *b40 = (Vec4 *)(c + 0xB40);
    Vec4 *b60 = (Vec4 *)(c + 0xB60);
    Vec4 *b80 = (Vec4 *)(c + 0xB80);
    Vec4 *b50 = (Vec4 *)(c + 0xB50);
    unsigned int *lp = (unsigned int *)(*(char **)(c + 0x1C0) + 0xC);
    unsigned int l = *lp;
    SymMod *m;
    PendObj *o;
    float lim;
    float len2;

    if ((l & 0x3FFFF) != 0)
        m = *(SymMod **)((char *)lp - (l & 0x3FFFF));
    else
        m = 0;
    if (m != 0 && m != (SymMod *)DldSysUndefSymbol)
        o = (PendObj *)(m->base + ((l >> 18) & 0xFFF) * m->tab->stride);
    else
        o = 0;
    if (o == 0)
        o = *(PendObj **)(c + 0x408);
    lim = (o->lim < params->lim) ? params->lim : o->lim;
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vaddy.z vf6, vf0, vf7y\n"
        "vsubw.z vf6, vf6, vf7w\n"
        "vsubx.y vf6, vf0, vf5x\n"
        "vsubz.y vf6, vf6, vf5z\n"
        "vaddz.x vf6, vf7, vf7z\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.y vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(c + 0xBA0), "r"(*(Vec4 **)(c + 0x13C)) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len2) : "r"(vel) : "$2");
    if (1.0f < len2) {
        float k = 1.0f / sqrtF(len2);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(vel), "r"(k) : "memory");
    }
    b50->q = vel->q;
    b40->q = (*(Vec4 **)(c + 0x138))->q;
    GetGeometryPointerPosition(&pos, c + 0xC0);
    b80->q = vel->q;
    b60->q = b40->q;
    b80[1].q = vel->q;
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         ".set reorder\n"
                         : : "f"(0.5f), "r"(&pos), "r"(b40), "r"(b60 + 1) : "memory", "$8");
    *(float *)(c + 0xC20) = lim;
    *(char *)(c + 0xC28) = 1;
    *(int *)(c + 0xC24) = 0;
    *(int *)(c + 0xC00) = 0;
}
