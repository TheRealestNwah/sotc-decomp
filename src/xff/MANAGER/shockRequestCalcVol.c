#ifdef NONMATCHING /* pattern copy from rodata is scheduled before the flags load; original loads flags first */
typedef struct ShockPattern {
    unsigned char data[4];
} ShockPattern;

typedef struct ShockParam {
    char pad0[4];
    short port;
    unsigned short flags;
    float inner;
    float outer;
} ShockParam;

extern int **D_001396A0;
extern int D_001396A8;
extern char iosDefaultPadData[];
extern int Shock_Request(void *pad, int port, ShockPattern pattern, int id, int flag);
extern void testGetCamPos(void *, void *);

static inline float squareLength(float *v)
{
    float r;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         ".set reorder\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline void subVector(float *out, float *a, float *b)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

int shockRequestCalcVol(ShockParam *param, float *pos)
{
    ShockPattern pattern = {{0, 0, 0xFF, 0x40}};
    void *pad = iosDefaultPadData + 0x58;
    int port = param->port;
    int result = 0;

    if (param->flags % 2 == 1) {
        float cam[4] __attribute__((aligned(16)));
        float mtx[16] __attribute__((aligned(16)));
        float diff[4] __attribute__((aligned(16)));
        float inner = param->inner * param->inner;
        float outer = param->outer * param->outer;
        float d;

        testGetCamPos(cam, mtx);
        subVector(diff, pos, cam);
        d = squareLength(diff);
        if (!(d < inner)) {
            if (!(d < outer)) {
                return 0;
            }
            pattern.data[2] = (int)((1.0f - (d - inner) / (outer - inner)) * 255.0f);
        }
    }
    if (D_001396A0 != 0) {
        if (*D_001396A0 != 0)
            result = Shock_Request(pad, port, pattern, D_001396A8++, 0);
    }
    return result;
}
#endif
