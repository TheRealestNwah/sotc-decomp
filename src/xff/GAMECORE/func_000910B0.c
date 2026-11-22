/* Parked: 23 diffs, same size. Builds a quaternion/translation matrix from the character class, then for each of n 0x20-byte hang segments transforms both endpoints, casts a collision ray (SCRGetCollisionCallBack with func_00091AB8) and either sets the segment's script-control status (dld-linked def) or records edge/hand grip geometry from func_00090408. Remaining: the Original fills v[1], copies it to v[0] before loading the second endpoint, then fills v[2]; this hoists all six item loads ahead of the stores. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { Vec4 a; Vec4 b; } Seg;

extern char gcGlobalVar[];
extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);
extern int SCRGetCollisionCallBack(char *, float *, float *, void *, int (*)(), int);
extern int func_00091AB8();
extern int func_00090408(char *, char *, int);
extern int IsGeoColStatus(char *, long, long);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void CopyGeometryPointer(void *, void *);

static inline void quatMatrix(Vec4 *mm, Vec4 *quat, Vec4 *pos)
{
    register Vec4 *m __asm__("$2") = mm;

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
                         : : "r"(m), "r"(quat), "r"(pos) : "memory");
}

static inline void mulVec(Vec4 *out, Vec4 *m, Vec4 *v)
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline Seg mkSeg(float *p)
{
    Seg s;

    s.a.f[0] = p[0];
    s.a.f[1] = p[1];
    s.a.f[2] = p[2];
    s.a.f[3] = 1.0f;
    s.b.f[0] = p[3];
    s.b.f[1] = p[4];
    s.b.f[2] = p[5];
    s.b.f[3] = 1.0f;
    return s;
}

static int func_000910B0(void *edge, void *hand, void *obj, char *item, int n)
{
    Vec4 m[4];
    Vec4 a;
    Vec4 b;
    Vec4 v[3];
    char col[0x40];
    char *ch;
    int r = 0;

    ch = GetCharacterClass(obj);
    quatMatrix(m, *(Vec4 **)(ch + 0x13C), *(Vec4 **)(ch + 0x134));
    while (n-- != 0) {
        v[1].f[0] = ((float *)item)[0];
        v[1].f[1] = ((float *)item)[1];
        v[1].f[2] = ((float *)item)[2];
        v[1].f[3] = 1.0f;
        v[0] = v[1];
        v[2].f[0] = ((float *)item)[3];
        v[2].f[1] = ((float *)item)[4];
        v[2].f[2] = ((float *)item)[5];
        v[2].f[3] = 1.0f;
        v[1] = v[2];
        mulVec(&a, m, &v[0]);
        mulVec(&b, m, &v[1]);
        if (SCRGetCollisionCallBack(col, a.f, b.f, gcGlobalVar + 0x230, func_00091AB8, 0)) {
            unsigned int *h = (unsigned int *)(item + 0x18);
            unsigned int v = *h;
            int off = v & 0x3FFFF;
            char *t = off != 0 ? *(char **)((char *)h - off) : 0;
            int *def = (t != 0 && t != (char *)DldSysUndefSymbol)
                ? (int *)(*(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)) : 0;

            if (def != 0) {
                if (IsGeoColStatus(col, 0x8000L << 31, 0x8000L << 31))
                    CharaCtrlSetScriptCtrlStatus(obj, def[1]);
            } else {
                int f = func_00090408(col, ch, 1);

                if (f & 4) {
                    r |= 1;
                    CopyGeometryPointer(edge, col);
                }
                if (f & 2) {
                    r |= 2;
                    CopyGeometryPointer(hand, col);
                }
            }
        }
        item += 0x20;
    }
    return r;
}
#else
extern int func_000910B0();
#endif
