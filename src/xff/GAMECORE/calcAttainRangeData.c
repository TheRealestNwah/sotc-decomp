typedef struct { long long a, b, c, d; } Block32;

extern char ZeroPoint[];
extern float iosGetSinf(float);
extern float iosGetCosf(float);
extern void iosGetLengthPointToLine(void *, void *, void *, void *);

#ifdef NONMATCHING
/* Flag note: 28 diffs with per-file -fno-strict-aliasing (42 without); permuter with the flag reached only 760. */
/* Parked: 42 words differ (copy/compare scheduling, stack vector order, float constant spelling). */
void calcAttainRangeData(char *out, char *in, int flag)
{
    *(long long *)(out + 0x0) = *(long long *)(in + 0x0);
    *(long long *)(out + 0x8) = *(long long *)(in + 0x8);
    *(long long *)(out + 0x10) = *(long long *)(in + 0x10);
    *(long long *)(out + 0x18) = *(long long *)(in + 0x18);
    if (*(float *)(out + 0x18) < 2.3561943f) {
        struct { float q[4]; float p[4]; float d[4]; } L;
        float dist;
        float half;
        float one = 1.0f;
        float lo = *(float *)(out + 0x10);
        float hi = *(float *)(out + 0x14);

        ((int *)L.p)[0] = 0;
        ((int *)L.p)[1] = 0;
        L.p[3] = one;
        L.p[2] = (lo + hi) * 0.5f;
        half = (hi - lo) * 0.5f;
        L.d[0] = -iosGetSinf(*(float *)(out + 0x18));
        ((int *)L.d)[1] = 0;
        L.d[2] = iosGetCosf(*(float *)(out + 0x18));
        L.d[3] = one;
        iosGetLengthPointToLine(L.q, ZeroPoint, L.d, L.p);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vsqrt Q, vf7w\n"
                             "vwaitq\n"
                             "cfc2.ni $2, $22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(dist) : "r"(L.q), "r"(L.p) : "$2", "memory");
        if (dist < half)
            half = dist;
        *(float *)(out + 0x14) = half;
        *(float *)(out + 0x18) = 3.14159274f;
        *(int *)(out + 0x10) = 0;
    }
    {
        float s;
        if (flag != 0)
            s = 0.7f;
        else
            s = 0.799999952f;
        *(float *)(out + 0x14) = *(float *)(out + 0x14) * s;
        *(float *)(out + 0x10) = *(float *)(out + 0x10) * s;
    }
    *(int *)(out + 0x8) = 0;
    *(int *)(out + 0x0) = 0;
}
#else
void calcAttainRangeData(char *out, char *in, int flag);
#endif
