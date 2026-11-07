typedef struct {
    char pad0[4];
    int enabled;
} Info;

typedef struct {
    char pad0[4];
    Info *info;
    char pad8[0xB0 - 8];
    float center[4];
    char padC0[0x100 - 0xC0];
    float inv[16];
    float min[4];
    float max[4];
    float limit;
} Volume;

extern float GetRateInOutCubeVolumeWithInverseMatrix(float *, void *, void *, void *);

static float func_000CBD28(float *dist, float *diff, float *pos, Volume *vol)
{
    float r = 1.0f;

    if (vol->info->enabled != 0) {
        float d;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                             "lqc2 vf6, 0x0(%2)
"
                             "vsub.xyz vf5, vf5, vf6
"
                             "sqc2 vf5, 0x0(%3)
"
                             "lqc2 vf7, 0x0(%3)
"
                             "vmul.xyz vf7, vf7, vf7
"
                             "vaddy.x vf7, vf7, vf7y
"
                             "vaddz.x vf7, vf7, vf7z
"
                             "qmfc2.ni $2, vf7
"
                             "mtc1 $2, %0
"
                             : "=f"(d)
                             : "r"(pos), "r"(vol->center), "r"(diff)
                             : "$2", "memory");
        *dist = d;
        do {
        } while (0);
        r = -1.0f;
    }
    if (r < 0.0f) {
        r = 0.0f;
        if (!(vol->limit <= *dist)) {
            r = GetRateInOutCubeVolumeWithInverseMatrix(vol->inv, pos, vol->min, vol->max);
            if (r < 0.0f)
                r = 0.0f;
        }
    }
    return r;
}
