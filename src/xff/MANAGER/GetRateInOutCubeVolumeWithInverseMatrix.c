extern void iosAbsVector(void *, void *);

static inline void vecSub(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

float GetRateInOutCubeVolumeWithInverseMatrix(float *matrix, float *point, float *inner, float *outer)
{
    float local[4] __attribute__((aligned(16)));
    float range[4] __attribute__((aligned(16)));
    float dist[4] __attribute__((aligned(16)));
    float rate;
    float t;

    rate = -1.0f;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(local), "r"(matrix), "r"(point) : "memory");
    iosAbsVector(local, local);
    if (local[0] <= outer[0] && local[1] <= outer[1] && local[2] <= outer[2]) {
        if (local[0] <= inner[0] && local[1] <= inner[1] && local[2] <= inner[2]) {
            rate = 1.0f;
        } else {
            rate = 1.0f;
            vecSub(range, outer, inner);
            vecSub(dist, local, inner);
            vecSub(dist, range, dist);
            if (local[0] > inner[0])
                rate = dist[0] / range[0];
            if (local[1] > inner[1]) {
                t = dist[1] / range[1];
                if (t <= rate)
                    rate = t;
            }
            if (local[2] > inner[2]) {
                t = dist[2] / range[2];
                if (t <= rate)
                    rate = t;
            }
        }
    }
    return rate;
}
