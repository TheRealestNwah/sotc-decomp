typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { s128 q[4]; float f[16]; } Matrix;

extern Vec4 ZUnitVector;
extern float iosGetACosfExact(float);
extern void iosRotMatrixX(float *, float);
extern void iosApplyRotMatrix(void *, void *, void *);

static inline int nearlyZero(float value, float tolerance)
{
    if (value < 0.0f) {
        if (-value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    } else {
        if (value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    }
nearZero:
    return 1;
notNearZero:
    return 0;
}

static inline float getPitch(Vec4 *v)
{
    float p = iosGetACosfExact(v->f[2]);
    if (v->f[1] < 0.0f)
        p = -p;
    if (p > 1.4835299f)
        p = 1.4835299f;
    else if (p < -1.4835299f)
        p = -1.4835299f;
    return p;
}

/* Inline helpers taking the matrix by pointer keep gcc from caching its
   stack address in a saved register across the two calls. */
static inline void rotApplyM(Matrix *mm, Vec4 *out, float a, Vec4 *in)
{
    iosRotMatrixX(mm->f, a);
    iosApplyRotMatrix(out, mm, in);
}

static inline void rotApplyZ(Matrix *mm, Vec4 *out, float a)
{
    iosRotMatrixX(mm->f, a);
    iosApplyRotMatrix(out, mm, &ZUnitVector);
}

static inline void getPitchDir(Vec4 *out, float pitch)
{
    Matrix m;
    if (nearlyZero(pitch, 0.0001f) == 1) {
        out->q = ZUnitVector.q;
    } else {
        if (pitch > 1.4835299f)
            pitch = 1.4835299f;
        else if (pitch < -1.4835299f)
            pitch = -1.4835299f;
        iosRotMatrixX(m.f, -pitch);
        iosApplyRotMatrix(out, &m, &ZUnitVector);
    }
}

/* Shares the function-scope matrix, so the limit paths cross-jump into one copy. */
#define applyLimit(L) ({                        \
    float limit = (L);                          \
    if (nearlyZero(limit, 0.0001f) == 1) {      \
        out->q = ZUnitVector.q;                 \
    } else {                                    \
        if (limit > 1.4835299f)                 \
            limit = 1.4835299f;                 \
        else if (limit < -1.4835299f)           \
            limit = -1.4835299f;                \
        rotApplyZ(&m2, out, -limit);            \
    }                                           \
})

int GAMEUTIL_act_pitch_rot(Vec4 *out, Vec4 *cur, int clip, float speed, float lo, float hi)
{
    int r = 0;
    Vec4 tmp;
    Matrix m;
    Matrix m2;
    float p, p2;

    if (nearlyZero(speed, 0.0001f) == 1) {
        out->q = cur->q;
    } else {
        if (1.4835299f < lo)
            lo = 1.4835299f;
        else if (hi < -1.4835299f)
            hi = -1.4835299f;
        tmp.q = cur->q;
        p = getPitch(&tmp);
        r = 1;
        rotApplyM(&m, out, -speed, &tmp);
        if (lo < p) {
            if (0.0f <= speed) {
                out->q = tmp.q;
                r = 0;
            } else if (clip) {
                p2 = getPitch(out);
                if (p2 < lo)
                    applyLimit(lo);
            }
        } else if (p < hi) {
            if (speed <= 0.0f) {
                out->q = tmp.q;
                r = 0;
            } else if (clip) {
                p2 = getPitch(out);
                if (hi < p2)
                    applyLimit(hi);
            }
        } else {
            p2 = getPitch(out);
            if (lo < p2)
                applyLimit(lo);
            else if (p2 < hi)
                getPitchDir(out, hi);
        }
    }
    return r;
}
