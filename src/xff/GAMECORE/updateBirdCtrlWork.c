/* Parked: 517 differing words, 831 of 844 words. Bird path following:
 * orientation from Euler angles, passage targets, line-distance steering
 * toward the next passage point with func_001010F8, the FlapWing script and
 * layout attainment. Branch layout follows the Original's: the x40 test,
 * both func_001038C8 tests and the x44 == 0.0f test are written with the
 * fall-through case first, and the two FlapWing calls share one block
 * (goto flap). The p->x1A0 zero goes through a float local, so it stays in
 * f0 for the following x74 compare. Remaining: the Original keeps four
 * separate func_001010F8 calls, each ending in a jump that reloads
 * ctrl->x64. gcc here cross-jumps them into one call (13 missing words).
 * There are also register differences (p in s5 in the Original). */
#ifdef NONMATCHING

typedef int s128 __attribute__((mode(TI)));
typedef union 
{
  struct 
  {
    float x;
    float y;
    float z;
    float w;
  } v;
  float f[4];
  s128 q;
} Vec;
typedef struct 
{
  char pad0[0x510];
  int x510;
  char pad514[0x750 - 0x514];
  int x750;
} Chr;
typedef struct 
{
  char pad0[0x134];
  Vec *pos;
  char pad138[4];
  Vec *quat;
} Obj;
typedef struct 
{
  int x0;
  int x4;
} Pass;
typedef struct 
{
  char pad0[4];
  int x4;
  int x8;
  s128 *target;
  int x10;
  Chr *chr;
  Obj *obj;
  Pass *x1C;
  float inv[4][4] __attribute__((aligned(16)));
  float mat[4][4] __attribute__((aligned(16)));
  char padA0[0xC0 - 0xA0];
  float xC0;
  char padC4[4];
  int xC8;
  void *owner;
  Vec xD0;
  Vec xE0;
  Vec xF0;
  Vec x100;
  Vec x110;
  Vec x120;
  Vec x130;
  char pad140[8];
  float x148;
  float x14C;
  float x150;
  float x154;
  float x158;
  float x15C;
  float x160;
  char pad164[0xC];
  Vec x170;
  float x180;
  float x184;
  char pad188[0x1A0 - 0x188];
  float x1A0;
  char pad1A4[0xC];
} Tmp;
typedef struct 
{
  char pad0[4];
  int x4;
  char pad8[8];
  s128 x10;
  int x20;
  char pad24[0x3C - 0x24];
  int x3C;
  int x40;
  float x44;
  char pad48[8];
  Vec x50;
  int x60;
  int x64;
  char pad68[0x74 - 0x68];
  float x74;
  char pad78[4];
  float x7C;
  float x80;
  float x84;
  float x88;
  float x8C;
  char pad90[0xA8 - 0x90];
  float xA8;
  char padAC[8];
  float xB4;
  float xB8;
  char padBC[0xD0 - 0xBC];
  int xD0;
  char padD4[0x1A8 - 0xD4];
  int x1A8;
  int x1AC;
  char pad1B0[0x200 - 0x1B0];
  int x200;
  char pad204[0x224 - 0x204];
  float x224;
  float x228;
  float x22C;
  float x230;
  char pad234[0xC];
  Vec x240;
} Ctrl;
typedef struct 
{
  char pad0[0x30];
  Vec x30;
  char pad40[0xA8 - 0x40];
  int xA8;
  char padAC[4];
  Vec xB0;
  char padC0[0xE0 - 0xC0];
  int xE0;
  char padE4[0x3CC - 0xE4];
  float x3CC;
} Lay;
typedef struct 
{
  int pad;
  int x4;
} ScriptDef;
typedef struct 
{
  char pad0[0x190];
  float x190;
  char pad194[0x238 - 0x194];
  char x238[1];
} GcGlobal;
extern s128 fltMaxVector;
extern Vec YUnitVector;
extern Vec ZUnitVector;
extern GcGlobal gcGlobalVar;
extern float RO_00181440;
extern ScriptDef *ScriptCtrlDef_SCRFlapWing;
extern int MotRootDyn_NOROOTDYNAMICS_POS_FREE;
extern void _initBaseMoveTmpWork(void *, Tmp *, Ctrl *, Lay *);
extern float getRatioFromInterp(float, float);
extern float getValueInterp(float, float, float, float);
extern void GetQuaternionByEulerYXZ(void *, float, float, float);
extern void GetEulerYXZFromQuaternion(void *, void *);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void getTurnAndPitchFromDir(void *, float *, float *);
extern void getTurnAndPitchFromQuaternion(void *, float *, float *);
extern float iosGetSinf(float);
extern int ClipCollisionDirect(void *, void *, void *, void *);
extern int func_001038C8(Tmp *);
extern void func_000FFB80(Tmp *);
extern void _initMovePathWork(Tmp *, void *, float);
extern int _compPassagePos(Tmp *);
extern void func_00103830(Ctrl *);
extern int func_000FFE48(Vec *, Tmp *);
extern float CalcDistancePointAndLine(void *, void *, void *);
extern void CalcFootVec(void *, void *, void *, void *);
extern void func_001010F8(void *, void *, int, int, int, Tmp *);
extern void setLockPassageWork(Lay *, int);
extern int chkAttainExecLayout(Lay *, Vec *, Obj *, Chr *);
extern void func_001038E8(Ctrl *);
extern void forceSetWayFinish(Lay *);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void func_00101B58(Tmp *, int);
extern void func_00103030(Tmp *, int);
inline static void quatMul3(void *out, void *a, void *b)
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
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

inline static void quatDir(void *out, void *q)
{
__asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

inline static float vdist(void *a, void *b)
{
  float r;
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
  return r;
}

inline static float vlen(void *v)
{
  float r;
__asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
  return r;
}

inline static void normalize3(void *v)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
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

inline static void quatToMatrix(float *out, float *quat)
{
__asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(out), "r"(quat));
}

inline static void unitRow(float *out)
{
__asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(out));
}

inline static void matInverse(float *dst, float *src)
{
__asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

inline static void scale3(void *d, void *a, float s)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

inline static void vadd(void *d, void *a, void *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

inline static void vadd3(void *d, void *a, void *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

inline static void vsub(void *d, void *a, void *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

inline static float dot3(void *a, void *b)
{
  float r;
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
  return r;
}

inline static void matVec(void *d, void *m, void *v)
{
__asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

inline static float dot4(Vec *a, Vec *b)
{
  float r;
__asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni $2, vf15\n" "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
  return r;
}

inline static void negate4(Vec *v)
{
  float m = -1.0f;
__asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(m) : "memory");
}

inline static void lerp4(Vec *out, Vec *a, Vec *b, float t)
{
__asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

inline static void blend4(Vec *out, Vec *b, Vec *a, float t)
{
  union 
  {
    float f;
    int i;
  } dsign;
  dsign.f = dot4(a, b);
  if (dsign.i < 0)
    negate4(b);
  lerp4(out, a, b, t);
  normalize4(out);
}

extern float *m;
int updateBirdCtrlWork(void *th, Ctrl *ctrl, Lay *lay)
{
  float z;
  Tmp w;
  Tmp *p = &w;
  Vec a;
  Vec b;
  Vec c;
  Vec d;
  Vec e;
  Vec f;
  Vec g;
  struct 
  {
    char pad[0x44];
    float y;
    char pad48[8];
  } hit;
  float turn;
  float pitch;
  _initBaseMoveTmpWork(th, p, ctrl, lay);
  p->x150 = getRatioFromInterp(ctrl->xA8, gcGlobalVar.x190);
  GetQuaternionByEulerYXZ(&a, 0.0f, 0.0f, ctrl->x230);
  p->owner = ctrl;
  quatMul3(&p->xD0, p->obj->quat, &a);
  quatDir(&b, &p->xD0);
  if (__builtin_fabsf(dot3(&b, &YUnitVector)) > 0.97999996f)
  {
    GetEulerYXZFromQuaternion(&c, &p->xD0);
    c.f[2] = getValueInterp(c.f[2], 0.0f, ctrl->xA8, gcGlobalVar.x190);
    GetQuaternionByEulerYXZ(&p->xD0, c.f[0], c.f[1], c.f[2]);
  }
  else
  {
    float t = getRatioFromInterp(ctrl->xA8, gcGlobalVar.x190);
    GetQuaternionByAxisDirZY(&d, &b, &YUnitVector);
    e.q = p->xD0.q;
    blend4(&p->xD0, &e, &d, t);
  }
  normalize4(&p->xD0);
  {

        register float *m __asm__("$2") = p->mat[0];
    quatToMatrix(m, (float *) (&p->xD0));
    m += 12;
    unitRow(m);
  }
  matInverse(p->inv[0], p->mat[0]);
  matVec(&p->x170, p->mat, &ZUnitVector);
  getTurnAndPitchFromDir(&p->x170, &p->x180, &p->x184);
  if (!func_001038C8(p))
  {
    p->x158 = (ctrl->x224 * ctrl->x224) * ctrl->x88;
  }
  else
  {
    p->x158 = (ctrl->x224 * ctrl->x224) * ctrl->xB8;
  }
  ctrl->x228 = ctrl->x22C;
  ctrl->x22C = -p->x158;
  getTurnAndPitchFromQuaternion(&ctrl->x240, &p->x148, &p->x14C);
  quatDir(&e, &p->xD0);
  getTurnAndPitchFromDir(&e, &turn, &pitch);
  if (!func_001038C8(p))
  {
    float s = (-iosGetSinf(pitch)) * ctrl->x84;
    p->x154 = s;
    p->x15C = (ctrl->x80 + s) - p->x158;
    p->x160 = s - ((ctrl->x224 * ctrl->x224) * (ctrl->x8C + ctrl->x88));
  }
  else
  {
    p->x154 = 0.0f;
    p->x160 = -p->x158;
    p->x15C = ctrl->xB4 - p->x158;
  }
  z = 0.0f;
  p->x1A0 = z;
  if (ctrl->x74 > z)
  {
    f.q = p->obj->pos->q;
    scale3(&g, &YUnitVector, -ctrl->x74);
    vadd3(&g, &g, &f);
    g.v.w = 1.0f;
    if (ClipCollisionDirect(&hit, &f, &g, gcGlobalVar.x238))
    {
      p->x1A0 = f.v.y - hit.y;
    }
  }
  func_000FFB80(p);
  _initMovePathWork(p, &p->xC0, ctrl->x7C);
  if (_compPassagePos(p))
  {
    ctrl->x10 = *p->target;
    func_00103830(ctrl);
  }
  if ((ctrl->x3C == 1) && (p->x1C->x4 == ctrl->xD0))
  {
    ctrl->x3C = 2;
  }
  if (ctrl->x4 == 0)
  {
    ctrl->x10 = fltMaxVector;
  }
  else
    if ((((p->chr->x750 != ctrl->x64) && (p->x1C->x0 != ctrl->x200)) && (ctrl->x3C != 2)) && (p->target != 0))
  {
    if (!(p->x10 == 0))
    {
      if (p->chr->x750 == ctrl->x20)
      {
        goto flap;
      }
      else
        if (MotRootDyn_NOROOTDYNAMICS_POS_FREE == p->chr->x510)
      {
        int ok = func_000FFE48(&a, p);
        int flag = 0;
        float dd;
        float len;
        float dt;
        matVec(&b, p->mat, &a);
        if (ctrl->x40 == 0)
        {
          dd = CalcDistancePointAndLine(&a, &p->x110, &p->xE0);
          if ((dd <= p->xC0) && ok)
          {
            if (ctrl->x44 <= ctrl->x224)
            {
              ctrl->x44 = ctrl->x224;
              ctrl->x50.q = b.q;
            }
            else
              if (ctrl->x50.v.x != RO_00181440)
            {
              b.q = ctrl->x50.q;
              matVec(&a, p->inv, &b);
            }
          }
          else
            if (ctrl->x44 == 0.0f)
          {
            if (ok)
            {
              CalcFootVec(&c, &a, &p->x110, &p->xE0);
              scale3(&c, &c, (dd - p->xC0) / dd);
              vadd(&a, &a, &c);
              a.v.w = 1.0f;
            }
            matVec(&b, p->mat, &a);
            flag = 1;
            ctrl->x50.q = b.q;
          }
          else
          {
            b.q = ctrl->x50.q;
            matVec(&a, p->inv, &b);
            if (ctrl->x44 < ctrl->x224)
            {
              float h = p->x160 * 0.5f;
              float t = (ctrl->x224 - ctrl->x44) / p->x160;
              if (vdist(&b, p->obj->pos) < (((ctrl->x224 * t) + ((h * t) * t)) * 1.05f))
              {
                flag = 1;
              }
            }
          }
        }
        else
        {
          b.q = ctrl->x50.q;
          matVec(&a, p->inv, &b);
        }
        vsub(&c, &a, &p->x120);
        len = vlen(&c);
        scale3(&c, &c, 1.0f / len);
        dt = dot3(&c, &p->xE0);
        if ((((ctrl->x40 != 0) || (len < lay->x3CC)) || (dt <= 0.0f)) || (len < (ctrl->x224 + ctrl->x224)))
        {
          ctrl->x40 = 1;
          if (p->xC8 == 0)
          {
            func_001010F8(&p->x110, &p->xF0, flag, 1, 0, p);
          }
          else
          {
            func_001010F8(&p->x110, &p->x100, flag, 1, 0, p);
          }
        }
        else
        {
          vsub(&e, &p->x110, &a);
          normalize3(&e);
          vsub(&f, &a, &p->x120);
          normalize3(&f);
          if (dot3(&e, &p->xE0) < dot3(&f, &p->xE0))
          {
            d.q = f.q;
          }
          else
          {
            d.q = p->xE0.q;
          }
          func_001010F8(&a, &d, flag, 0, 0, p);
        }
      }
    }
    else
    {
      int r;
      if (lay->xE0 != 1)
      {
        setLockPassageWork(lay, 1);
      }
      r = chkAttainExecLayout(lay, &p->x130, p->obj, p->chr);
      if (r == 1)
      {
        ctrl->x60 = r;
      }
      if (((lay->xE0 == 0) && (p->chr->x750 == ctrl->x20)) && (ctrl->x60 != 0))
      {
        setLockPassageWork(lay, 0);
        func_001038E8(ctrl);
        forceSetWayFinish(lay);
      }
      else
        if ((p->chr->x750 == ctrl->x20) && (ctrl->x60 == 0))
      {
      flap:
        CharaCtrlSetScriptCtrlStatus(p->x8, ScriptCtrlDef_SCRFlapWing->x4);
      }
      else
        if (MotRootDyn_NOROOTDYNAMICS_POS_FREE == p->chr->x510)
      {
        if (lay->xA8 != 0)
        {
          matVec(&a, p->inv, &lay->xB0);
        }
        else
        {
          vsub(&a, &p->x130, &lay->x30);
          a.v.w = 1.0f;
          matVec(&a, p->inv, &a);
        }
        a.v.y = 0.0f;
        normalize3(&a);
        func_001010F8(&p->x110, &a, 0, 0, 1, p);
      }
    }
  }
  if (p->chr->x750 != ctrl->x64)
  {
    func_00101B58(p, ctrl->x64);
    ctrl->x1A8 = 0;
    ctrl->x1AC = 0;
  }
  else
  {
    func_00103030(p, ctrl->x64);
    ctrl->x1A8 = 1;
  }
  return 1;
}
#endif
