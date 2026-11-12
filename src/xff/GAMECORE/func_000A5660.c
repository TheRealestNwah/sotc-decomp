typedef int s128 __attribute__((mode(TI)));

extern char *GetLayoutClass(int);
extern void *isysGetThisSubThread(void);
extern void AI_GetVelocity3XYZ(float *, float *, float *, float *, float *, float);
extern void AI_GetPosition3XYZ(float *, float *, float *, float *, float *, float *, float);
extern int AI_GetSideSignalFromDirLev(void *, void *);
extern float AI_GetRotVelocity(float, float, float, float);
extern void AI_UpdateVelocity(float *, float, float);
extern float iosGetACosfExact(float);
extern float iosGetASinfExact(float);
extern float AI_GetVelocity3(float, float, float, float, float);
extern float AI_GetPosition3(float, float, float, float, float, float);
extern s128 ZeroVector;

static inline void normalize3(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

#ifdef NONMATCHING /* 137 diffs, same word count: constant (0.0/1.0) register setup order and call-arg scheduling */
static void func_000A5660(char *p)
{
    float vel[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float nv[4] __attribute__((aligned(16)));
    float t, d, ang, side_f;
    char *obj = GetLayoutClass((int)isysGetThisSubThread());

    t = *(float *)(p + 0x290);
    *(float *)(p + 0x30C) = 1.0f;
    if (t <= *(float *)(p + 0x740)) {
        AI_GetVelocity3XYZ(vel, (float *)(p + 0x6B0), (float *)(p + 0x6C0), (float *)(p + 0x6D0), (float *)(p + 0x6E0), t);
        AI_GetPosition3XYZ(pos, (float *)(p + 0x6B0), (float *)(p + 0x6C0), (float *)(p + 0x6D0), (float *)(p + 0x700), (float *)(p + 0x6E0), t);
        AI_GetVelocity3(*(float *)(p + 0x748), *(float *)(p + 0x74C), *(float *)(p + 0x750), 0.0f, t);
        pos[1] += AI_GetPosition3(*(float *)(p + 0x748), *(float *)(p + 0x74C), *(float *)(p + 0x750), 0.0f, 0.0f, t);
        pos[3] = 1.0f;
        **(s128 **)(obj + 0x134) = *(s128 *)pos;
        *(s128 *)dir = *(s128 *)vel;
        *(s128 *)(p + 0x730) = *(s128 *)vel;
        dir[1] = 0.0f;
        normalize3(dir);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                             "lqc2 vf6, 0x0(%2)
"
                             "vaddw.x vf7, vf0, vf0w
"
                             "vmul.xyz vf6, vf5, vf6
"
                             "vaddax.x ACC, vf0, vf6x
"
                             "vmadday.x ACC, vf7, vf6y
"
                             "vmaddz.x vf6, vf7, vf6z
"
                             "qmfc2.ni %0, vf6
"
                             : "=r"(d) : "r"(dir), "r"(p + 0x240));
        ang = iosGetACosfExact(d);
        {
            int side = AI_GetSideSignalFromDirLev(p + 0x240, dir);
            *(float *)(p + 0x2F0) = d;
            side_f = (float)side;
            *(float *)(p + 0x2F4) =
                AI_GetRotVelocity(*(float *)(p + 0x2F4) * 90.0f * 3.1415927f / 180.0f, ang * side_f, 1.0f, 0.1f) * 180.0f / 282.68f;
        }
        *(float *)(p + 0x300) = 0.0f;
        AI_UpdateVelocity((float *)(p + 0x2FC), 0.0f, 1.0f);
        *(s128 *)nv = *(s128 *)vel;
        normalize3(nv);
        *(float *)(p + 0x304) = iosGetASinfExact(nv[1]);
    } else {
        AI_UpdateVelocity((float *)(p + 0x2F4), 0.0f, 1.0f);
    }
    *(s128 *)(p + 0x2E0) = ZeroVector;
}
#endif
