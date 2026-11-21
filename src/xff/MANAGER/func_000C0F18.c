typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern float iosGetRandom(void);
extern Vec4 ZUnitVector;
extern void func_000C6450(char *, Vec4 *, float *, char *, char *, char *);
extern void func_000C65B0(char *, char *, int);
extern void func_000C6648(char *, char *, char *);
extern void func_000C1638(char *, char *);

#define F(b, o) (*(float *)((b) + (o)))
typedef union { int i; float f; } U;
#define I(b, o) (((U *)((b) + (o)))->i)
#define Q(b, o) (((Vec4 *)((b) + (o)))->q)

/* The a0-a3 clobbers put the blend factor in t0, as in the Original. */
static inline void lerpXYZ(void *out, void *a, void *b, float t)
{
    __asm__ __volatile__("qmtc2.ni %3, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "r"(t) : "memory", "a0", "a1", "a2", "a3");
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scaleXYZ(void *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void normalizeXYZ(void *out, void *in)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

static inline int isFar(char *ctx)
{
    int n = I(ctx, 0x120) < 2;
    return n == 0;
}

static void func_000C0F18(char *p, char *pos, char *e, char *ctx, char *res, char *prm)
{
    Vec4 dir;
    Vec4 rv;
    float speed;
    int far;

    speed = 0.0f;
    F(p, 0x40) = F(prm, 0x18) + F(prm, 0x1C) * iosGetRandom();
    F(p, 0x44) = 0.0f;
    if (I(res, 0) == 1 || I(res, 0) == 3) {
        Q(p, 0) = Q(e, 0x10);
        F(p, 0x48) = F(ctx, 0xA4) + iosGetRandom() * F(ctx, 0xA8);
    } else {
        lerpXYZ(p, e + 0x10, e + 0x40, iosGetRandom());
        F(p, 0x48) = 0.0f;
    }
    F(p, 4) += F(prm, 0);
    addXYZ(p, p, pos);
    if (I(res, 0xB8) != 0) {
        rv.f[0] = F(prm, 0x124) + iosGetRandom() * F(prm, 0xC0);
        rv.f[1] = F(prm, 0x128) + iosGetRandom() * F(prm, 0xC4);
        rv.f[2] = F(prm, 0x12C) + iosGetRandom() * F(prm, 0xC8);
        rv.f[3] = 0.0f;
        if (iosGetRandom() <= 0.5f) rv.f[0] = -rv.f[0];
        if (iosGetRandom() <= 0.5f) rv.f[1] = -rv.f[1];
        if (iosGetRandom() <= 0.5f) rv.f[2] = -rv.f[2];
        addXYZ(p, p, &rv);
    }
    func_000C6450(p, &dir, &speed, e, res, prm);
    F(p, 0x88) = F(prm, 0x4C) + iosGetRandom() * F(prm, 0x154);
    F(p, 0x8C) = F(prm, 0x50) + iosGetRandom() * F(prm, 0x158);
    F(p, 0x54) = F(prm, 0x110) + F(prm, 0x114) * iosGetRandom();
    F(p, 0x58) = F(prm, 0x20) + F(prm, 0x24) * iosGetRandom();
    F(p, 0x5C) = F(p, 0x40) - (F(prm, 0x28) + F(prm, 0x2C) * iosGetRandom());
    F(p, 0x60) = 1.0f / F(p, 0x58);
    F(p, 0x64) = 1.0f / (F(p, 0x40) - F(p, 0x5C));
    F(p, 0x4C) = F(prm, 0x54) + F(prm, 0x58) * iosGetRandom();
    F(p, 0x50) = F(prm, 0x5C) + F(prm, 0x60) * iosGetRandom();
    F(p, 0x68) = F(prm, 0x78) + F(prm, 0x7C) * iosGetRandom();
    F(p, 0x6C) = F(prm, 0x80) + F(prm, 0x84) * iosGetRandom();
    F(p, 0x70) = F(prm, 0x90) + F(prm, 0x94) * iosGetRandom();
    F(p, 0x74) = F(prm, 0x98) + F(prm, 0x9C) * iosGetRandom();
    F(p, 0x78) = F(prm, 0xA8) + F(prm, 0xAC) * iosGetRandom();
    F(p, 0x7C) = F(prm, 0xB0) + F(prm, 0xB4) * iosGetRandom();
    if (I(res, 0xC8) == 0) {
        F(p, 0x80) = 0.0f;
    } else {
        F(p, 0x80) = F(prm, 0xCC) + F(prm, 0xD0) * iosGetRandom();
        if (I(res, 0xC8) == 2 && 0.5f <= iosGetRandom()) F(p, 0x80) = -F(p, 0x80);
    }
    F(p, 0x84) = 0.0f;
    far = isFar(ctx);
    if (far == 1) {
        F(p, 0x94) = F(ctx, 0x90) + iosGetRandom() * F(ctx, 0x94);
        if (I(ctx, 0x88) == 1 && 0.5f <= iosGetRandom()) F(p, 0x94) = -F(p, 0x94);
        if (I(ctx, 0x84) == 1) {
            F(p, 0x90) = iosGetRandom() * F(ctx, 0x124);
        } else if (0.0f <= F(p, 0x94)) {
            F(p, 0x90) = 0.0f;
        } else {
            F(p, 0x90) = F(ctx, 0x124) - 0.01f;
        }
    } else {
        F(p, 0x90) = 0.0f;
        F(p, 0x94) = 0.0f;
    }
    if (I(res, 0xC) == 0) {
        F(p, 0x98) = 0.0f;
        F(p, 0x9C) = 0.0f;
        F(p, 0xA0) = 0.0f;
        __asm__ __volatile__("break 0");
    } else if (I(res, 0xC) == 1 || I(res, 0xC) == 4) {
        if (I(res, 0x164) == 1) {
            F(p, 0x98) = iosGetRandom() * 6.2831850052f;
        } else if (I(res, 0x164) == 0) {
            F(p, 0x98) = F(prm, 0x148);
        } else {
            F(p, 0x98) = F(e, 0x194);
        }
        F(p, 0x9C) = F(prm, 0xDC) + F(prm, 0xE0) * iosGetRandom();
        F(p, 0xA0) = 1.0f;
        if (iosGetRandom() <= 0.5f) {
            F(p, 0x9C) = -F(p, 0x9C);
            F(p, 0xA0) = -F(p, 0xA0);
        }
        if (I(res, 0xC) == 1) {
            if (I(res, 0x18C) == 1) {
                F(p, 0x30) = iosGetRandom() - 0.5f;
                F(p, 0x34) = iosGetRandom() - 0.5f;
                F(p, 0x38) = iosGetRandom() - 0.5f;
                F(p, 0x3C) = 0.0f;
                normalizeXYZ(p + 0x30, p + 0x30);
            } else {
                Q(p, 0x30) = ZUnitVector.q;
            }
        } else if (I(res, 0xC) == 4) {
            func_000C65B0(p, prm, 1);
        } else {
            __asm__ __volatile__("break 0");
        }
    } else if (I(res, 0xC) == 2) {
        F(p, 0x98) = F(prm, 0xF8) + F(prm, 0xFC) * iosGetRandom();
        F(p, 0x9C) = F(prm, 0x100) + F(prm, 0x104) * iosGetRandom();
        F(p, 0xA0) = 0.0f;
        if (speed < 0.0f ? speed < -0.005f : 0.005f < speed) {
            Q(p, 0x30) = Q(p, 0x10);
        } else {
            scaleXYZ(p + 0x30, &dir, 0.005f);
        }
    } else if (I(res, 0xC) == 3) {
        F(p, 0x98) = F(p, 0);
        F(p, 0x9C) = F(p, 4);
        F(p, 0xA0) = F(p, 8);
    }
    F(p, 0xA4) = 0.0f;
    func_000C1638(p, ctx);
    func_000C6648(p, e, ctx);
}
