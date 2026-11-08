typedef int s128 __attribute__((mode(TI)));
typedef struct { long long x, y; } Pair;
typedef float Vec4[4] __attribute__((aligned(16)));

extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *GameObject_PARTHENON_BRIDGE_1;
extern char *GameObject_PARTHENON_BRIDGE_2;
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, void *);
extern void func_0006BC58(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

/* Parked: 19 words differ (callee-saved assignment: the dir/pos vector pointers land in s1/s2 swapped, and the two long long args in s2/s4 swapped). */
#ifdef NONMATCHING
int SCRConditionMinoCBridgeRayChack(void *obj, int u1, int u2, int u3, long long ex0, long long ex1, int u4, int u5, unsigned int *key, float f0, float f1, float f2)
{
    struct { s128 q; char buf[0x50]; Vec4 p70; Vec4 p80; Vec4 p90; Vec4 pa0; Pair held; } L;
    int cnt;
    char *c1;
    char *c2;
    char *r1;
    char *r2;
    char *chr;
    
    
    

    c1 = GetCharacterClass(*(void **)(GameObject_PARTHENON_BRIDGE_1 + 8)) + 0x1C0;
    r1 = dldResolve(key);
    cnt = r1 != *(char **)c1;
    c2 = GetCharacterClass(*(void **)(GameObject_PARTHENON_BRIDGE_2 + 8)) + 0x1C0;
    r2 = dldResolve(key);
    if (r2 != *(char **)c2)
        cnt += 2;
    if (cnt == 3)
        return 1;
    L.held.x = ex0;
    L.held.y = ex1;
    L.q = *(s128 *)(GetCharacterClass(obj) + 0x470);
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
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
                         : : "r"(L.pa0), "r"(&L.q) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.p90), "r"(L.pa0), "r"(f1) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.p70), "r"(*(void **)(GetLayoutClass(obj) + 0x134)), "r"(L.p90) : "memory");
    chr = GetCharacterClass(obj) + 0x470;
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
                         : : "r"(L.pa0), "r"(chr) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%3)\n"
                         "lqc2 vf6, 0x0(%0)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         : : "r"(L.p90), "r"(L.pa0), "r"(f2), "r"(L.p70) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.p90), "r"(L.pa0), "r"(f0) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.p80), "r"(L.p70), "r"(L.p90) : "memory");
    return ClipCollisionDirectCallBack(L.buf, L.p70, L.p80, gcGlobalVar + 0x238, 0, 0, 0, func_0006BC58, &L.held) == 0;
}
#else
extern int SCRConditionMinoCBridgeRayChack(void *obj, int u1, int u2, int u3, long long ex0, long long ex1, int u4, int u5, unsigned int *key, float f0, float f1, float f2);
#endif
