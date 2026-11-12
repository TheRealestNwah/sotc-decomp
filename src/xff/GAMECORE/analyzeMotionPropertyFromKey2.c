typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
    int x18;
    char pad[0x14];
} MotionPredict;

extern int PredictMotionOrientByScriptCtrl(int);
extern void PredictMotionChangeState(MotionPredict *, int, int);
extern void analyzeMotionProperty(int, int, int, int, int, float, float);

#ifdef NONMATCHING /* 1 word: v pinned to $a2 drops the old andi mask, but the beqz tests $a2 where the original tests $v0 (the original copies v0 into a2 before the branch and fills the delay slot from the then-block). */
int analyzeMotionPropertyFromKey2(char *obj, int a1, int a2, int a3, int t0)
{
  int new_var;
  MotionPredict p;
  register int v __asm__("$6");
  v = PredictMotionOrientByScriptCtrl(*((int *) (obj + 8)));

  do
  {
    if (v != 0)
    {
      p.x0 = 0;
      p.x4 = 0;
      p.x14 = 0;
      p.x18 = 0;
      PredictMotionChangeState(&p, *((int *) (obj + 8)), v);
      if (p.x14 != 0)
      {
        new_var = t0;
        analyzeMotionProperty(*((int *) (obj + 8)), p.x14, a2, a3, new_var, *((float *) (obj + 0xB0)), 0.0f);
        return p.x14;
      }
    }
  }
  while (0);
  return 0;
}
#endif
