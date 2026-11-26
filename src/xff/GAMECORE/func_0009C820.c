/* Parked: 19 diffs, same size. Remaining: case 2 register assignment
   (YUnitVector/t2/b2/inv in s1/s0/s2 vs the Original's s0/s2/s1). The
   0x1F0 offset through new_var2 (from the permuter) fixes the copy's load base. */
#ifdef NONMATCHING

typedef int s128 __attribute__((mode(TI)));
typedef union 
{
  s128 q;
  float f[4];
} Vec4;
extern Vec4 ZeroVector;
extern char YUnitVector[];
extern char ZUnitVector[];
extern void *isysGetThisSubThread(void);
extern void *GetCharacterClass(void *);
extern void *GetLayoutClass(void *);
extern float AI_GetTimeOfCurrMotion(void *, float);
extern void GetDifferencialQuaternionWithNoRegularize(void *, void *, void *, void *);
extern float iosGetRandom(void);
extern float iosGetSinf(float);
extern float iosGetCosf(float);
extern void SCRSetCharaMotionPlaySpeedRatioDirect(void *, float);
extern void SetCharacterObjCollisionProcFlag(void *, int);
extern void func_0009C638(char *, void *, float);

inline static void randomTarget(char *o, Vec4 *t, char *base, char *layout, Vec4 *inv0)
{

    register Vec4 *inv asm("$2");
  float r;
  float a;
  r = iosGetRandom() * (*((float **) (o + 0x20)))[1];
  a = iosGetRandom() * 3.1415926f;
  a = a + a;
  t->f[0] = r * iosGetSinf(a);
  t->f[1] = r * iosGetCosf(a);
  t->f[2] = (*((float **) (o + 0x20)))[2];
  if ((*((float *) (base + 0x40))) < t->f[2])
    t->f[2] = *((float *) (base + 0x40));
  t->f[3] = 1.0f;
  inv = inv0;
__asm__ __volatile__("lqc2 vf8, 0x0(%0)
vaddw.xyz vf12, vf0, vf0w
lqc2 vf11, 0x0(%1)
vmr32.w vf14, vf0
vmr32.w vf15, vf0
vmr32.w vf16, vf0
vopmula.xyz ACC, vf11, vf12
vmadd.xyz vf11, vf0, vf0
vmadd.xyz vf10, vf11, vf12
vmul.xyz vf13, vf11, vf10
vopmula.xyz ACC, vf11, vf10
vmaddw.xyz vf15, vf10, vf11w
vmsubw.xyz vf16, vf10, vf11w
vopmula.xyz ACC, vf13, vf12
vmadd.xyz vf17, vf13, vf12
vopmula.xyz ACC, vf15, vf12
vmadd.xyz vf15, vf0, vf0
vsub.xyz vf14, vf12, vf17
vmove.yz vf17, vf14
vmove.y vf14, vf16
vmove.y vf16, vf15
vmove.y vf15, vf17
vmove.z vf14, vf15
vmove.z vf15, vf16
vmove.z vf16, vf17
vmulax.xyzw ACC, vf14, vf8x
vmadday.xyzw ACC, vf15, vf8y
vmaddaz.xyzw ACC, vf16, vf8z
vmaddw.xyzw vf10, vf0, vf8w
sqc2 vf10, 0x0(%0)" : : "r"(t), "r"(inv) : "memory");
__asm__ __volatile__("lqc2 vf5, 0x0(%0)
lqc2 vf6, 0x0(%1)
vadd.xyz vf5, vf5, vf6
sqc2 vf5, 0x0(%1)" : : "r"(*(Vec4 **)(layout + 0x134)), "r"(t) : "memory");
}

inline static void conj(Vec4 *out, Vec4 *q)
{
__asm__ __volatile__("lqc2 vf11, 0x0(%1)
vsubw.x vf5, vf0, vf0w
vmulx.xyz vf11, vf11, vf5x
sqc2 vf11, 0x0(%0)" : : "r"(out), "r"(q) : "memory");
}

void func_0009C820(char *o)
{
  unsigned long new_var2;
  Vec4 q;
  char *new_var;
  Vec4 inv;
  void *th;
  th = isysGetThisSubThread();
  if ((*((int *) (o + 0x198))) == (*((int *) (o + 0x19C))))
  {
    return;
  }
  *((int *) (o + 0x1BC)) = 0;
  *((int *) (o + 0x234)) = 0;
  switch (*((int *) (o + 0x19C)))
  {
    case 0:
      *((float *) (o + 0x1B8)) = 3.0f;
      *((s128 *) (o + 0x220)) = ZeroVector.q;
      break;

    case 1:
    {
      char *b1 = o + 0xA0;
      Vec4 *t1;
      char *l1;
      Vec4 *i1;
      *((float *) (o + 0x1B8)) = AI_GetTimeOfCurrMotion(GetCharacterClass(th), 1.0f) * 0.9f;
      *((s128 *) (o + 0x220)) = ZeroVector.q;
      *((s128 *) (o + 0x200)) = *((s128 *) (o + 0x1F0));
      t1 = (Vec4 *) (o + 0x1F0);
      l1 = GetLayoutClass(isysGetThisSubThread());
      GetDifferencialQuaternionWithNoRegularize(&q, ZUnitVector, o + 0xC0, YUnitVector);
      i1 = &inv;
      conj(i1, &q);
      randomTarget(o, t1, b1, l1, i1);
      *((int *) (o + 0x1D0)) = 0;
      break;
    }

    case 2:
    {
      Vec4 *t2;
      char *b2;
      char *l2;
      Vec4 *i2;
      *((int *) (o + 0x494)) = 1;
      new_var2 = 0x1F0;
      *((float *) (o + 0x1B8)) = 1.0f;
      new_var = o + new_var2;
      func_0009C638(o, YUnitVector, 1.0f);
      *((s128 *) (o + 0x200)) = *((s128 *) (o + 0x1F0));
      t2 = (Vec4 *) new_var;
      b2 = o + 0xA0;
      new_var = o;
      l2 = GetLayoutClass(isysGetThisSubThread());
      GetDifferencialQuaternionWithNoRegularize(&q, ZUnitVector, new_var + 0xC0, YUnitVector);
      i2 = &inv;
      conj(i2, &q);
      randomTarget(o, t2, b2, l2, i2);
      *((int *) (o + 0x1D0)) = 0;
      break;
    }

    case 3:
      *((float *) (o + 0x1B8)) = 5.0f;
      break;

    case 4:
      *((float *) (o + 0x1B8)) = 1.0f;
      func_0009C638(o, o + 0x240, 1.0f);
      break;

    case 5:
      SCRSetCharaMotionPlaySpeedRatioDirect(th, 1.0f);
      SetCharacterObjCollisionProcFlag(th, 1);
      break;

    case 6:
      SetCharacterObjCollisionProcFlag(th, 0);
      break;

  }

}
#endif
