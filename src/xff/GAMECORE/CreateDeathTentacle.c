
typedef int s128 __attribute__((mode(TI)));
typedef struct 
{
  int a;
  int b;
} Pair;
typedef struct 
{
  s128 pos;
  int target;
  int kind;
  int pad18;
  int pad1C;
  int dmg;
  void *work;
  char pad28[8];
  s128 interest;
  int cnt;
  int buf;
  int pad48;
  Pair pr;
  int pad54;
  int pad58;
  char pad5C[4];
} Tentacle;
extern int D_0017A9B0;
extern char rootPtn[];
extern void func_0004B090(void);
extern void D_0004B0B0(void);
extern int effectGetDamageWork(void **);
extern void *createScriptObj(void *, int, void *, int, int, int, int, int);
extern void *iosMallocAlign(void *, int, int);
extern char *GetLayoutClass(int);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*)(void), void *);
extern void setScriptObjArgument(void *, void *);
extern void GAMEUTIL_set_auto_get_flag_boss_interest_position(int);
extern void GAMEUTIL_set_custom_boss_interest_position(s128 *);
inline static void calcPair(Pair *p, int t, int lim, int step)
{
  int n = 1;
  while (t > lim)
  {
    t -= step;
    n++;
  }

  p->b = n;
  p->a = 0;
}

void CreateDeathTentacle(int target)
{
  Pair pr;
  void *dw;
  int dmg;
  int t;
  int n;
  int new_var;
  void **obj;
  Tentacle *w;
  int new_var2;
  dw = 0;
  calcPair(&pr, 0xCA, 0x3C, 0x3A);
  new_var2 = 0x65;
  dmg = effectGetDamageWork(&dw);
  obj = createScriptObj(func_0004B090, 0, rootPtn, 0x2000, 0x26A, 8, target, 0);
  if (obj == 0)
  {
    D_0017A9B0 = 1;
    return;
  }
  D_0017A9B0 = 0;
  w = iosMallocAlign(*obj, 0x60, 0x10);
  w->buf = (int) iosMallocAlign(*obj, 0x194, 0x10);
  w->pad48 = 0;
  w->cnt = 10;
  w->kind = new_var2;
  w->dmg = dmg;
  w->target = target;
  w->pad18 = 0;
  w->pad1C = 0;
  w->pr = pr;
  w->work = dw;
  w->pad54 = 0;
  w->pad58 = 0;
  w->interest = (w->pos = *(*((s128 **) (GetLayoutClass(target) + (new_var = 0x134)))));
  SetScriptObjDeleteCallBackFunc(obj, D_0004B0B0, w);
  setScriptObjArgument(obj, w);
  GAMEUTIL_set_auto_get_flag_boss_interest_position(0);
  GAMEUTIL_set_custom_boss_interest_position(&w->interest);
}
