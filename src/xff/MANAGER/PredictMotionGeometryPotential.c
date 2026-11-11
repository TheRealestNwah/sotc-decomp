typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern Vec4 ZeroVector;

extern int GetMotionResourceFrames(void *motion);
extern void GetMotionRootFloatFrame(Vec4 *out, void *motion, float frame);
extern int GetMotionRootDirInfo(Vec4 *out, void *motion, float frame);
extern void DivQuaternion(Vec4 *out, Vec4 *a, Vec4 *b);

static inline void unitQuat(Vec4 *q)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(q) : "memory");
}

static inline void subVec(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

#ifdef NONMATCHING
/* 9 diffs: rot and the first quaternion buffer swap saved registers s3/s4. Permuter (5 workers, 25 min) reported a better score from unitQuat(rot), but it is still 9 diffs here. */
void PredictMotionGeometryPotential(Vec4 *rot, Vec4 *trans, char *obj, float start, float end)
{
    Vec4 *r = rot;
    Vec4 p0;
    Vec4 p1;
    Vec4 q0;
    Vec4 q1;
    void *motion;
    int frames;

    motion = obj + 0x50;
    frames = GetMotionResourceFrames(motion);
    if (start < 0.0f) {
        start = 0.0f;
    } else if (frames < start) {
        goto zero;
    }
    GetMotionRootFloatFrame(&p0, motion, start);
    if (GetMotionRootDirInfo(&q0, motion, start) == 0) {
        unitQuat(&q0);
    }
    if (end < 0.0f || frames <= end) {
        end = frames;
    }
    GetMotionRootFloatFrame(&p1, motion, end);
    if (GetMotionRootDirInfo(&q1, motion, end) == 0) {
        unitQuat(&q1);
    }
    if (end < start) {
zero:
        *(s128 *)trans = *(s128 *)&ZeroVector;
        unitQuat(r);
        return;
    }
    subVec(trans, &p1, &p0);
    trans->w = 0.0f;
    DivQuaternion(r, &q0, &q1);
}
#endif
