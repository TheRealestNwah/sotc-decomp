
typedef struct 
{
  void *a;
  void *b;
  int a_kept;
  int b_kept;
  char pad10[0x4];
  unsigned char a_own;
  unsigned char b_own;
  char pad16[0x2];
  void *c;
} HarpoonLws;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void isysRequestDeleteObj(void *);
extern void func_00076698(char *);
extern void SCRSetupArrow1ByPlayer2(void *, int, float *, float *);
extern int SkelFocusDef_PLAYER_HAND_A_L;
extern int ScriptAnimationObjDef_BOW_END;
extern void *_SCRSetupLWSWithTargetNodeParent(int, void *, int);
extern void _SCRStartLWS(void *, int, int, void *);
inline static void vecSubNormalize(float *out, float *a, float *b)
{
__asm__ __volatile__(".set noreorder
"
        "lqc2 vf5, 0x0(%1)
"
        "lqc2 vf6, 0x0(%2)
"
        "vsub.xyzw vf7, vf5, vf6
"
        "sqc2 vf7, 0x0(%0)
"
        "lqc2 vf5, 0x0(%0)
"
        "vmul.xyz vf7, vf5, vf5
"
        "vmulax.w ACC, vf0, vf7x
"
        "vmadday.w ACC, vf0, vf7y
"
        "vmaddz.w vf7, vf0, vf7z
"
        "vrsqrt Q, vf0w, vf7w
"
        "vwaitq
"
        "vmulq.xyz vf5, vf5, Q
"
        "sqc2 vf5, 0x0(%0)
"
        ".set reorder
"
        : "+r"(out) : "r"(a), "r"(b) : "memory");
}

static void T_00079800(void *obj)
{
  char *w = GetSCRCharaAIWorkPtr(obj);
  HarpoonLws *h;
  float v[4];
  float *pos;
  void *new_var;
  float *tgt = (float *) (w + 0x4A0);
  { register float *p __asm__("$3") = (float *) (w + 0x30); /* pinned to the original's $v1 */
    __asm__("" : "+r"(p));
    vecSubNormalize(v, p, tgt); }
  h = (HarpoonLws *) (w + 0x60);
  pos = h->b;
  if (pos != 0)
  {
    if (h->b_own == 0)
    {
      if (h->b_kept == 0)
      {
        isysRequestDeleteObj(h->b);
      }
    }
    else
    {
      isysRequestDeleteObj(h->b);
    }
    h->b = 0;
    h->b_kept = 1;
    h->b_own = 0;
  }
  new_var = h->a;
  if (h->a != 0)
  {
    if (h->a_own == 0)
    {
      if (h->a_kept == 0)
      {
        isysRequestDeleteObj(h->a);
      }
    }
    else
    {
      isysRequestDeleteObj(new_var);
    }
    h->a = 0;
    h->a_kept = 1;
    h->a_own = 0;
  }
  *(void **)(w + 0x64) = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_BOW_END, obj, SkelFocusDef_PLAYER_HAND_A_L);
  _SCRStartLWS(*(void **)(w + 0x64), -1, 4, w + 0x6C);
  w[0x75] = 1;
  func_00076698(w);
  SCRSetupArrow1ByPlayer2(obj, *((int *) (w + 0x70)), v, tgt);
}
