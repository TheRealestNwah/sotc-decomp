typedef int s128 __attribute__((mode(TI)));
typedef struct { int idx; float w; float s; int pad; char data[0x10]; } WindHit;
extern s128 ZeroVector;
extern s128 B_00149AA0;
extern char *B_00149AB0[];
extern WindHit B_00149CC0[];
extern int func_000CACE8(void *);
extern void func_000CBB18(float *, char *, void *, float, float);

static inline void vecScale3(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd3(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vecLen3(float *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

float *GetWindVector(float *len, void *arg)
{
    float tmp[4] __attribute__((aligned(16)));
    int n = func_000CACE8(arg);
    int i;
    int prev = -1;
    int pri;
    float rem = 1.0f;
    float mx = 0.0f;
    WindHit *e;
    char *obj;

    B_00149AA0 = ZeroVector;
    for (i = 0; i < n; i++) {
        e = &B_00149CC0[i];
        obj = B_00149AB0[e->idx];
        pri = **(int **)(obj + 4);
        if (pri != prev) {
            rem -= mx;
            if (rem < 0.001f)
                break;
            mx = e->w;
        } else if (e->w < mx) {
            mx = e->w;
        }
        func_000CBB18(tmp, obj, e->data, e->w, e->s);
        vecScale3(tmp, tmp, rem);
        vecAdd3((float *)&B_00149AA0, (float *)&B_00149AA0, tmp);
        prev = pri;
    }
    if (len != 0)
        *len = vecLen3((float *)&B_00149AA0);
    return (float *)&B_00149AA0;
}
