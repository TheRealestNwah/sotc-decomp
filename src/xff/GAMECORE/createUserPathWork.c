typedef struct {
    char pad0[0x98];
    char link0[0xC];
    int xA4;
    char padA8[0x414 - 0xA8];
    int x414;
    char pad418[0x434 - 0x418];
    int x434;
    char pad438[0x2038 - 0x438];
    int x2038;
    char pad203C[0x3C44 - 0x203C];
    int x3C44;
    int x3C48;
    int *x3C4C;
    int x3C50;
} UserPathWork;

typedef struct {
    char pad0[0x2EC];
    int x2EC[4];
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;
extern float ZeroVector[];

static const union {
    int i;
    float f;
} RO_001812D0 = { 0x7FFFFFFF };
static const union {
    int i;
    float f;
} RO_001812D4 = { 0xFFFFFFFF };

extern void InitTwoWayLink(void *, void *);
extern void resetUserPathWork(int, UserPathWork *);
extern void setPassageRangeData(UserPathWork *, float, float);
extern void setAttainRangeData(UserPathWork *, float *, float, float, float, float);
extern void setRouteMinAngle(UserPathWork *, float);
extern void setSearchRouteMaxAngle(UserPathWork *, float);
extern void setReductionCosUserPathWork(UserPathWork *, float);
extern void setSelfColAndNearMinDist(UserPathWork *, int, float);
extern void setSearchRadius(UserPathWork *, float);
extern void setSearchPointMax(UserPathWork *, int);
extern void setStabilizeYPathWork(UserPathWork *, int);
extern void setRayByRealColPathWork(UserPathWork *, int);
extern void setPassageWideRayPathWork(UserPathWork *, int);
extern void setAngleStabilizeYPathWork(UserPathWork *, int);
extern void setExecRayChkPathWork(UserPathWork *, int);
extern void setPathRayWideParam(UserPathWork *, int, float);
extern void setForceRouteAttrPathWork(UserPathWork *, int);
extern void setRouteColCheckPathWork(UserPathWork *, int);
extern void setRouteLockPathWork(UserPathWork *, int);
extern void setPlayerWayColCheckPathWork(UserPathWork *, int);
extern void setFollowModePathWork(UserPathWork *, int);
extern void setRealColJudgeFunc(UserPathWork *, void *);

static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

void createUserPathWork(int owner, UserPathWork *work, int idx, float x, float z)
{
    float r;

    work->x3C4C = &gcGlobalVar.x2EC[work->x3C50 = idx];
    work->x434 = 0;
    work->x2038 = 0;
    work->x3C44 = 0;
    work->x3C48 = 0;
    work->x414 = 0;
    InitTwoWayLink(work->link0, &work->xA4);
    work->xA4 = 0;
    resetUserPathWork(owner, work);
    setPassageRangeData(work, x, z);
    setAttainRangeData(work, ZeroVector, 0.0f, 0.0f, 0.0f, 0.0f);
    setRouteMinAngle(work, 0.0f);
    setSearchRouteMaxAngle(work, 3.14159251f);
    setReductionCosUserPathWork(work, 3.14159251f);
    r = RO_001812D0.f;
    do {
        setSelfColAndNearMinDist(work, 0, r);
        setSearchRadius(work, sqrtF(r));
        setSearchPointMax(work, 0x380);
    } while (0);
    setStabilizeYPathWork(work, 0);
    setRayByRealColPathWork(work, 0);
    setPassageWideRayPathWork(work, 0);
    setAngleStabilizeYPathWork(work, 0);
    setExecRayChkPathWork(work, 1);
    setPathRayWideParam(work, 0, RO_001812D4.f);
    setForceRouteAttrPathWork(work, 0);
    setRouteColCheckPathWork(work, 1);
    setRouteLockPathWork(work, 0);
    setPlayerWayColCheckPathWork(work, 0);
    setFollowModePathWork(work, 0);
    setRealColJudgeFunc(work, 0);
}
