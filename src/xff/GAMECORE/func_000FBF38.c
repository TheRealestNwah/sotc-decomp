typedef struct {
    char pad0[0x14];
    unsigned int count;
} GoalPoint;

typedef struct {
    float pos[4];
    int flags;
} SubPoint;

static const union {
    int i;
    float f;
} RO_00181394 = { 0x7FFFFFFF };

extern GoalPoint *getGoalPointDataByAreaIdx(char *, int, int);
extern short *getChildSubPointIdxArrayByAreaIdx(char *, int, int);
extern SubPoint *getSubPointDataByAreaIdx(char *, int, int);

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

static int func_000FBF38(char *w, char *lay, int area, int idx)
{
    GoalPoint *goal = getGoalPointDataByAreaIdx(w, area, idx);
    short *child = getChildSubPointIdxArrayByAreaIdx(w, area, idx);
    float best = RO_00181394.f;
    int sel = -1;
    unsigned int i;

    if (goal == 0 || child == 0)
        return -1;
    for (i = 0; i < goal->count; i++) {
        SubPoint *sp = getSubPointDataByAreaIdx(w, child[i], idx);
        float d = dist(sp->pos, *(float **)(lay + 0x134));

        if (d < best && (sp->flags & 1)) {
            sel = child[i];
            best = d;
        }
    }
    return sel;
}
