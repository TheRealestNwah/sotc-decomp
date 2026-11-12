typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } U;

extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern char *GetScriptAnimationClass(int);
extern char *GetDamageClass(int);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void updateScriptDataSystem(int);
extern int GetWaterSurfacePositionY(float *, float *, void *, float, float);
extern void setDischargeParam(int, void *, float, float);
extern int nico_GetCharacterAttackedGPAttr(int, int);
extern void func_000CC4C0(int);
extern void scrRunM(int);

static void func_000CB658(char *o)
{
  U pos;
  U c;
  U a;
  float b;
  int thr;
  char *base;
  int s6;
  int s0;
  int i;
  int n;
  int found;
  int type;
  int entry;
  char *anim;
  char *tbl;
  float (*new_var)[4];
  float ratio;
  float d;
  thr = isysGetThisSubThread();
  base = o + 4;
  for (;;)
  {
    s6 = 0;
    s0 = isysGetThisSubThread();
    SCRExecBossPreProcess(*((int *) o));
    CharaCtrlResetAllScriptCtrlStatus(s0);
    updateScriptDataSystem(s0);
    new_var = &c.f;
    do
    {
      if (s6 == 0)
      {
        s0 = *((int *) (o + 0x5A80));
      }
      else
        if (s6 == 1)
      {
        s0 = *((int *) (o + 0x5A84));
      }
      else
      {
        s0 = *((int *) (o + 0x5A88));
      }
      if ((*((signed char *) (GetScriptAnimationClass(s0) + 0x364))) != 1)
      {
        anim = GetScriptAnimationClass(s0);
        tbl = *((char **) (anim + 0x328));
        n = *((int *) tbl);
        found = 0;
        for (i = 0; i < n; i++)
        {
          entry = *((int *) ((*((char **) (anim + 0x338))) + (i * 8)));
          if (entry != 0)
          {
            type = *((int *) ((*((char **) (tbl + 0x18))) + (i * 12)));
            switch (type)
            {
              case 3:

              case 10:

              case 13:

              case 0x2B:
                pos.q = *(*((s128 **) (GetLayoutClass(entry) + 0x134)));
                found = 1;
                break;

            }

          }
          if (found)
          {
            break;
          }
        }

        a.q = pos.q;
        c.q = pos.q;
        if (GetWaterSurfacePositionY(&b, a.f, gcGlobalVar + 0x230, a.f[1] + 6.0f, a.f[1] - 6.0f))
        {
          c.f[1] = b;
          d = __builtin_fabsf(b - a.f[1]);
          if (6.0f < d)
          {
            ratio = 0.0f;
          }
          else
          {
            ratio = (6.0f - d) / 6.0f;
          }
        }
        else
        {
          ratio = 0.0f;
        }
__asm__ volatile("sqrt.s %0, %0" : "+f"(ratio));
        setDischargeParam(((int *) (base + 0x5AA0))[s6], *new_var, 6.0f, ratio);
      }
      else
      {
        setDischargeParam(((int *) (base + 0x5AA0))[s6], pos.f, 0.0f, 0.0f);
      }
      s6++;
    }
    while (s6 < 3);
    if (GetDamageClass(thr))
    {
      int g = nico_GetCharacterAttackedGPAttr(thr, 0x3F0);
      if (((g == 0x10) || (g == 0x30)) || (g == 0x40))
      {
        func_000CC4C0(thr);
      }
    }
    isysGetThisSubThread();
    SCRExecBossPostProcess(*((int *) o));
    scrRunM(1);
  }

}
