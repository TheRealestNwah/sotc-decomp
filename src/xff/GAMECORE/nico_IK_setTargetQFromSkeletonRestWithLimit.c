
extern int *DldSysUndefSymbol;
extern void convert_from_quater_to_rotXYZ_direct_motion_ik_base(float *, void *, int);
extern void convert_from_rotXYZ_to_quater_direct_motion_ik_base(void *, float *, int);
typedef struct 
{
  float pad0;
  float min;
  float max;
  char pad[0x1C];
} Limit;
inline static char *dldResolve(unsigned int *h)
{
  unsigned int v = *h;
  int off = v & 0x3FFFF;
  int *t = (off != 0) ? (*((int **) (((char *) h) - off))) : (0);
  return ((t != 0) && (t != DldSysUndefSymbol)) ? (((char *) t[4]) + (((v >> 18) & 0xFFF) * ((int *) t[2])[3])) : (0);
}

void func_0003BEB8(void *out, char *ik, void *q);
typedef int s128 __attribute__((mode(TI)));
typedef union 
{
  s128 q;
  float f[4];
} Vec4;
typedef struct 
{
  char pad[0x20];
  Vec4 q;
  char pad30[8];
  int parent;
  int pad3C;
} Node;
typedef struct 
{
  int obj;
  Vec4 *q;
  int pad8;
  int padC;
  struct 
  {
    int pad[2];
    Node *nodes;
  } *sk;
  int idx;
  unsigned int *h;
} IkTarget;
extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
inline static void quatMul(void *d, void *a, void *b)
{
__asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

extern float r;
inline static float dot4(void *a, void *b)
{

    register float r __asm__("$f0");
__asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni %0, vf15\n"
                         : "=r"(r) : "r"(a), "r"(b));
  return r;
}

inline static void negate4(void *v)
{
  float m = -1.0f;
__asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(m) : "memory");
}

inline static void lerp4(void *out, void *a, void *b, float t)
{
  register void *o __asm__("$6") = out;
__asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(o), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

inline static void normalize4(void *v)
{
__asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

inline static void getGlobalRest(Vec4 *out, IkTarget *ik, int obj, int idx)
{
  if (ik->sk->nodes[idx].parent == (-1))
  {
    char *lay = GetLayoutClass(obj);
    quatMul(out, *((void **) (lay + 0x13C)), &ik->sk->nodes[ik->idx].q);
  }
  else
  {
    out->q = ik->sk->nodes[idx].q.q;
  }
}

#ifdef NONMATCHING /* 4 diffs: addu operand order for the cur/src pointers and v0/v1 for the lq temp; permuter stuck at 30 */
void nico_IK_setTargetQFromSkeletonRestWithLimit(IkTarget *ik, void *base, int open, float rate)
{
  Vec4 q;
  Vec4 lim;
  Vec4 tgt;
  union 
  {
    float f;
    int i;
  } d;
  IkTarget **new_var;
  float t;
  Vec4 *cur;
  Vec4 *src;
  char *cc = GetCharacterClass(ik->obj);
  int idx = ik->idx;
  float *w = ((float *) (*((char **) (cc + 0x320)))) + idx;
  new_var = &ik;
  if (open)
  {
    getGlobalRest(&q, ik, (*new_var)->obj, idx);
    func_0003BEB8(&lim, dldResolve(ik->h), base);
    quatMul((*((Vec4 **) (cc + 0x328))) + idx, &q, &lim);
    *w += rate * 0.5f;
    *w = ((*w) <= 1.0f) ? (*w) : (1.0f);
  }
  else
  {
    *w -= rate * 0.5f;
    *w = ((*w) >= 0.0f) ? (*w) : (0.0f);
  }
  cur = &ik->q[ik->idx];
  src = (*((Vec4 **) (cc + 0x328))) + idx;
  t = *w;
  tgt.q = cur->q;
  d.f = dot4(src, &tgt);
  if (d.i < 0)
  {
    negate4(&tgt);
  }
  lerp4(cur, src, &tgt, t);
  normalize4(&ik->q[ik->idx]);
  ((float *) (*((char **) (cc + 0x324))))[idx] = 2.0f;
}
#endif
