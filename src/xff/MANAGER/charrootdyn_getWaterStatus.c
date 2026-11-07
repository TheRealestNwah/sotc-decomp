
typedef int s128 __attribute__((mode(TI)));
typedef union 
{
  s128 q;
  float f[4];
} Vec4;
typedef struct 
{
  Vec4 geometry[4];
  Vec4 position;
} CollisionPoint;
typedef struct 
{
  int f0;
  int id;
} FinderEntry;
extern int CheckUnderVariableXZSurface(CollisionPoint *, float *, float *, void *);
extern FinderEntry *ClipCollisionFinderCallBack(char *, float *, Vec4 *, int *, int (*)(FinderEntry *, void *), void *);
extern int charrootdyn_slideExceptionJudgeCB(FinderEntry *, void *);
char charrootdyn_getWaterStatus(char *chr, Vec4 *out, void *unused, int *finder, Vec4 *point, float height)
{
  Vec4 adjusted;
  CollisionPoint water;
  CollisionPoint obstacle;
  Vec4 finish;
  CollisionPoint obstacle2;
  Vec4 finish2;
  int *finder1 = (int *) (chr + 0xE20);
  int ok;
  float below;
  adjusted.q = point->q;
  adjusted.f[1] += height;
  if (CheckUnderVariableXZSurface(&water, point->f, adjusted.f, ((*((short *) (chr + 0x370))) * 4) + (*((int *) (chr + 0xE38)))))
  {
    finish.q = point->q;
    finish.f[1] += height;
    if (ClipCollisionFinderCallBack((char *) (&obstacle), point->f, &finish, finder1, charrootdyn_slideExceptionJudgeCB, 0) && (obstacle.position.f[1] > water.position.f[1]))
    {
      ok = 0;
    }
    else
    {
      ok = 1;
      out->q = water.position.q;
    }
  }
  else
  {
    ok = 0;
  }
  if (ok)
  {
    finish2.q = out->q;
    finish2.f[1] += height + height;
    if (ClipCollisionFinderCallBack((char *) (&obstacle2), out->f, &finish2, finder, charrootdyn_slideExceptionJudgeCB, 0))
    {
      {
        float oy = obstacle2.position.f[1];
        below = out->f[1] - oy;
      }
    }
    else
    {
      below = (-height) * 2.0f;
    }
    *((float *) (chr + 0x10C4)) = below;
    __asm__ volatile("" ::: "memory");
    *((char *) (chr + 0x362)) = 1;
    *((float *) (chr + 0x10C8)) = out->f[1];
    *((float *) (chr + 0x10CC)) = out->f[1] - (point->f[1] + height);
  }
  return *((char *) (chr + 0x362));
}
