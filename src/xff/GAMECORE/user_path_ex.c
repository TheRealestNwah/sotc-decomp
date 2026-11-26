typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef int s128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

typedef union {
    float f[4];
    s128 q;
} V4;

typedef struct {
    char pad0[0x14];
    unsigned int count;
} RootPoint;

typedef struct {
    char pad0[0x14];
    unsigned int count;
} GoalPoint;

typedef struct {
    float pos[4];
    int flags;
} SubPoint;

typedef struct UserPathWork {
    char pad0000[0x3C60];
    int path[6];
    int field3C78;
    int field3C7C;
    int field3C80;
    int field3C84;
    int link[3];
    int field3C94;
    char pad3C98[8];
    int field3CA0;
    int field3CA4;
    int field3CA8;
    int field3CAC;
    int field3CB0;
} UserPathWork;

typedef struct {
    char pad0[0x3CA4];
    int f3CA4;
    int f3CA8;
    int f3CAC;
} PathEx;

static const int RO_00181300 = 20;
static const float RO_00181304 = 0.5f;
static const int RO_0018139C;

extern char *GetLayoutClass();
extern int getRootPointIdxForGroupID(char *, int, int, int *);
extern void resetAttackWork(int);
extern void setUserPathMode(void *, int);
extern void *getGoalPointDataByAreaIdx(void *, int, int);
extern void *getSubPointDataByAreaIdx(void *, int, int);
extern void *getRootPointDataByAreaIdx(void *, int, int);
extern short *getChildSubPointIdxArrayByAreaIdx(void *, int, int);
extern short *getChildGoalPointIdxArrayByAreaIdx(void *, int, int);
extern int getPathColiGroup(char *);
extern int pathDetectCollision2(char *, float *, float *, float *, int);
extern void setAttainmentPos(void *, void *);
extern void setAttainmentPosAndDir(void *, float *, float *);
extern void setAttainmentPosAndDirAndLock(char *, float *, float *);
extern void setAttainmentPosAndDirPos(char *, float *, float *);
extern void setAttainmentObj(char *, int);
extern void updateAttackWork2(int, int);
extern void updateAttackWork(int, int);
extern int getWayFinish(char *);
extern int getPassageNum(char *);
extern float iosGetCosf(float);
extern float iosGetRandom(void);
extern void updateUserPathWork(int, char *);
extern void createUserPathWork(int, UserPathWork *, float, float, int);
extern void createAttackWork(int);
extern void deleteUserPathWork(char *);

static int func_000FB928(char *w, char *lay, int area, int cur, int stage);
static int func_000FBDF8(char *, char *, int, int, char *);
static int func_000FBF38(char *, char *, int, int);
static int func_000FC070(char *w);
static void func_000FC0C0(char *p);
static void func_000FC0D0(char *w, char *layout);
static void func_000FC1A0(char *w, char *lay);
static void func_000FC310(char *w, char *a, char *b);
static int func_000FC4B8(char *w, char *lay, char *lay2, int g1, int g2);

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

static int func_000FB928(char *w, char *lay, int area, int cur, int stage)
{
    int n = 0;
    char *goal = getGoalPointDataByAreaIdx(w, area, stage);
    short *child = getChildSubPointIdxArrayByAreaIdx(w, area, stage);
    int buf[RO_00181300];
    unsigned int i;
    int r;

    if (goal == 0 || child == 0)
        return -1;
    for (i = 0; i < *(unsigned int *)(goal + 0x14); i++) {
        if (*(int *)(getSubPointDataByAreaIdx(w, child[i], stage) + 0x10) & 2) {
            if (cur != child[i] && (unsigned int)n < 20)
                buf[n++] = child[i];
        }
    }
    if (n > 0) {
        r = iosGetRandom() * n;
        if (r >= n)
            r = n - 1;
        return buf[r];
    }
    return cur;
}

void createUserPathWorkEx(int owner, UserPathWork *work, float arg3, float arg4, int arg2)
{
    work->path[0] = -1;
    work->path[1] = -1;
    work->path[2] = -1;
    work->path[3] = -1;
    work->path[4] = -1;
    work->path[5] = -1;
    work->link[0] = -1;
    work->link[1] = -1;
    work->link[2] = -1;
    work->field3C94 = -1;
    work->field3C7C = 0;
    work->field3C80 = 0;
    work->field3C84 = 0;
    work->field3C78 = 0;
    func_000FC0C0((char *)work);
    work->field3CA0 = 1;
    work->field3CA4 = 0;
    work->field3CA8 = 0;
    work->field3CAC = 0;
    work->field3CB0 = 0;
    createUserPathWork(owner, work, arg3, arg4, arg2);
    createAttackWork(owner);
}

void deleteUserPathWorkEx(char *path)
{
    deleteUserPathWork(path);
}

void setUserPathExMode(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x3C60)) = arg1;
}

void setUserPathGroupID(char *p, int a1, int a2)
{
    *(int *)(p + 0x3C68) = a1;
    *(int *)(p + 0x3C6C) = a2;
}

int getUserPathExMode(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x3C60));
}

int getPathExFinish(PathEx *p, int kind)
{
    switch (kind) {
    case 2:
    case 3:
    case 4:
        return p->f3CA8;
    case 5:
    case 6:
    case 7:
    case 8:
        return p->f3CA4;
    case 9:
        return p->f3CAC;
    }
    return 0;
}

int getPPointPasasgeNum(char *p)
{
    if (*(int *)(p + 0x3C60) != 9) {
        return 0;
    }
    return *(int *)(p + 0x3CB0);
}

void setGPSelectMode(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x3C78)) = arg1;
}

void setForceInitPathEx(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x3C7C)) = arg1;
}

void setGpReferencePathEx(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x3C80)) = arg1;
}

int changedGPIndex(void *a, char *w, void *c)
{
    char *l1 = GetLayoutClass(a);
    char *l2 = GetLayoutClass(c);
    int r = func_000FBDF8(w, l1, *(int *)(w + 0x3C88), *(int *)(w + 0x3C8C), l2);
    return func_000FC4B8(w, l1, l2, *(int *)(w + 0x3C90), r);
}

int changedAPIndex(void *actor, char *work)
{
    return *(int *)(work + 0x3C98) != func_000FBF38(work, GetLayoutClass(actor), *(int *)(work + 0x3C90), *(int *)(work + 0x3C8C));
}

int changedDPGroupID(int a, char *p, int g, int h)
{
    int r = 0;

    if (g == *(int *)(p + 0x3C68)) {
        if (h != *(int *)(p + 0x3C6C)) {
            r = 1;
        }
    } else {
        r = 1;
    }
    return r;
}

void setGpCalcDist(void *arg0, float fparg0)
{
    (*(float *)((char *)(arg0) + 0x3C84)) = fparg0;
}

int getConnectPPointIdx(char *context, int point, int area)
{
    int count = 0;
    char *goal = getGoalPointDataByAreaIdx(context, point, area);
    short *indexAddress = getChildSubPointIdxArrayByAreaIdx(context, point, area);
    if (goal == 0 || indexAddress == 0)
        return 0;
    {
        unsigned int i = 0;
        if (*(unsigned int *)(goal + 0x14) != 0) {
            short *indices = indexAddress;
            do {
                int subPoint = *indices++;
                char *data = getSubPointDataByAreaIdx(context, subPoint, area);
                if (*(int *)(data + 0x10) & 2)
                    ++count;
                ++i;
            } while (i < *(unsigned int *)(goal + 0x14));
        }
    }
    return count;
}

static const int RO_00181390 = 0x7FFFFFFF;

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
    float best = *(const float *)&RO_00181390;
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

static const int RO_00181394 = 0x7FFFFFFF;

static int func_000FBF38(char *w, char *lay, int area, int idx)
{
    GoalPoint *goal = getGoalPointDataByAreaIdx(w, area, idx);
    short *child = getChildSubPointIdxArrayByAreaIdx(w, area, idx);
    float best = *(const float *)&RO_00181394;
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

static int func_000FC070(char *w)
{
    void *sp = getSubPointDataByAreaIdx(w, *(int *)(w + 0x3C9C), *(int *)(w + 0x3C8C));

    if (sp != 0) {
        setAttainmentPos(w, sp);
        setUserPathMode(w, 0);
    }
}

static void func_000FC0C0(char *p)
{
    *(int *)(p + 0x3C98) = -1;
    *(int *)(p + 0x3C9C) = -1;
}

static void func_000FC0D0(char *w, char *layout)
{
    Vec4 pos;
    Vec4 dir;
    float *goal = getGoalPointDataByAreaIdx(w, W(int, 0x3C90), W(int, 0x3C8C));

    if (goal == 0)
        return;
    vecSub(dir, *(float **)(layout + 0x134), goal);
    dir[1] = 0;
    vecNormalize(dir);
    vecScale(pos, dir, W(float, 0x3C84));
    vecAdd(pos, pos, goal);
    pos[3] = 1.0f;
    dir[3] = 1.0f;
    setAttainmentPosAndDir(w, pos, dir);
    setUserPathMode(w, 0);
}

static const int RO_00181398 = 0x7FFFFFFF;

static const int RO_0018139C = 0x7FFFFFFF;

static inline int findNearestSubPoint(char *w, char *lay)
{
    int area = *(int *)(w + 0x3C90);
    int idx = *(int *)(w + 0x3C8C);
    GoalPoint *goal = getGoalPointDataByAreaIdx(w, area, idx);
    short *child = getChildSubPointIdxArrayByAreaIdx(w, area, idx);
    float best = *(const float *)&RO_00181398;
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

static void func_000FC1A0(char *w, char *lay)
{
    SubPoint *sp;

    *(int *)(w + 0x3C98) = findNearestSubPoint(w, lay);
    sp = getSubPointDataByAreaIdx(w, *(int *)(w + 0x3C98), *(int *)(w + 0x3C8C));
    if (sp != 0) {
        setAttainmentPos(w, sp);
        setUserPathMode(w, 0);
        *(int *)(w + 0x3CA0) = 0;
    }
}

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

static void func_000FC310(char *w, char *a, char *b)
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
    root = getRootPointDataByAreaIdx(w, area, sub);
    child = getChildGoalPointIdxArrayByAreaIdx(w, area, sub);
    best = *(const float *)&RO_0018139C;
    if (root == 0 || child == 0) {
        goal = -1;
    } else {
        if (W(int, 0x3C78) == 0)
            pos.q = **(u_long128 **)(a + 0x134);
        else
            pos.q = **(u_long128 **)(b + 0x134);
        for (i = 0; i < root->count; i++) {
            d = vecDist(getGoalPointDataByAreaIdx(w, child[i], sub), pos.f);
            if (d < best) {
                sel = child[i];
                best = d;
            }
        }
        goal = sel;
    }
    if (W(int, 0x3C94) == W(int, 0x3C88) && W(int, 0x3C90) != -1 && W(int, 0x3C90) != goal) {
        if (func_000FC4B8(w, a, b, W(int, 0x3C90), goal) == 0)
            return;
        W(int, 0x3C90) = goal;
        W(int, 0x3C94) = W(int, 0x3C88);
        return;
    }
    W(int, 0x3C90) = goal;
    W(int, 0x3C94) = W(int, 0x3C88);
}

static int func_000FC4B8(char *w, char *lay, char *lay2, int g1, int g2)
{
    float *a = getGoalPointDataByAreaIdx(w, g1, *(int *)(w + 0x3C8C));
    float *b = getGoalPointDataByAreaIdx(w, g2, *(int *)(w + 0x3C8C));
    V4 pos;

    if (a == 0)
        return 1;
    if (*(int *)(w + 0x3C78) == 0)
        pos.q = **(s128 **)(lay + 0x134);
    else
        pos.q = **(s128 **)(lay2 + 0x134);
    if (dist(pos.f, a) - dist(pos.f, b) > RO_00181304)
        return 1;
    return 0;
}
