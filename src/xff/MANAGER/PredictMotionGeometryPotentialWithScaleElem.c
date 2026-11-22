typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern s128 ZeroVector;
extern int GetMotionResourceFrames(int);
extern void GetMotionRootFloatFrame(void *, int, float);
extern int GetMotionRootDirInfo(void *, int, float);
extern void DivQuaternion(void *, void *, void *);
extern char *GetLayoutClass(int);

static inline void unitQuat(void *q)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(q) : "memory");
}

#ifdef NONMATCHING
/* Parked: 6 diffs (was ~96). TImode stack buffers keep their addresses rematerialized like the Original, and end, m and vel are pinned. Remaining: the stack slots of p1 and q0 are swapped (gcc gives slots in first-address-taken order: p0, q0, p1, q1; the Original has p0, p1, q0, q1). */
char *PredictMotionGeometryPotentialWithScaleElem(Vec4 *quat, Vec4 *vel_, int obj, int motion, float t0, float t1)
{
    register Vec4 *vel __asm__("$16") = vel_;
    s128 p0;
    s128 p1;
    s128 q0;
    s128 q1;
    int m;
    int frames;
    register float end __asm__("$f22");
    char *scale;

    m = motion + 0x50;
    end = t1;
    frames = GetMotionResourceFrames(m);
    if (t0 < 0.0f) {
        t0 = 0.0f;
    } else if (frames < t0) {
        goto zero;
    }
    GetMotionRootFloatFrame(&p0, m, t0);
    if (GetMotionRootDirInfo(&q0, m, t0) == 0) {
        void *q = &q0;
        unitQuat(q);
    }
    if (t1 < 0.0f || frames <= t1) {
        end = frames;
    }
    GetMotionRootFloatFrame(&p1, m, end);
    if (GetMotionRootDirInfo(&q1, m, end) == 0) {
        void *q = &q1;
        unitQuat(q);
    }
    if (end < t0) {
zero:
        *(s128 *)vel = ZeroVector;
        unitQuat(quat);
    } else {
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\nlqc2 vf6, 0x0(%2)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%0)\n"
                             : : "r"(vel), "r"(&p1), "r"(&p0) : "memory");
        vel->w = 0.0f;
        DivQuaternion(quat, &q0, &q1);
    }
    scale = GetLayoutClass(obj) + 0x90;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvmul.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%0)\n"
                         : : "r"(vel), "r"(scale) : "memory");
    return scale;
}
#else
char *PredictMotionGeometryPotentialWithScaleElem(Vec4 *quat, Vec4 *vel, int obj, int motion, float t0, float t1);
#endif
