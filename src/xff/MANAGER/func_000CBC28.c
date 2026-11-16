/* Distance ratio of a point against an object's near/far range. */
static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecLenSq(float *v)
{
    float r;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

typedef struct {
    char pad0[4];
    int *info;
    char pad8[0xB0 - 0x8];
    float pos[4];
    char padC0[0x100 - 0xC0];
    float lo;
    float hi;
} RangeObj;

static float func_000CBC28(float *dist, float *diff, float *pos, RangeObj *o)
{
    float r = 1.0f;

    if (o->info[1] != 0) {
        vecSubXYZ(diff, pos, o->pos);
        *dist = vecLenSq(diff);
        r = -1.0f;
    }
    if (r < 0.0f) {
        float lo = o->lo;
        float hi = o->hi;
        float d = *dist;

        if (lo <= hi) {
            if (hi <= d)
                r = 0.0f;
            else if (d <= lo)
                r = 1.0f;
            else
                r = (hi - d) / (hi - lo);
        } else {
            if (lo <= d)
                r = 0.0f;
            else if (d <= hi)
                r = 0.0f;
            else
                r = 1.0f - (lo - d) / (lo - hi);
        }
    }
    return r;
}
