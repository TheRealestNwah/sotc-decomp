/* Parked: 1000 diffs, same size (1332 words). Bird root-dynamics update: hovering approach (xC0/xD0 motions), dive arc (x154 == 3), hover (x3C == 2), landing turn (x200 motion) and free flight with yaw limits, then the XZ-stabilised and default root cases. Structure and every call match; the score is positional, from small scheduling and register-choice drift (block A tail loads p->obj before its branch to the end, and the first vector temporaries take a0/v0 where the Original uses v0/v1). The sp+0 matrix pointer is copied into a register through an empty asm, as the Original does. */
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
  char pad0[0x360];
  signed char x360;
  char pad361[0x4E4 - 0x361];
  float x4E4;
  char pad4E8[0x510 - 0x4E8];
  int x510;
  char pad514[0x9E0 - 0x514];
  Vec x9E0;
} Chr;
typedef struct
{
  char pad0[0x30];
  Vec x30;
  char pad40[0x134 - 0x40];
  Vec *pos;
  char pad138[4];
  Vec *quat;
} Obj;
typedef struct
{
  char *x0;
  char *x4;
  float x8;
  float xC;
} Pass;
typedef struct
{
  char pad0[0x3C];
  int x3C;
  char pad40[0x68 - 0x40];
  float x68;
  char pad6C[0x9C - 0x6C];
  float x9C;
  float xA0;
  float xA4;
  char padA8[8];
  float xB0;
  char padB4[0xC0 - 0xB4];
  char *xC0;
  char padC4[0xD0 - 0xC4];
  char *xD0;
  char padD4[0xF4 - 0xD4];
  float xF4;
  float xF8;
  char padFC[4];
  float x100;
  char pad104[0x110 - 0x104];
  Vec x110;
  Vec x120;
  float x130;
  float x134;
  float x138;
  char pad13C[4];
  Vec x140;
  float x150;
  int x154;
  char pad158[8];
  Vec x160;
  Vec x170;
  Vec x180;
  float x190;
  char pad194[0x1A0 - 0x194];
  float x1A0;
  char pad1A4[0x200 - 0x1A4];
  char *x200;
  char pad204[0x210 - 0x204];
  Vec x210;
  float x220;

  float x224;
  char pad228[4];
  float x22C;
  float x230;
  float x234;
  char pad238[8];
  Vec x240;
  Vec x250;
  Vec x260;
} Ctrl;
typedef struct
{
  char pad0[8];
  int x8;
  Vec *xC;
  char pad10[4];
  Chr *chr;
  Obj *obj;
  Pass *x1C;
  char pad20[0xCC - 0x20];
  Ctrl *ctrl;
  Vec xD0;
  char padE0[0x1A0 - 0xE0];
  float x1A0;
} Tmp;
typedef struct
{
  char pad0[0x190];
  float x190;
  float x194;
  char pad198[0x2B0 - 0x198];
  char x2B0[1];
} GcGlobal;
typedef struct
{
  int pad;
  int x4;
} ScriptDef;
extern int MotRootDyn_NOROOTDYNAMICS_POS_FREE;
extern int MotRootDyn_NOROOTDYNAMICS_VEL_XZSTAB;
extern ScriptDef *ScriptCtrlDef_SCRHovering;
extern Vec YUnitVector;
extern Vec ZUnitVector;
extern s128 IdentityQuaternion;
extern GcGlobal gcGlobalVar;
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void DivQuaternion(void *, void *, void *);
extern Obj *GetLayoutClass(int);
extern int SCRGetFirstObj(void *);
extern void GetLimitationQuaternion(void *, void *, float);
extern int GetMotionResourceFrames(void *);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void GetQuaternionByEulerYXZ(void *, float, float, float);
extern void GetStabYRotQuaternion(void *, void *);
extern float adjustAngleForLimit(float, float);
extern void analyzeMotionPropertyXZ(int, char *, float *, int, int, float, float);
extern void analyzeMotionProperty2XZ(int, char *, float *, int, int, float, float, float);
extern int func_001038C8(Tmp *);
extern float getRatioFromInterp(float, float);
extern void getTurnAndPitchFromDir(void *, float *, float *);
extern float getValueInterp(float, float, float, float);
extern float iosGetASinfExact(float);
extern float iosGetATan2fExact(float, float);

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

inline static float distXZ(void *a, void *b)
{
  float r;
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
  return r;
}

inline static void scale4(void *d, void *a, float s)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static void func_00101B58(Tmp *p)
{
  struct
  {
    Vec s0;
    Vec s10;
    Vec s20;
    Vec s30;
    Vec s40;
    Vec s50;
    Vec s60;
    Vec s70;
    Vec s80;
    Vec s90;
    Vec sA0;
    Vec sB0;
    Vec sC0;
    float sD0;
    float sD4;
    float sD8;
    float sDC;
    float sE0;
  } L;
  Chr *chr = p->chr;
  Ctrl *c = p->ctrl;
  char *m;
  float t;
  float d;
  float r;
  float a;
  float b;

  if (MotRootDyn_NOROOTDYNAMICS_POS_FREE == chr->x510)
  {
    m = p->x1C->x0;
    if (m == c->xC0 || m == c->xD0)
    {
      if (chr->x360)
      {
        float h = chr->x4E4;
        c->x150 = h;
        c->x110.q = p->obj->pos->q;
        c->x110.v.y -= h;
        analyzeMotionPropertyXZ(p->x8, p->x1C->x0, &c->x134, 0, 0, 1.0f, p->x1C->xC);
        c->x130 = 0;
        c->x138 = p->x1C->xC;
        c->x140.q = p->obj->quat->q;
      }
      if (p->xC == 0)
        goto end;
      {
        float one;
        vsub(&L.s20, p->xC, &c->x110);
        L.s20.v.y = 0;
        normalize3(&L.s20);
        one = 1.0f;
        L.s20.v.w = one;
        scale4(&L.s10, &L.s20, c->xF8);
        vadd3(&L.s0, p->xC, &L.s10);
        L.s0.v.w = one;
        c->x120.q = L.s0.q;
        c->x120.v.y += c->xF4;
        c->x130 += gcGlobalVar.x190;
        L.s40.q = p->obj->pos->q;
        L.s40.v.y -= c->x150;
        vsub(&L.s30, &L.s0, &L.s40);
        L.s30.v.y = 0;
        L.s30.v.w = one;
        normalize3(&L.s30);
        GetQuaternionByAxisDirZY(&L.s50, &L.s30, &YUnitVector);
        if (c->x130 < c->x100)
        {
          t = getRatioFromInterp(c->x100, c->x130);
          L.s60.q = c->x140.q;
          blend4(p->obj->quat, &L.s60, &L.s50, t);
          analyzeMotionPropertyXZ(p->x8, p->x1C->x0, &c->x134, 0, 0, one, p->x1C->xC);
          c->x110.q = L.s40.q;
          c->x138 = p->x1C->xC;
        }
        else if (c->x3C == 1)
        {
          Obj *o = GetLayoutClass(SCRGetFirstObj(gcGlobalVar.x2B0));
          vsub(&L.s30, o->pos, p->obj->pos);
          L.s30.v.w = one;
          L.s30.v.y = 0;
          normalize3(&L.s30);
          GetQuaternionByAxisDirZY(&L.s50, &L.s30, &YUnitVector);
          DivQuaternion(&L.s60, &L.s50, p->obj->quat);
          GetLimitationQuaternion(&L.s60, &L.s60, gcGlobalVar.x190 * 0.08726646f);
          quatMul3(p->obj->quat, p->obj->quat, &L.s60);
          normalize4(p->obj->quat);
        }
        else
        {
          p->obj->quat->q = L.s50.q;
        }
        unitRow(c->x260.f);
        c->x230 = 0;
        c->x240.q = IdentityQuaternion;
        d = vdist(&L.s0, &c->x110) / c->x134;
        if (c->x130 < c->x100)
        {
          L.s70.q = p->obj->pos->q;
          L.s70.v.y -= c->x150;
          unitRow(L.s60.f);
          L.s60.v.z = p->chr->x9E0.v.z * d;
          quatToMatrix(L.s80.f, p->obj->quat->f);
          unitRow(L.sB0.f);
          matVec(&L.s60, &L.s80, &L.s60);
          vadd3(p->obj->pos, &L.s70, &L.s60);
        }
        else
        {
          vsub(&L.sC0, &L.s0, &c->x110);
          normalize3(&L.sC0);
          L.sC0.v.w = 1.0f;
          analyzeMotionProperty2XZ(p->x8, p->x1C->x0, &L.sD0, 0, 0, 1.0f, c->x138, p->x1C->x8);
          L.sD0 *= d;
          scale3(&L.sC0, &L.sC0, L.sD0);
          vadd3(p->obj->pos, &c->x110, &L.sC0);
        }
        c->x150 = p->chr->x4E4;
        p->obj->pos->v.y += c->x150;
        c->x224 = d * vlen(&p->chr->x9E0) * gcGlobalVar.x194;
        goto end;
      }
    }
    else if (c->x154 == 3)
    {
      float zero = 0.0f;
      float span;
      float k;
      float k2;
      float one;
      float dy;
      c->x190 += gcGlobalVar.x190;
      c->x224 += c->x22C * gcGlobalVar.x190;
      if (c->x224 < zero)
        c->x224 = zero;
      span = distXZ(&c->x160, &c->x170);
      k = distXZ(&c->x160, p->obj->pos) / span;
      one = 1.0f;
      k *= k;
      if (one < k)
        k = one;
      if (c->x190 < c->x1A0)
      {
        dy = (p->obj->pos->v.y - c->x160.v.y) / k;
        vsub(&L.s10, p->obj->pos, &c->x160);
        L.s10.v.y = zero;
        normalize3(&L.s10);
        scale4(&L.s10, &L.s10, span);
        c->x170.v.x = c->x160.v.x + L.s10.v.x;
        c->x170.v.y = c->x160.v.y + dy;
        c->x170.v.z = c->x160.v.z + L.s10.v.z;
      }
      vsub(&L.s20, &c->x160, p->obj->pos);
      normalize3(&L.s20);
      getTurnAndPitchFromDir(&L.s20, &L.sD4, &L.sD8);
      quatDir(&L.s40, &p->xD0);
      scale3(&L.s40, &L.s40, c->x224 * gcGlobalVar.x190);
      vadd3(&L.s40, &L.s40, p->obj->pos);
      k2 = distXZ(&c->x160, &L.s40) / span;
      k2 *= k2;
      if (one < k2)
        k2 = one;
      L.s40.v.y = p->obj->pos->v.y - (c->x170.v.y - c->x160.v.y) * (k - k2);
      vsub(&L.s30, &L.s40, p->obj->pos);
      normalize3(&L.s30);
      getTurnAndPitchFromDir(&L.s30, &L.sDC, &L.sE0);
      GetQuaternionByEulerYXZ(&L.s0, L.sE0, L.sD4, zero);
      if (c->x190 < c->x1A0)
      {
        t = getRatioFromInterp(c->x1A0, c->x190);
        L.s50.q = c->x180.q;
        blend4(p->obj->quat, &L.s50, &L.s0, t);
      }
      else
      {
        p->obj->quat->q = L.s0.q;
      }
      quatDir(&L.s50, p->obj->quat);
      scale3(&L.s50, &L.s50, c->x224 * gcGlobalVar.x190);
      vadd3(p->obj->pos, p->obj->pos, &L.s50);
      unitRow(c->x260.f);
      c->x230 = 0;
      c->x240.q = IdentityQuaternion;
      goto end;
    }
    else if (c->x3C == 2)
    {
      CharaCtrlSetScriptCtrlStatus(p->x8, ScriptCtrlDef_SCRHovering->x4);
      c->x224 = 0;
      L.s0.q = p->chr->x9E0.q;
      L.s0.v.w = 1.0f;
      L.s0.v.z = 0;
      quatToMatrix(L.s10.f, p->obj->quat->f);
      unitRow(L.s40.f);
      matVec(&L.s0, &L.s10, &L.s0);
      vadd3(p->obj->pos, p->obj->pos, &L.s0);
      goto end;
    }
    else if (m == c->x200)
    {
      t = getRatioFromInterp((float)GetMotionResourceFrames(m + 0x50), p->x1C->x8);
      if (p->chr->x360)
      {
        c->x210.q = c->x250.q;
        c->x220 = c->x224;
      }
      quatDir(&L.s50, p->obj->quat);
      L.s50.v.y = 0;
      GetQuaternionByAxisDirZY(&L.s40, &L.s50, &YUnitVector);
      c->x224 = getValueInterp(c->x220, 0.0f, (float)GetMotionResourceFrames(p->x1C->x0 + 0x50), p->x1C->x8);
      L.s60.q = c->x210.q;
      blend4(p->obj->quat, &L.s60, &L.s40, t);
      { float *m0; __asm__("" : "=r"(m0) : "0"(L.s0.f)); quatToMatrix(m0, p->obj->quat->f); }
      unitRow(L.s30.f);
      unitRow(c->x260.f);
      c->x230 = 0;
      c->x240.q = IdentityQuaternion;
    }
    else
    {
      float lim = c->x9C * c->xA0;
      float ang;
      float zero;
      normalize4(&c->x240);
      L.s80.q = IdentityQuaternion;
      blend4(&L.s60, &L.s80, &c->x240, gcGlobalVar.x190);
      quatMul3(p->obj->quat, &p->xD0, &L.s60);
      normalize4(p->obj->quat);
      { float *m0; __asm__("" : "=r"(m0) : "0"(L.s0.f)); quatToMatrix(m0, p->obj->quat->f); }
      unitRow(L.s30.f);
      ang = 0;
      if (!func_001038C8(p))
      {
        quatDir(&L.s90, &c->x240);
        *(int *)&L.s90.v.y = 0;
        normalize3(&L.s90);
        ang = adjustAngleForLimit(iosGetATan2fExact(L.s90.v.x, L.s90.v.z) * c->xA0, c->xA4);
      }
      if (0 < p->x1A0 && 0 < c->x68 && p->x1A0 < c->x68)
      {
        float s = iosGetASinfExact(p->x1A0 / c->x68);
        ang = adjustAngleForLimit(ang, __builtin_fabsf(s));
      }
      zero = 0;
      a = adjustAngleForLimit(ang - c->x230, lim);
      c->x234 = a;
      a = adjustAngleForLimit(a, lim);
      c->x234 = a;
      c->x230 += a * gcGlobalVar.x190;
      b = adjustAngleForLimit(c->x230, c->xA4);
      c->x230 = b;
      GetQuaternionByEulerYXZ(&L.s70, zero, zero, -b);
      quatMul3(p->obj->quat, p->obj->quat, &L.s70);
      normalize4(p->obj->quat);
      c->x224 += c->x22C * gcGlobalVar.x190;
      if (c->x224 < zero)
        c->x224 = zero;
    }
    {
      float z;
      L.s80.q = p->chr->x9E0.q;
      z = L.s80.v.z;
      if (z < 0.0f)
      {
        z = 0.0f;
        L.s80.v.z = z;
      }
      L.s80.v.z = z * (c->xB0 * c->x224);
      scale3(&L.sA0, &ZUnitVector, c->x224 * gcGlobalVar.x190);
      vadd(&L.sA0, &L.sA0, &L.s80);
      L.sA0.v.w = 1.0f;
      matVec(&L.sA0, &L.s0, &L.sA0);
      vadd3(p->obj->pos, p->obj->pos, &L.sA0);
    }
  }
  else if (MotRootDyn_NOROOTDYNAMICS_VEL_XZSTAB == chr->x510)
  {
    GetStabYRotQuaternion(&L.s0, p->obj->quat);
    quatToMatrix(L.s10.f, L.s0.f);
    unitRow(L.s40.f);
    matVec(&L.s50, &L.s10, &p->chr->x9E0);
    vadd3(p->obj->pos, p->obj->pos, &L.s50);
    unitRow(p->obj->x30.f);
  }
  else
  {
    if (p->x1C->x4 == c->xC0 && p->chr->x360)
      p->obj->pos->q = c->x120.q;
    c->x224 = vlen(&p->chr->x9E0) * gcGlobalVar.x194;
    unitRow(c->x260.f);
  }
end:
  c->x250.q = p->obj->quat->q;
}
#endif
