typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

extern char *GetLayoutClass(int);
extern int getRootPointIdxForGroupID(char *, int, int, int *);
extern void resetAttackWork(int);
extern void func_000FC0C0(char *);
extern void setUserPathMode(char *, int);
extern void func_000FC310(char *, char *, char *);
extern void func_000FC1A0(char *, char *);
extern void func_000FC0D0(char *, char *);
extern int func_000FB928(char *, char *, int, int, int);
extern void func_000FC070(char *);
extern float *getGoalPointDataByAreaIdx(char *, int, int);
extern float *getSubPointDataByAreaIdx(char *, int, int);
extern int getPathColiGroup(char *);
extern int pathDetectCollision2(char *, float *, float *, float *, int);
extern void setAttainmentPos(char *, float *);
extern void setAttainmentPosAndDir(char *, float *, float *);
extern void setAttainmentPosAndDirAndLock(char *, float *, float *);
extern void setAttainmentPosAndDirPos(char *, float *, float *);
extern void setAttainmentObj(char *, int);
extern void updateAttackWork2(int, int);
extern void updateAttackWork(int, int);
extern int getWayFinish(char *);
extern int getPassageNum(char *);
extern float iosGetCosf(float);
extern void updateUserPathWork(int, char *);

static inline void vecSub(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}
static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}
static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}
static inline float vecDot(float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

#define W(type, o) (*(type *)(w + (o)))

void updateUserPathWorkEx(int owner, char *w, int target)
{
    int done = 0;
    char *lay = GetLayoutClass(owner);
    char *tlay = GetLayoutClass(target);
    int changed = 0;
    VecQ a;
    VecQ b;
    VecQ c;
    float *goal;
    float *sp;
    int n;

    W(int, 0x3CA4) = 0;
    W(int, 0x3CA8) = 0;
    W(int, 0x3CAC) = 0;
    if (W(long, 0x3C68) != W(long, 0x3C70) || W(int, 0x3C7C) != 0) {
        W(int, 0x3C88) = getRootPointIdxForGroupID(w, W(int, 0x3C68), W(int, 0x3C6C), &W(int, 0x3C8C));
        changed = 1;
    }
    if (W(int, 0x3C60) != W(int, 0x3C64) || changed) {
        resetAttackWork(owner);
        switch (W(int, 0x3C60)) {
        case -1:
            func_000FC0C0(w);
            setUserPathMode(w, -1);
            break;
        case 0:
            func_000FC0C0(w);
            setUserPathMode(w, 0);
            break;
        case 1:
            func_000FC0C0(w);
            setUserPathMode(w, 1);
            break;
        case 2:
        case 3:
        case 4:
            func_000FC310(w, lay, tlay);
            func_000FC1A0(w, lay);
            break;
        case 5:
        case 8:
            func_000FC310(w, lay, tlay);
            goal = getGoalPointDataByAreaIdx(w, W(int, 0x3C90), W(int, 0x3C8C));
            sp = getSubPointDataByAreaIdx(w, W(int, 0x3C98), W(int, 0x3C8C));
            if (goal == 0)
                break;
            if (sp == 0 && W(int, 0x3C60) == 8) {
                func_000FC1A0(w, lay);
                sp = getSubPointDataByAreaIdx(w, W(int, 0x3C98), W(int, 0x3C8C));
            }
            if (sp != 0 && W(int, 0x3C90) == *(short *)((char *)sp + 0x18)) {
                vecSub(b.f, goal, sp);
                b.f[1] = 0.0f;
                vecNormalize(b.f);
                if (pathDetectCollision2(w, a.f, sp, goal, getPathColiGroup(w)))
                    c.q = a.q;
                else
                    c.q = *(u_long128 *)goal;
                if (W(int, 0x3C60) == 5)
                    setAttainmentPos(w, c.f);
                else
                    setAttainmentPosAndDir(w, c.f, b.f);
            } else {
                setAttainmentPos(w, goal);
            }
            setUserPathMode(w, 0);
            break;
        case 6:
            func_000FC310(w, lay, tlay);
            sp = getGoalPointDataByAreaIdx(w, W(int, 0x3C90), W(int, 0x3C8C));
            if (sp == 0)
                break;
            vecSub(b.f, *(float **)(GetLayoutClass(owner) + 0x134), sp);
            b.f[1] = 0.0f;
            vecNormalize(b.f);
            vecScale(a.f, b.f, W(float, 0x3C84));
            vecAdd(a.f, a.f, sp);
            a.f[3] = 1.0f;
            vecScale(b.f, b.f, -1.0f);
            b.f[3] = 1.0f;
            setAttainmentPosAndDirAndLock(w, a.f, b.f);
            setUserPathMode(w, 0);
            break;
        case 7:
            func_000FC310(w, lay, tlay);
            func_000FC0D0(w, tlay);
            break;
        case 9:
            W(int, 0x3CB0) = 0;
            func_000FC310(w, lay, tlay);
            W(int, 0x3C9C) = func_000FB928(w, lay, W(int, 0x3C90), -1, W(int, 0x3C8C));
            func_000FC070(w);
            break;
        case 10:
            func_000FC0C0(w);
            setAttainmentObj(w, target);
            setUserPathMode(w, 0);
            break;
        }
        done = 1;
    }
    if (!done) {
        switch (W(int, 0x3C60)) {
        case -1:
        case 0:
        case 1:
            updateAttackWork2(owner, target);
            break;
        case 2:
        case 3:
        case 4:
            updateAttackWork2(owner, target);
            if (W(int, 0x3C98) == -1)
                break;
            sp = getSubPointDataByAreaIdx(w, W(int, 0x3C98), W(int, 0x3C8C));
            goal = getGoalPointDataByAreaIdx(w, W(int, 0x3C90), W(int, 0x3C8C));
            if (getWayFinish(w)) {
                W(int, 0x3CA8) = 1;
                break;
            }
            n = getPassageNum(w);
            if (n != 1)
                break;
            vecSub(a.f, sp, *(float **)(lay + 0x134));
            vecSub(b.f, goal, sp);
            vecNormalize(a.f);
            vecNormalize(b.f);
            if (W(int, 0x3C60) == 2) {
                if (iosGetCosf(sp[5] * 0.017453292519943295f) < vecDot(a.f, b.f)) {
                    W(int, 0x3CA0) = n;
                    setAttainmentPosAndDirPos(w, sp, goal);
                } else {
                    W(int, 0x3CA0) = 0;
                    setAttainmentPos(w, sp);
                }
            } else if (W(int, 0x3C60) == 3) {
                setAttainmentPosAndDirPos(w, sp, goal);
            } else {
                setAttainmentPosAndDirPos(w, sp, goal);
                if (iosGetCosf(sp[5] * 0.017453292519943295f) < vecDot(a.f, b.f))
                    W(int, 0x3CA0) = n;
                else
                    W(int, 0x3CA0) = 0;
            }
            break;
        case 5:
        case 6:
        case 8:
            updateAttackWork2(owner, target);
            if (W(int, 0x3C90) == -1)
                break;
            if (getWayFinish(w))
                W(int, 0x3CA4) = 1;
            break;
        case 7:
            updateAttackWork2(owner, target);
            if (W(int, 0x3C90) == -1)
                break;
            if (getWayFinish(w))
                W(int, 0x3CA4) = 1;
            func_000FC0D0(w, tlay);
            break;
        case 9:
            updateAttackWork2(owner, target);
            if (W(int, 0x3C9C) == -1)
                break;
            if (getWayFinish(w)) {
                W(int, 0x3C9C) = func_000FB928(w, lay, W(int, 0x3C90), W(int, 0x3C9C), W(int, 0x3C8C));
                func_000FC070(w);
                W(int, 0x3CAC) = 1;
                W(int, 0x3CB0)++;
            }
            break;
        case 10:
            updateAttackWork(owner, target);
            break;
        }
    }
    W(int, 0x3C64) = W(int, 0x3C60);
    W(int, 0x3C70) = W(int, 0x3C68);
    W(int, 0x3C74) = W(int, 0x3C6C);
    W(int, 0x3C7C) = 0;
    updateUserPathWork(owner, w);
}
