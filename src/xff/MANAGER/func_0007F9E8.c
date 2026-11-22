/* Blends a quaternion at offset 0x20 toward IdentityQuaternion by t and
 * renormalises it; which blends run depends on the type at offset 0. */
/* Parked: 22 diffs.
 * Remaining: in the cases that keep the temporary quaternion off $sp, the
 * temporary's address (addiu aN, $sp, X) and the copy of the source pointer
 * (daddu aN, $a0) come out in swapped order and registers.
 */
#ifdef NONMATCHING
typedef unsigned int qword __attribute__((mode(TI)));

typedef union {
    float v[4];
    qword q;
} Quat;

static inline float dot4(Quat *a, Quat *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni $2, vf15
" "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void scale4(Quat *out, Quat *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void lerp4(Quat *out, Quat *a, Quat *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void normalize4(Quat *out, Quat *in)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

extern Quat IdentityQuaternion;

typedef struct Blend {
    int type;
    char pad4[0x1C];
    Quat rot;
} Blend;

static inline void quatInterp(Quat *out, Quat *a, Quat *b, float t)
{
    Quat tmp;
    union {
        float f;
        int i;
    } d;

    tmp.q = b->q;
    d.f = dot4(a, &tmp);
    if (d.i < 0)
        scale4(&tmp, &tmp, -1.0f);
    lerp4(out, a, &tmp, t);
    normalize4(out, out);
}

void func_0007F9E8(Blend *b, float t)
{
    switch (b->type) {
    case 1:
    case 5:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
        break;
    case 4:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
        break;
    case 7:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
        break;
    case 2:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
    case 45:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
        break;
    case 11:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
        break;
    case 9:
    case 38:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
        break;
    case 6:
        quatInterp(&b->rot, &b->rot, &IdentityQuaternion, t);
        break;
    }
}
#endif
