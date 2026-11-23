/* 4 diffs, same size (443 words). Builds a jump velocity from a JumpVelocityDef (gravity -14.7, optionally scaled), rotates it by the character orientation (cc+0x13C) about Y by def->angle, or falls back to a motion velocity or the current velocity, then limits it against the floor speed and adds it into cc+0x30. Remaining diffs are in the else branch quaternion apply: the Original puts the output (sp) pointer in $v1 and cc+0x13C in $v0; ours swaps them. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

typedef struct {
    float angle;
    float vx;
    float vy;
    float vz;
    unsigned int flags;
    float speed;
    float rate;
    unsigned char xz1;
    char pad1D[3];
    float speed2;
    float rate2;
    unsigned char xz2;
    char pad29[3];
    float maxSpeed;
} JumpVel;

extern void *JumpVelocityDef_IGNORE_MOTION_VELOCITY;
extern void *JumpVelocityDef_NOT_ADD_FLOOR_SPEED;
extern Vec4 YUnitVector;
extern Vec4 ZeroVector;
extern char *GetCharacterClass(void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(Vec4 *, short, Vec4 *);
extern void *memset(void *, int, unsigned int);

static inline float sqrtf_(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float lengthSquareXYZ(Vec4 *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline void scaleXZ(Vec4 *out, Vec4 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "mfc1 $8, %2\n"
                         "qmtc2.ni $8, vf6\n"
                         "vmulx.xz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "f"(factor) : "$8", "memory");
}

static inline void scaleXYZ(Vec4 *out, Vec4 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void scaleXYZW(Vec4 *out, Vec4 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void normalizeXYZ(Vec4 *out, Vec4 *a)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a) : "memory");
}

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatMul(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                         "lqc2 vf12, 0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatApply(Vec4 *out, Vec4 *q, Vec4 *v)
{
    __asm__("" : "+r"(out));
    __asm__ __volatile__("lqc2 vf8, 0(%2)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0(%1)\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         : : "r"(out), "r"(q), "r"(v) : "memory");
}

static inline void rotateY(Vec4 *out, Vec4 *q, short ang)
{
    Vec4 t;
    SetQuaternionByAxisRotateVWithNoRegularize(&t, -ang, &YUnitVector);
    quatMul(out, q, &t);
}

int func_00053620(void *obj, int *ref, int *vref, float scale)
{
    Vec4 vel;
    Vec4 src;
    Vec4 jump;
    Vec4 rot;
    JumpVel *def = dldElement(ref);
    char *cc = GetCharacterClass(obj);
    float *vsrc = dldElement(vref);
    Vec4 *in;
    Vec4 *dst;
    int have;
    int ignore;
    int ret;

    ret = 1;
    have = 1;
    ignore = 0;
    if (def == JumpVelocityDef_IGNORE_MOTION_VELOCITY || def == JumpVelocityDef_NOT_ADD_FLOOR_SPEED) {
        ignore = 1;
    }
    in = 0;
    if (vsrc != 0 && !ignore) {
        in = &src;
        src.f[0] = vsrc[0];
        src.f[1] = vsrc[1];
        src.f[2] = vsrc[2];
        src.f[3] = 0.0f;
    } else {
        have = 0;
    }
    if (def != 0 && have) {
        float vx, vy, vz, g;
        vx = def->vx;
        vy = def->vy;
        vz = def->vz;
        memset(&jump, 0, 0x10);
        if (def->flags & 1) {
            g = scale * -14.6999998f;
        } else {
            g = -14.6999998f;
        }
        if (vy < 0.0f) {
            if (vz < 0.0f) {
                jump.f[1] = vz;
                jump.f[2] = vx;
            } else {
                float v = sqrtf_(g * -2.0f * vz);
                jump.f[1] = v;
                jump.f[2] = vx / ((v * -2.0f) / g);
            }
        } else {
            if (vz < 0.0f) {
                jump.f[1] = g * -0.5f * vy;
            } else {
                jump.f[1] = 0.0f;
            }
            jump.f[2] = vx / vy;
        }
        {
            rotateY(&rot, *(Vec4 **)(cc + 0x13C), (short)(int)(def->angle * 32768.0f / 180.0f));
            quatApply(&vel, &rot, &jump);
        }
        if ((def->flags >> 1) & 1) {
            ret = 0;
        }
    } else if (in != 0) {
        quatApply(&vel, *(Vec4 **)(cc + 0x13C), in);
    } else {
        vel.q = ((Vec4 *)(cc + 0x30))->q;
    }
    dst = (Vec4 *)(cc + 0x30);
    if (cc[0xA28] == 0 && *(int *)(cc + 0x124) != 0 && (*(char **)(cc + 0x19C))[0x8E] != 0) {
        Vec4 *floor = (Vec4 *)(*(char **)(cc + 0x19C) + 0x10);
        if (def != 0) {
            if (!((def->flags >> 2) & 1)) {
                floor = &ZeroVector;
            }
            if (!ignore) {
                float spd = def->speed;
                float spd2 = spd * spd;
                float len2 = lengthSquareXYZ(floor);
                float m;
                if (0.0f <= spd) {
                    float rate = def->rate;
                    float inv = 1.0f / rate;
                    if (spd2 * (inv * inv) < len2) {
                        if (def->xz1) {
                            scaleXZ(&vel, &vel, rate);
                        } else {
                            scaleXYZ(&vel, &vel, rate);
                        }
                    } else {
                        float r2 = 1.0f;
                        float s2 = def->speed2;
                        if (0.0f <= s2) {
                            r2 = def->rate2;
                            if (s2 * s2 < len2) {
                                float t = (sqrtf_(len2) - s2) / (spd - s2);
                                float u = 1.0f - t;
                                if (def->xz2) {
                                    scaleXZ(&vel, &vel, r2 * u + rate * t);
                                } else {
                                    scaleXYZ(&vel, &vel, r2 * u + rate * t);
                                }
                            }
                        }
                        if (spd2 < len2) {
                            float t = (sqrtf_(len2) - spd) / (spd * inv - spd);
                            float u = 1.0f - t;
                            if (def->xz1) {
                                scaleXZ(&vel, &vel, r2 * u + def->rate * t);
                            } else {
                                scaleXYZ(&vel, &vel, r2 * u + def->rate * t);
                            }
                        }
                    }
                }
                m = def->maxSpeed;
                len2 = lengthSquareXYZ(&vel);
                if (0.0f <= m && m * m < len2) {
                    normalizeXYZ(&vel, &vel);
                    scaleXYZW(&vel, &vel, m);
                }
            }
        }
        addXYZ(dst, floor, &vel);
    } else {
        dst->q = vel.q;
    }
    return ret;
}
#endif
