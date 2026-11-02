extern void PredictMotionGeometryPotentialWithScaleElem(float *, float *, void *, char *, float, float);
extern float GetMotionStretchRatio(char *);
extern void GetZDirFromQuaternion(float *, float *);
extern float iosGetATan2fExact(float, float);

void analyzeMotionProperty2(void *obj, char *elem, float *len, float *speed, float *yaw, float scale, float from,
                            float to)
{
    float pos[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float frames = (float)*(int *)(elem + 0x5C) * scale;

    PredictMotionGeometryPotentialWithScaleElem(quat, pos, obj, elem, from, to);
    if (len != 0) {
        float l;

        __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vsqrt Q, vf7w\n"
                             "vwaitq\n"
                             "cfc2 $2, $vi22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(l) : "r"(pos) : "$2");
        *len = l;
    }
    if (speed != 0)
        *speed = (to - from) / GetMotionStretchRatio(elem + 0x50) / frames;
    if (yaw != 0) {
        GetZDirFromQuaternion(dir, quat);
        dir[1] = 0.0f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(dir) : "memory");
        *yaw = -iosGetATan2fExact(dir[0], dir[2]);
    }
}
