typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;
extern int GetMotionResourceFrames(int);
extern void GetMotionRootFloatFrame(void *, int, float);
extern int GetMotionRootDirInfo(void *, int, float);
extern void DivQuaternion(void *, void *, void *);
extern char *GetLayoutClass(int);

#ifdef NONMATCHING
/* Parked: ~96 words differ (callee-saved assignment of the stack-buffer pointers and the t1/end copies). */
char *PredictMotionGeometryPotentialWithScaleElem(void *quat, float *vel, int obj, int motion, float t0, float t1)
{
    struct { float p0[4]; float p1[4]; float q0[4]; float q1[4]; } L __attribute__((aligned(16)));
    int m = motion + 0x50;
    float last;
    float end;
    char *scale;

    end = t1;
    last = (float)GetMotionResourceFrames(m);
    if (t0 < 0.0f) {
        t0 = 0.0f;
    } else if (last < t0)
        goto zero;
    GetMotionRootFloatFrame(L.p0, m, t0);
    if (GetMotionRootDirInfo(L.q0, m, t0) == 0)
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(L.q0) : "memory");
    if (t1 < 0.0f || last <= t1)
        end = last;
    GetMotionRootFloatFrame(L.p1, m, end);
    if (GetMotionRootDirInfo(L.q1, m, end) == 0)
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(L.q1) : "memory");
    if (end < t0)
        goto zero;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                         : : "r"(L.p1), "r"(L.p0), "r"(vel) : "memory");
    vel[3] = 0.0f;
    DivQuaternion(quat, L.q0, L.q1);
    goto done;
zero:
    *(s128 *)vel = ZeroVector;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(quat) : "memory");
done:
    scale = GetLayoutClass(obj) + 0x90;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvmul.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%0)\n"
                         : : "r"(vel), "r"(scale) : "memory");
    return scale;
}
#else
char *PredictMotionGeometryPotentialWithScaleElem(void *quat, float *vel, int obj, int motion, float t0, float t1);
#endif
