typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern char *getPointDataByAreaIdx(char *, int, int);
extern unsigned short *getConnectLineArrayByAreaIdx(char *, int, int);
extern char *getLineDataByAreaIdx(char *, int, int);
extern void *getPathColiGroup(char *);
extern int ClipCollisionDirect(void *, void *, void *, void *);

static inline void vecSubXYZW(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDot(float *a, float *b)
{
    float dot;
    float result;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline void vecNormalize(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "memory");
}

typedef struct { short x, y; int pad; } Area;

int getAttainInversePos(char *w, float *p, unsigned max, u_long128 *out)
{
    Vec4 d0;
    Vec4 d1;
    char clip[0x50] __attribute__((aligned(16)));
    unsigned cnt = 0;
    int found = 0;
    unsigned i;
    unsigned *cp = (unsigned *)(w + 0x434);
    Area *a = (Area *)(w + 0x438);

    vecSubXYZW(d0, p, (float *)w);
    d0[1] = 0;
    vecNormalize(d0, d0);
    for (i = 0; i < *cp; i++) {
        char *pt = getPointDataByAreaIdx(w, a[i].x, a[i].y);
        unsigned short *ln = getConnectLineArrayByAreaIdx(w, a[i].x, a[i].y);
        int ok = 0;
        unsigned j;

        for (j = 0; j < *(unsigned *)(pt + 0x10); j++) {
            if (!(*(int *)(getLineDataByAreaIdx(w, *ln++, a[i].y) + 8) & 4)) {
                ok = 1;
                break;
            }
        }
        if (ok && (*(int *)(pt + 0x18) & 1)) {
            vecSubXYZW(d1, (float *)pt, (float *)w);
            d1[1] = 0;
            vecNormalize(d1, d1);
            if (vecDot(d0, d1) < 0.0f) {
                cnt++;
                if (!ClipCollisionDirect(clip, w, pt, getPathColiGroup(w))) {
                    found = 1;
                    *out = *(u_long128 *)pt;
                }
                if (!(cnt < max))
                    return found;
            }
        }
    }
    return 0;
}
