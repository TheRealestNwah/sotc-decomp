/* Parked: 7 diffs, same size (269 words). Applies the root-dynamics mode (XZ, XZFIT, NOROOTDYNAMICS_VEL_XZSTAB or default) of the current motion to the root quaternion at 0x80 and position at 0x40. Remaining: in the XZ case the Original loads the high dword of the vector copy before the negu of the angle and stores it right after the sll; gcc schedules the negu first and the sd late. Explicit dword copies and argument ordering did not move it. Permuter (-j2, 30 min) found nothing better. The empty asm in mulRotF flushes cse so the temporary address is rebuilt after the call. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { s128 q; int i[4]; } IV;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;

extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
extern int MotRootDyn_XZ;
extern int MotRootDyn_XZFIT;
extern int MotRootDyn_NOROOTDYNAMICS_VEL_XZSTAB;
extern char XUnitVector[];
extern char ZUnitVector[];
extern void *memset(void *, int, unsigned int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, void *);

typedef struct {
    char pad0[0x40];
    float unk40, unk44, unk48, unk4C;
    char pad50[0x30];
    s128 unk80;
    char pad90[0xA4];
    s128 *unk134;
    int pad138;
    s128 *unk13C;
} Root;

static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

static inline void quatMul(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline void quatMulF(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b));
}

static inline void quatRot(void *out, void *quat, void *vec)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
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
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(vec), "r"(quat) : "memory");
}
static inline void quatRotF(void *out, void *quat, void *vec)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
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
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(vec), "r"(quat));
}

#define mulRotF(OUT, A, T, ANG, AX) { void *o_ = (OUT); void *a_ = (A); SetQuaternionByAxisRotateVWithNoRegularize(&T, -(ANG), AX); __asm__ __volatile__("" : : "r"(a_)); quatMul(o_, a_, &T); }
#define mulRot(OUT, A, T, ANG, AX) { void *o_ = (OUT); void *a_ = (A); SetQuaternionByAxisRotateVWithNoRegularize(&T, -(ANG), AX); quatMul(o_, a_, &T); }

void func_0007F138(char *obj, Root *r, char *a2)
{
    V4 q;
    V4 t10;
    V4 t20;
    V4 t30;
    V4 t40;
    short rz;
    short rx;
    void *dyn;

    rz = *(float *)(obj + 0x728) * 32768.0f / 3.14159265f;
    rx = *(float *)(obj + 0x440) * 32768.0f / 3.14159265f;
    memset(&q, 0, 16);
    q.w = 1.0f;
    ((IV *)&r->unk40)->q = ((IV *)r->unk134)->q;
    dyn = dldElement((int *)(a2 + 8));
    if (dyn == (void *)MotRootDyn_XZ) {
        memset(&t30, 0, 16);
        t30.y = *(float *)(obj + 0x6D4);
        t20 = t30;
        mulRot(&r->unk80, r->unk13C, t30, rz, ZUnitVector);
        quatRotF(&t10, &r->unk80, &t20);
        r->unk40 += t10.x;
        r->unk48 += t10.z;
        r->unk44 -= *(float *)(obj + 0x6D4) - t10.y;
        mulRotF(&q, &q, t40, rz, ZUnitVector);
    } else if (dyn == (void *)MotRootDyn_XZFIT) {
    } else if (dyn == (void *)MotRootDyn_NOROOTDYNAMICS_VEL_XZSTAB) {
        mulRotF(&q, &q, t10, rx, XUnitVector);
        mulRotF(&q, &q, t20, rz, ZUnitVector);
        quatMul(&r->unk80, r->unk13C, &q);
    } else {
        mulRotF(&q, &q, t10, rz, ZUnitVector);
        r->unk80 = *r->unk13C;
    }
}
#else
typedef struct Root Root;
extern void func_0007F138(char *obj, Root *r, char *a2);
#endif
