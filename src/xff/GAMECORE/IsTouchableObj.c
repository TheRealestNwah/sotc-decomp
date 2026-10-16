extern char *GetLayoutClass(void *);
extern void SCRGetDir(float *, void *);
extern float SCRGetAngle(float *, float *, float *);

int IsTouchableObj(void *obj, void *target, float near, float far, float angle)
{
    char *ct = GetLayoutClass(target);
    char *co = GetLayoutClass(obj);
    float d;
    float dir[4] __attribute__((aligned(16)));

    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vsub.xyzw vf6, vf4, vf5\n"
                         "vmul.xyz vf6, vf6, vf6\n"
                         "vaddz.x vf6, vf6, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d)
                         : "r"(*(float **)(co + 0x134)), "r"(*(float **)(ct + 0x134))
                         : "$2");
    if (near * near < d && d < far * far) {
        SCRGetDir(dir, obj);
        if (__builtin_fabsf(SCRGetAngle(*(float **)(co + 0x134), dir, *(float **)(ct + 0x134))) < angle)
            return 1;
    }
    return 0;
}
