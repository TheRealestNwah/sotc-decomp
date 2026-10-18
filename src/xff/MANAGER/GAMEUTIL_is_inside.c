typedef int s128 __attribute__((mode(TI)));
extern void iosGetExceptAxisVector(float *, float *, float *);
static inline float distanceSquare(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vsub.xyzw vf07, vf05, vf06\n"
                         "vmul.xyz vf07, vf07, vf07\n"
                         "vaddy.x vf07, vf07, vf07y\n"
                         "vaddz.x vf07, vf07, vf07z\n"
                         "qmfc2 %0, vf07\n"
                         : "=r"(d) : "r"(a), "r"(b));
    return d;
}
int GAMEUTIL_is_inside(void *control, float *a, float *b, float radiusA, float radiusB)
{
    float p[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    char *state = control;
    float radius = radiusA + radiusB;
    float radiusSquare = radius * radius;
    if (*(int *)state) {
        iosGetExceptAxisVector(p, a, (float *)(state + 0x10));
        iosGetExceptAxisVector(q, b, (float *)(state + 0x10));
    } else {
        *(s128 *)p = *(s128 *)a;
        *(s128 *)q = *(s128 *)b;
    }
    return distanceSquare(p, q) <= radiusSquare;
}
