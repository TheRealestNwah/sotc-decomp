typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
typedef struct { int f0, id; } FinderEntry;
extern int CheckUnderVariableXZSurface(CollisionPoint *, float *, float *, void *);
extern FinderEntry *ClipCollisionFinderCallBack(char *, float *, Vec4 *, int *,
    int (*)(FinderEntry *, void *), void *);
extern int charrootdyn_slideExceptionJudgeCB(FinderEntry *, void *);

int charrootdyn_checkUnderWater(Vec4 *out, Vec4 *point, void *surface, int *finder, float height)
{
    Vec4 adjusted;
    CollisionPoint water;
    CollisionPoint obstacle;
    Vec4 finish;
    adjusted.q = point->q;
    adjusted.f[1] += height;
    if (CheckUnderVariableXZSurface(&water, point->f, adjusted.f, surface)) {
        finish.q = point->q;
        finish.f[1] += height;
        if (ClipCollisionFinderCallBack((char *)&obstacle, point->f, &finish, finder,
                charrootdyn_slideExceptionJudgeCB, 0) && obstacle.position.f[1] > water.position.f[1])
            return 0;
        out->q = water.position.q;
        return 1;
    }
    return 0;
}
