typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));

extern s128 ZeroVector;
extern void GetGeometryPointerPosition(void *, void *);
extern void *GetGeometryPointerSurfacePlane(void *);
extern int getAverageNormal(void *, float, void *, int, void *, float, float, int, int, void *);
extern void CompletePlaneD(void *, void *);
extern float GetPointDistanceFromPlane(void *, void *);
extern void GetPlaneFittingDiffVector(void *, void *, void *);

/* Parked: 2 words differ (the last loop forms base+index as (sp+index)+0x10 instead of (sp+0x10)+index). The getAverageNormal prototype order and the $3 pin on acc were found by search. */
#ifdef NONMATCHING
int charrootdyn_getCompleteFittingPlaneFromStabGPWithSlopeLimit(void *obj, s128 *out, void *gp, int p3, int p4, int p5, float lim0, float lim1)
{
    struct { Vec4 pos; Vec4 n[4]; Vec4 sum; } L;
    int r;
    int i;
    float *sum;
    register float *acc __asm__("$3");
    float *cur;

    GetGeometryPointerPosition(L.pos, gp);
    r = getAverageNormal(obj, lim0, L.n[0], p4, L.pos, lim0, lim1, p3, p5, GetGeometryPointerSurfacePlane(gp));
    *(s128 *)L.sum = *(s128 *)L.n[0];
    sum = L.sum;
    acc = sum;
    cur = L.n[1];
    i = 2;
    do {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(acc), "r"(cur) : "memory");
        i--;
        cur += 4;
    } while (i >= 0);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(sum), "r"(0.25f) : "memory");
    i = 0;
    CompletePlaneD(obj, L.sum);
    if (GetPointDistanceFromPlane(obj, L.pos) > 0.0f) {
        *out = ZeroVector;
    } else {
        while (i < 4) {
            float *p = L.n[i];

            i++;
            if (GetPointDistanceFromPlane(obj, p) > 0.0f)
                CompletePlaneD(obj, p);
        }
        GetPlaneFittingDiffVector(out, obj, L.pos);
    }
    return r;
}
#else
extern int charrootdyn_getCompleteFittingPlaneFromStabGPWithSlopeLimit(void *obj, s128 *out, void *gp, int p3, int p4, int p5, float lim0, float lim1);
#endif
