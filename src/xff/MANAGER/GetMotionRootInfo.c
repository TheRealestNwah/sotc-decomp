typedef int s128 __attribute__((mode(TI)));

extern void GetMotionRootIntFrame(void *, void *, int);
extern void GetMotionRootFloatFrame(void *, void *, float);
extern int GetMotionResourceFrames(void *);

static inline void vecSub(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

void GetMotionRootInfo(float *pos, float *delta, void *motion, float frame, float prevFrame, float scale)
{
    s128 prev;
    s128 first;
    s128 last;
    s128 tail;
    s128 head;

    GetMotionRootFloatFrame(pos, motion, frame);
    GetMotionRootFloatFrame(&prev, motion, prevFrame);
    if (prevFrame <= frame) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(delta), "r"(pos), "r"(&prev) : "memory");
    } else {
        GetMotionRootIntFrame(&first, motion, 0);
        GetMotionRootIntFrame(&last, motion, GetMotionResourceFrames(motion));
        vecSub(&tail, &last, &prev);
        vecSub(&head, pos, &first);
        vecAdd(delta, &tail, &head);
    }
    __asm__ __volatile__("mfc1 $2, %1\n"
                         "lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(delta), "f"(scale) : "$2", "memory");
    delta[3] = 0.0f;
}
