/* Parked: 20 diffs, same size (333 words). An empty clobber-free asm after GetDifferencialQuaternionWithNoRegularize and a clobber-free first quatToMatrix flush CSE so gcc recomputes the stack addresses like the Original; permuter temporaries (new_var/new_var2/new_var3) fixed the s4/s5 and s0/s1 choices. Remaining: the three static stores (D_00136B80/60/70) use different lui registers and order, and the sp+0x80 matrix address setup is scheduled differently around the identity-row sqc2; the second quatToMatrix stores through $s4 where the Original stores through a $v0 copy. */
#ifdef NONMATCHING

typedef int s128 __attribute__((mode(TI)));
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
inline static void quatAxisY(float *out, float *q)
{
__asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vaddy.z vf6, vf0, vf7y\n"
        "vsubw.z vf6, vf6, vf7w\n"
        "vsubx.y vf6, vf0, vf5x\n"
        "vsubz.y vf6, vf6, vf5z\n"
        "vaddz.x vf6, vf7, vf7z\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.y vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(q) : "memory");
}

inline static void quatAxisZ(float *out, float *q)
{
__asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
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
        ".set reorder\n"
        : : "r"(out), "r"(q) : "memory");
}

inline static void quatMul(float *out, float *a, float *b)
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

inline static void quatNormalize(float *out, float *in)
{
__asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

typedef float Vec4[4] __attribute__((aligned(16)));
extern void GetGeometryPointerPosition(void *, void *);
extern void *GetGeometryPointerSurfacePlane(void *);
extern int func_0005BF30(char *, int *, int, int, void *, float, float, float);
extern void GetPlaneFittingPoint(float *, void *, float *);
static Vec4 D_00136B60 = {0};
static Vec4 D_00136B70 = {0};
static Vec4 D_00136B80 = {0};
inline static void quatToMatrix(float *out, float *q)
{
__asm__ __volatile__(".set noreorder\n"
        "vaddw.xyz vf12, vf0, vf0w\n"
        "lqc2 vf11, 0x0(%0)\n"
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
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(q), "r"(out) : "memory");
}

inline static void quatToMatrixF(float *out, float *q)
{
__asm__ __volatile__(".set noreorder\n"
        "vaddw.xyz vf12, vf0, vf0w\n"
        "lqc2 vf11, 0x0(%0)\n"
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
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(q), "r"(out));
}

inline static void applyMatrix(float *out, float *m, float *v)
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

inline static void addXYZ(float *out, float *a, float *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

inline static void subXYZ(float *out, float *a, float *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

inline static void subXYZW(float *out, float *a, float *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

inline static void normalizeXYZ(float *out, float *a)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a) : "memory");
}

inline static void cross(float *out, float *a, float *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

int charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit_X(float *out, char *col, int *hit, void *gp, int p4, float *q, float x, float y, float z)
{
  float *new_var3;
  Vec4 p[2];
  Vec4 res[2];
  Vec4 s[2];
  float *new_var2;
  Vec4 pos;
  float *new_var;
  Vec4 t;
  Vec4 m[4];
  Vec4 dir;
  Vec4 az;
  Vec4 ax;
  Vec4 ay;
  Vec4 az2;
  Vec4 d;
  int tmp;
  void *plane;
  int i;
  plane = GetGeometryPointerSurfacePlane(gp);
  D_00136B60[0] = x;
  D_00136B80[2] = z;
  D_00136B70[1] = y;
  GetGeometryPointerPosition(pos, gp);
  quatToMatrixF((float *) m, q);
__asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(m[3]) : "memory");
  applyMatrix(t, (float *) m, D_00136B80);
  addXYZ(pos, pos, t);
  applyMatrix(t, (float *) m, D_00136B70);
  addXYZ(s[0], pos, t);
  subXYZ(s[1], pos, t);
  new_var3 = pos;
  applyMatrix(t, (float *) m, D_00136B60);
  addXYZ(p[0], new_var3, t);
  subXYZ(p[1], new_var3, t);
  {
    float *o = (float *) m;
    new_var2 = o;
    quatToMatrix(new_var2, q);
__asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(o), "r"(pos) : "memory");
  }
  for (i = 0; i < 2; i++)
  {
    char *c = col + (i * 0x50);
    hit[i] = func_0005BF30(c, &tmp, p4, (i * 2) + 1, m, x, y, z);
    if (hit[i])
    {
      *((s128 *) res[i]) = *((s128 *) (c + 0x40));
    }
    else
    {
      GetPlaneFittingPoint(res[i], plane, p[i]);
    }
  }

  subXYZW(dir, res[0], res[1]);
  normalizeXYZ(dir, dir);
  quatAxisZ(az, q);
  cross(ax, az, dir);
  normalizeXYZ(ax, ax);
  new_var = ay;
  quatAxisY(new_var, q);
  quatAxisZ(az2, q);
  GetDifferencialQuaternionWithNoRegularize(d, ax, new_var, az2);
__asm__ __volatile__("" : :);
  quatMul(out, d, q);
  quatNormalize(out, out);
  quatAxisY(new_var, out);
  return ay[1] < 0.0f;
}
#endif
