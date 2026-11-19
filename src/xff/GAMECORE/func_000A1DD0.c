typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x2E0];
    Vec4 vel;
} Obj;

typedef struct {
    Vec4 pos;
    char pad10[0x4C - 0x10];
    float accel;
} Target;

typedef struct {
    char pad0[0x30];
    Vec4 vel;
    Vec4 acc;
    Vec4 from;
    Vec4 to;
    Vec4 x70;
    char pad80[0x90 - 0x80];
    float time;
    float scale;
} Work;

typedef struct {
    char pad0[0x134];
    Vec4 *pos;
    char pad138[4];
    float *rot;
} Layout;

extern void *isysGetThisSubThread(void);
extern Layout *GetLayoutClass(void *);
extern void AI_GetYRotQuaternion(float *, float *);
extern float AI_GetTimeFromAccelC3(float, float, float, float);
extern Vec4 ZeroVector;

static inline void quatRotateVector(Vec4 *out, Vec4 *quat0, Vec4 *vec0)
{
    Vec4 *vec = vec0;
    register Vec4 *quat asm("$2") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

static inline void normalizeXYZ(Vec4 *output, Vec4 *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}

static inline void subXYZW(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float lengthXYZ(Vec4 *v)
{
    float len;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)
"
                         "vmul.xyz vf7, vf7, vf7
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vsqrt Q, vf7w
"
                         "vwaitq
"
                         "cfc2 $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(len) : "r"(v) : "$2");
    return len;
}

static inline float dotXYZ(Vec4 *a, Vec4 *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vaddw.x vf7, vf0, vf0w
"
                         "vmul.xyz vf6, vf5, vf6
"
                         "vaddax.x ACC, vf0, vf6x
"
                         "vmadday.x ACC, vf7, vf6y
"
                         "vmaddz.x vf6, vf7, vf6z
"
                         "qmfc2.ni $2, vf6
"
                         "mtc1 $2, %0
"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline float calcTime(Work *w, float a)
{
    Vec4 n1;
    Vec4 n2;
    Vec4 d;
    float dist;

    subXYZW(&d, &w->to, &w->from);
    dist = lengthXYZ(&d);
    normalizeXYZ(&d, &d);
    normalizeXYZ(&n1, &w->vel);
    normalizeXYZ(&n2, &w->acc);
    return AI_GetTimeFromAccelC3(lengthXYZ(&w->vel) * dotXYZ(&n1, &d),
                                 lengthXYZ(&w->acc) * dotXYZ(&n2, &d), dist, a);
}

/* Parked: 11 words differ (scheduling of the ZeroVector copies and the 1.0f store) */
#ifdef NONMATCHING
static void func_000A1DD0(Obj *obj, Target *tgt, Work *w)
{
    Vec4 q;
    Layout *l = GetLayoutClass(isysGetThisSubThread());

    AI_GetYRotQuaternion(q.f, l->rot);
    quatRotateVector(&w->vel, &q, &obj->vel);
    w->acc.q = ZeroVector.q;
    w->from.q = l->pos->q;
    w->to.q = tgt->pos.q;
    w->scale = 1.0f;
    w->x70.q = ZeroVector.q;
    if (tgt->accel > 0.0f)
        w->time = calcTime(w, 0.0f);
    else
        w->time = calcTime(w, 10.0f);
}
#endif
