typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x380];
    int f380;
    char pad1[0x3BC - 0x384];
    int searchPointMax;
    char pad2[0x3E0 - 0x3C0];
    u_long128 attainVec;
    float attain0;
    float attain1;
    float attain2;
    float attain3;
    char pad3[0x408 - 0x400];
    int f408;
} Way;

typedef struct {
    float f0;
    float f4;
    float f8;
    float fC;
    float f10;
} TimeFloatInter;

typedef struct {
    char pad0[0x50];
    u_long128 dir;
} GazeIK;

typedef struct {
    char pad0[0x110C];
    GazeIK *gazeIK;
} GazeOwner;

typedef struct {
    char pad0[0x6C];
    float f6C;
    float f70;
} WormCtrl;

typedef struct {
    u_long128 a;
    u_long128 b;
    int count;
} PositionFilter;

void setSearchPointMax(Way *way, int max)
{
    if (max <= 0) {
        way->searchPointMax = 0x380;
    } else {
        way->searchPointMax = max;
    }
}

int getWayFinish(Way *way)
{
    int finished = 0;
    if (way->f408 != 0) {
        finished = way->f380 == 0;
    }
    return finished;
}

void setAttainRangeData(Way *way, u_long128 *vec, float a, float b, float c, float d)
{
    way->attainVec = *vec;
    way->attain0 = a;
    way->attain1 = b;
    way->attain2 = c;
    way->attain3 = d;
}

void Init_TimeFloatInter(TimeFloatInter *t, float a, float b, float c, float d)
{
    t->f0 = c;
    t->f4 = b;
    t->f8 = a;
    t->fC = b;
    t->f10 = d;
}

void setGazeDirGazeIKWork(GazeOwner *owner, u_long128 *dir)
{
    if (owner->gazeIK != 0) {
        owner->gazeIK->dir = *dir;
    }
}

void setRotParamWormCtrlWork(WormCtrl *w, float a, float deg)
{
    w->f6C = a;
    w->f70 = deg * 0.0174532925f;
}

void GAMEUTIL_reset_position_filter(PositionFilter *f, u_long128 *pos)
{
    f->a = *pos;
    f->b = *pos;
    f->count = 1;
}

