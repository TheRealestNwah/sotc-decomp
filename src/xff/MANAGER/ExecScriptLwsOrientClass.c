
extern int **GetAnimationClass(void);
extern char *GetCharacterClass(int);
extern int ReparentChildObjects;
extern void func_0007FD80(int, float, float, void *);
extern void ExecAnimeTableInfo(char *, int, float);
extern void ExecChildGroupManagerObj(int, void *);
int ExecScriptLwsOrientClass(int obj, void *a1, float *pos, float f1, float f2)
{
  int result = 0;
  float r;
  float lim;
  char *chr;
  char *c1;
  char *q;
  int i;
  if (GetAnimationClass()[9] != 0)
  {
    return 0;
  }
  if ((*((signed char *) (GetCharacterClass(obj) + 0x2B4))) != 0)
  {
    return 0;
  }
  if (f1 != 0.0f)
  {
    func_0007FD80(obj, f1, f2, a1);
  }
  c1 = GetCharacterClass(obj);
  lim = *((float *) ((*((char **) (c1 + 0x1140))) + 0x3C));
  if (0.0f <= lim)
  {
    float d;
    float lim2 = lim * lim;
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyzw vf7, vf5, vf6\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vaddy.x vf7, vf7, vf7y\n"
                             "vaddz.x vf7, vf7, vf7z\n"
                             "qmfc2.ni $2, vf7\n"
                             "mtc1 $2, %0\n"
                             : "=f"(d) : "r"(pos), "r"(*(float **)(c1 + 0x134)) : "$2", "memory");
    if (d < lim2)
    {
      chr = GetCharacterClass(obj);
      q = chr + 0x1C0;
      ExecAnimeTableInfo(chr + 0x1F0, obj, (*((float *) (q + 8))) * (*((float *) (q + 0x2C))));
      for (i = 0; i < (*((int *) (chr + 0x3FC))); i++)
      {
        char *e = (*((char **) (chr + 0x30C))) + (i << 7);
        char *q2;
        if ((*((int *) (e + 0x44))) >= 0)
        {
          q2 = e + 4;
          ExecAnimeTableInfo(e + 0x34, obj, (*((float *) (q2 + 8))) * (*((float *) (q2 + 0x2C))));
        }
      }

    }
  }
  ExecChildGroupManagerObj(obj, &ReparentChildObjects);
  return 1;
}
