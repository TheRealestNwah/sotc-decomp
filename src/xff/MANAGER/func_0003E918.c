typedef int s128 __attribute__((mode(TI)));
typedef float FVEC[4] __attribute__((aligned(16)));

typedef struct {
    FVEC q;
    FVEC ofs;
    FVEC pos;
    FVEC axisZ;
    FVEC axisY;
    float ratio_max;
    float yaw_max;
    float yaw_min;
    float yaw_thr;
    float pitch_max;
    float blend_max;
    char pad68[8];
} IkTemp;

typedef struct {
    char pad00[0xC];
    int reset;
    char pad10[0x50];
    float yaw_speed;
} IkObj;

extern FVEC YUnitVector;
extern void get_temp_parameter_motion_ik_base(IkTemp *, IkObj *);
extern void GetOffsetPositionQuaternion(float *, float *, float *, IkTemp *);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_yaw(float, float, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(float *, float, float);
extern void convert_from_quater_to_rotXYZ_motion_ik_base(float *, float *, IkObj *);
extern float iosGetACosfExact(float);

static inline void vecSub(float *d, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(float *d, float *a)
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
                         : : "r"(d), "r"(a) : "memory");
}

static inline void quatConj(float *d, float *a)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(d), "r"(a) : "memory");
}

static inline void quatMul(float *d, float *a, float *b)
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
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void quatAxisZ(float *d, float *q)
{
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
                         : : "r"(d), "r"(q) : "memory");
}

static inline void quatAxisY(float *d, float *q)
{
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
                         : : "r"(d), "r"(q) : "memory");
}

static inline float vecDot(float *a, float *b)
{
    register float r __asm__("$2");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=r"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

static inline void vecLerp(float *d, float *a, float *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
static void func_0003E918(float *out, IkObj *ik, IkObj *obj, float *target, float *prev)
{
    FVEC zdir;
    FVEC pos;
    FVEC dir;
    FVEC rq;
    FVEC qinv;
    FVEC qbase;
    FVEC qlocal;
    FVEC qtmp;
    FVEC qcur;
    FVEC qaim;
    FVEC qlinv;
    IkTemp tp;
    FVEC ydir;
    float yaw0;
    float pitch0;
    float yaw1;
    float pitch1;
    float p;
    float r;

    get_temp_parameter_motion_ik_base(&tp, obj);
    GetOffsetPositionQuaternion(pos, tp.ofs, tp.pos, &tp);
    vecSub(dir, target, pos);
    vecNormalize(dir, dir);
    *(s128 *)qbase = *(s128 *)tp.q;
    quatConj(qinv, qbase);
    GetQuaternionByAxisDirZY(qlocal, tp.axisZ, tp.axisY);
    quatMul(qcur, qbase, qlocal);
    quatAxisZ(zdir, qcur);
    GAMEUTIL_get_yaw_pitch_by_direction(&yaw0, &pitch0, zdir);
    GAMEUTIL_get_yaw_pitch_by_direction(&yaw1, &pitch1, dir);
    yaw1 = GAMEUTIL_get_interp_yaw(yaw0, yaw1, 1.0f - GAMEUTIL_get_dist_ratio(ABS(pitch1), tp.ratio_max, 1.553343f));
    r = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(yaw0, yaw1);
    if (ik->reset == 0 && tp.yaw_thr < ABS(r) && r * ik->yaw_speed < 0.0f) {
        if (ik->yaw_speed >= 0.0f)
            r = tp.yaw_max;
        else
            r = tp.yaw_min;
    } else {
        if (tp.yaw_max < r)
            r = tp.yaw_max;
        if (r < tp.yaw_min)
            r = tp.yaw_min;
    }
    yaw1 = GAMEUTIL_increase_yaw(0, yaw0, r);
    if (tp.pitch_max < ABS(pitch1)) {
        if (pitch1 >= 0.0f)
            pitch1 = tp.pitch_max;
        else
            pitch1 = -tp.pitch_max;
    }
    GAMEUTIL_get_direction_by_yaw_pitch(dir, yaw1, pitch1);
    ik->yaw_speed = r;
    GetQuaternionByAxisDirZY(qaim, dir, YUnitVector);
    quatMul(qtmp, qinv, qaim);
    quatConj(qlinv, qlocal);
    quatMul(rq, qtmp, qlinv);
    convert_from_quater_to_rotXYZ_motion_ik_base(out, rq, obj);
    if (tp.blend_max < 1.553343f) {
        quatAxisY(ydir, qcur);
        vecLerp(out, out, prev, 1.0f - GAMEUTIL_get_dist_ratio(iosGetACosfExact(vecDot(ydir, YUnitVector)), tp.blend_max, 1.553343f));
    }
}
