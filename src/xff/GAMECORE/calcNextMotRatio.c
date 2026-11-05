extern int GetMotionResourceFrames(char *);
extern void PredictMotionGeometryPotentialWithScaleElem(float *, float *, void *, char *, float, float);
extern void GetZDirFromQuaternion(float *, float *);
extern float iosGetATan2fExact(float, float);

static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(v) : "memory");
}

static inline float motYaw(void *a0, char *mot, float s)
{
    float p[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));

    PredictMotionGeometryPotentialWithScaleElem(q, p, a0, mot, 0.0f, s);
    GetZDirFromQuaternion(d, q);
    d[1] = 0.0f;
    vecNormalize(d);
    return -iosGetATan2fExact(d[0], d[2]);
}

float calcNextMotRatio(void *a0, char **m, float cur, float k)
{
    char *mot = m[0];
    float a;
    float r;
    float res;

    GetMotionResourceFrames(mot + 0x50);
    a = motYaw(a0, mot, -1.0f);
    r = motYaw(a0, m[0], *(float *)(m + 3)) * k;
    if (__builtin_fabsf(a) > 0.0001f) {
        if ((cur >= 0.0f && a < 0.0f) || (cur < 0.0f && a >= 0.0f)) {
            if (__builtin_fabsf(cur) >= 150.0f * 0.017453293f)
                res = 1.0f;
            else
                res = __builtin_fabsf(r / a);
        } else {
            res = __builtin_fabsf((cur + r) / a);
        }
        if (!(res > 1.0f))
            return res;
    }
    return 1.0f;
}
