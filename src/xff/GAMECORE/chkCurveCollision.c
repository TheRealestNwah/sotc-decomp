/* Parked: 100 diffs, same size. Curve collision probe: builds the layout's forward axis A from its quaternion (+0x13C, VU0 block), the side vector B = normalise(A x YUnitVector) * f12, scales A by the owner's +0x3E4 reach, forms four ray start points (position + A, position, position + A, position) and four end points (start + B, start + B, start - B, start - B) in one frame struct, casts the four rays (ClipCollisionDirectCallBack with the layout group and getRealColJudgeFunc, w = 1.0 in both endpoints) and returns 1 when all four hit, 3 when the first two hit, 2 when the last two hit, else 0. VU0 runs match word for word. Remaining: register numbering (the Original keeps the start and end arrays in s6/s5 and the object in s4; ours puts them in different saved registers) and the order of the first address setups. Introducing pointer locals for the array bases made it worse (168). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern Vec YUnitVector;
extern int getColiGroupByUserPathWork(int);
extern void *getRealColJudgeFunc(int);
extern void *memset(void *, int, unsigned int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int, int, int, void *, int);

int chkCurveCollision(char *o, float f12)
{
    struct {
        Vec A;
        Vec B;
        Vec p[8];
        int hitf[4];
        char hit[0x50];
    } L __attribute__((aligned(16)));
    int *s2;
    int i;
    int bits;
    int g;
    float k;
    char *pos;

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
                         : "r"(&L.A), "r"(*(char **)(*(char **)(o + 0x18) + 0x13C))
                         : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(&L.A), "r"(&YUnitVector), "r"(&L.B)
                         : "memory");
    __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(f12));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         :
                         : "r"(&L.B), "r"(bits)
                         : "memory");
    k = *(float *)(*(char **)(o + 0x14) + 0x3E4);
    __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(k));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         :
                         : "r"(&L.A), "r"(bits)
                         : "memory");
    s2 = L.hitf;
    memset(s2, 0, 0x10);
#define ADD(d, p0, q) __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n" : : "r"(p0), "r"(q), "r"(d) : "memory")
#define SUB(d, p0, q) __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n" : : "r"(p0), "r"(q), "r"(d) : "memory")
    ADD(&L.p[0], *(char **)(*(char **)(o + 0x18) + 0x134), &L.A);
    L.p[1].q = **(s128 **)(*(char **)(o + 0x18) + 0x134);
    ADD(&L.p[2], *(char **)(*(char **)(o + 0x18) + 0x134), &L.A);
    L.p[3].q = **(s128 **)(*(char **)(o + 0x18) + 0x134);
    ADD(&L.p[4], &L.p[0], &L.B);
    ADD(&L.p[5], &L.p[1], &L.B);
    SUB(&L.p[6], &L.p[2], &L.B);
    SUB(&L.p[7], &L.p[3], &L.B);
    i = 0;
    do {
        int off = i * 16;

        i++;
        *(float *)((char *)&L.p[0] + off + 0xC) = 1.0f;
        *(float *)((char *)&L.p[4] + off + 0xC) = 1.0f;
        g = getColiGroupByUserPathWork(*(int *)(o + 4));
        if (ClipCollisionDirectCallBack(L.hit, (char *)&L.p[0] + off, (char *)&L.p[4] + off, g, 0, 0, 0, getRealColJudgeFunc(*(int *)(o + 4)), 0) != 0)
            *s2 = 1;
        s2++;
    } while (i < 4);
    if (L.hitf[0] != 0) {
        if (L.hitf[1] != 0 && L.hitf[2] != 0 && L.hitf[3] != 0)
            return 1;
        if (L.hitf[0] != 0 && L.hitf[1] != 0)
            return 3;
    }
    if (L.hitf[2] != 0 && L.hitf[3] != 0)
        return 2;
    return 0;
}
#endif
