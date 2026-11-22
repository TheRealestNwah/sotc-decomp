/* Parked: 23 diffs, same size. Shoulder collision probe: transforms the motion node tool position, B_0018B7B0 and the class origin into object space, casts a cyclic Z/Y one-way collision probe along the class quaternion turned by -0x8000 about Z and -0x2000 about X, and on a hit writes either the hit position or a point rotated by the arcsine of the target direction. Called as T_00092958 from nico_player_colfit_Shoulder.c. Remaining: the Original recomputes the SetQuaternionByAxisRotateVWithNoRegularize argument address after the call (ours CSEs it), and the t2/f12 argument setup order. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    float x, y, z, w;
} Vec4 __attribute__((aligned(8)));

typedef struct {
    char pad[0x40];
    s128 pos;
} ColResult;

extern char B_0018B7B0[];
extern char XUnitVector[], ZUnitVector[];
extern char *GetCharacterClass(int);
extern void GetMotionNodeQuaternionPosToolCoord(void *, void *, int, int, int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, void *);
extern int charrootdyn_getCyclicCollisionDetectZYOneWayCB(void *, void *, void *, int, int, void *, void *, int, float);
extern int character_ikcolattrfilter();
extern float iosGetASinfExact(float);

static inline void matVec(void *dst, void *m, void *v)
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
                         : : "r"(dst), "r"(m), "r"(v) : "memory");
}

static inline void subXYZ(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void subXYZW(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float lengthXYZ(void *v)
{
    float len;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(v) : "$2");
    return len;
}

static inline void normalize(void *dst, void *src)
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
                         : : "r"(dst), "r"(src) : "memory");
}

static inline void quatMul(void *dst, void *a, void *b)
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
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void quatPosTransform(void *dst, void *v, void *pos, void *q)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf18, 0x0(%2)\n"
                         "vmove.w vf18, vf0\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%3)\n"
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
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(dst), "r"(v), "r"(pos), "r"(q) : "memory");
}

static int func_00092958(s128 *out, int *obj0)
{
    register int *obj asm("s2") = obj0;
    Vec4 q __attribute__((aligned(16)));
    Vec4 v10 __attribute__((aligned(16)));
    Vec4 v20 __attribute__((aligned(16)));
    Vec4 v30 __attribute__((aligned(16)));
    Vec4 v40 __attribute__((aligned(16)));
    Vec4 v50 __attribute__((aligned(16)));
    Vec4 v60 __attribute__((aligned(16)));
    ColResult res __attribute__((aligned(16)));
    Vec4 vC0 __attribute__((aligned(16)));
    Vec4 qD0 __attribute__((aligned(16)));
    Vec4 qE0 __attribute__((aligned(16)));
    Vec4 qF0 __attribute__((aligned(16)));
    Vec4 v100 __attribute__((aligned(16)));
    Vec4 v110 __attribute__((aligned(16)));
    Vec4 q120 __attribute__((aligned(16)));
    Vec4 q130 __attribute__((aligned(16)));
    int actor;
    char *cc;
    float zero;
    float len;
    char *m;
    void *rq;

    actor = obj[0];
    cc = GetCharacterClass(actor);
    GetMotionNodeQuaternionPosToolCoord(&q, &v40, actor, obj[5], 1);
    m = (char *)obj + 0x70;
    matVec(&v20, m, &v40);
    matVec(&v30, m, B_0018B7B0);
    matVec(&v10, m, cc + 0x40);
    zero = 0.0f;
    v60.x = v30.x;
    v60.z = v10.z;
    v60.y = v10.y * zero;
    v60.w = 1.0f;
    v50 = v60;
    matVec(&v60, (char *)obj + 0x30, &v50);
    subXYZ(&vC0, &v30, &v10);
    vC0.x = zero;
    vC0.y = zero;
    len = lengthXYZ(&vC0);
    rq = *(void **)(cc + 0x13C);
    SetQuaternionByAxisRotateVWithNoRegularize(&qE0, -0x8000, ZUnitVector);
    quatMul(&qD0, rq, &qE0);
    SetQuaternionByAxisRotateVWithNoRegularize(&qF0, -0x2000, XUnitVector);
    quatMul(&qD0, &qD0, &qF0);
    if (charrootdyn_getCyclicCollisionDetectZYOneWayCB(&res, &v60, &qD0, 4, 1, cc + 0xE20, character_ikcolattrfilter, 0, len) ) {
    matVec(&qE0, m, &res.pos);
    subXYZW(&v100, &qE0, &v50);
    normalize(&qF0, &v100);
    subXYZW(&v110, &v30, &v50);
    normalize(&v110, &v110);
    if (qF0.y > v110.y) {
        *out = res.pos;
        return 1;
    }
    if (qF0.y <= zero) {
        short ang = (short)(int)(iosGetASinfExact(v110.y) * 32768.0f / 3.1415926f);
        rq = *(void **)(cc + 0x13C);
        SetQuaternionByAxisRotateVWithNoRegularize(&q130, ang, XUnitVector);
        quatMul(&q120, rq, &q130);
        v100.w = 1.0f;
        quatPosTransform(out, &v100, &v60, &q120);
        return 1;
    }
    }
    return 0;
}
#endif
