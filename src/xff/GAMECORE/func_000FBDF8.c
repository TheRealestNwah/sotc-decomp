typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x14];
    unsigned int count;
} RootPoint;

typedef union {
    float f[4];
    s128 q;
} V4;

static const union {
    int i;
    float f;
} RO_00181390 = { 0x7FFFFFFF };

extern RootPoint *getRootPointDataByAreaIdx(char *, int, int);
extern short *getChildGoalPointIdxArrayByAreaIdx(char *, int, int);
extern float *getGoalPointDataByAreaIdx(char *, int, int);

static inline float dist(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static int func_000FBDF8(char *w, char *lay, int area, int idx, char *lay2)
{
    RootPoint *root = getRootPointDataByAreaIdx(w, area, idx);
    short *child = getChildGoalPointIdxArrayByAreaIdx(w, area, idx);
    float best = RO_00181390.f;
    int sel = -1;
    unsigned int i;
    V4 pos;

    if (root == 0 || child == 0)
        return -1;
    if (*(int *)(w + 0x3C78) == 0)
        pos.q = **(s128 **)(lay + 0x134);
    else
        pos.q = **(s128 **)(lay2 + 0x134);
    for (i = 0; i < root->count; i++) {
        float d = dist(getGoalPointDataByAreaIdx(w, child[i], idx), pos.f);

        if (d < best) {
            sel = child[i];
            best = d;
        }
    }
    return sel;
}
