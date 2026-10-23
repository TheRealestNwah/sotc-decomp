typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    Vec4 current;
    Vec4 previous;
    int updated;
    float threshold;
} PositionFilter;

static inline float distanceSquared(void *a, void *b)
{
    float distance;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(distance) : "r"(a), "r"(b) : "$2");
    return distance;
}
int GAMEUTIL_doit_position_filter(PositionFilter *filter, Vec4 *position, int mode)
{
    if (mode == 1 || distanceSquared(filter, position) >= filter->threshold * filter->threshold) {
        filter->previous.q = filter->current.q;
        filter->current.q = position->q;
        filter->updated = 1;
    } else {
        filter->updated = 0;
    }
    return filter->updated;
}
