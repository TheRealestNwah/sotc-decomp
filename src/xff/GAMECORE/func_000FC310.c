typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

typedef struct {
    char pad0[0x14];
    unsigned int childCount;
} RootPoint;

extern const float RO_0018139C;
extern RootPoint *getRootPointDataByAreaIdx(void *, int, int);
extern short *getChildGoalPointIdxArrayByAreaIdx(void *, int, int);
extern float *getGoalPointDataByAreaIdx(void *, int, int);
extern int func_000FC4B8(void *, void *, void *, int, int);

static inline float vecDist(float *a, float *b)
{
    float length;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(length) : "r"(a), "r"(b) : "$2");
    return length;
}

#define W(type, o) (*(type *)(work + (o)))

static void func_000FC310(char *work, char *a, char *b)
{
    VecQ pos;
    RootPoint *root;
    short *child;
    float best;
    float d;
    unsigned int i;
    int sel;
    int area;
    int sub;
    int goal;

    if (W(int, 0x3C80) == 0)
        return;
    area = W(int, 0x3C88);
    sub = W(int, 0x3C8C);
    sel = -1;
    root = getRootPointDataByAreaIdx(work, area, sub);
    child = getChildGoalPointIdxArrayByAreaIdx(work, area, sub);
    best = RO_0018139C;
    if (root == 0 || child == 0) {
        goal = -1;
    } else {
        if (W(int, 0x3C78) == 0)
            pos.q = **(u_long128 **)(a + 0x134);
        else
            pos.q = **(u_long128 **)(b + 0x134);
        for (i = 0; i < root->childCount; i++) {
            d = vecDist(getGoalPointDataByAreaIdx(work, child[i], sub), pos.f);
            if (d < best) {
                sel = child[i];
                best = d;
            }
        }
        goal = sel;
    }
    if (W(int, 0x3C94) == W(int, 0x3C88) && W(int, 0x3C90) != -1 && W(int, 0x3C90) != goal) {
        if (func_000FC4B8(work, a, b, W(int, 0x3C90), goal) == 0)
            return;
        W(int, 0x3C90) = goal;
        W(int, 0x3C94) = W(int, 0x3C88);
        return;
    }
    W(int, 0x3C90) = goal;
    W(int, 0x3C94) = W(int, 0x3C88);
}
