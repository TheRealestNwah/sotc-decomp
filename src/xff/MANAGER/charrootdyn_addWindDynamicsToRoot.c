
typedef unsigned int s128 __attribute__((mode(TI)));
typedef union 
{
  float v[4];
  s128 q;
} Vec4;
extern void *GetGeometryPointerSurfacePlane(void *);
extern void GetPlaneFittingVector(void *, void *, void *);
inline static void scaleXYZ(Vec4 *out, Vec4 *a, float factor)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

inline static void lerp4(Vec4 *out, Vec4 *a, Vec4 *b, float t)
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

inline static void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

inline static float squareLength3(Vec4 *p)
{
  float result;
__asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(result) : "r"(p) : "$2");
  return result;
}

int charrootdyn_addWindDynamicsToRoot(char *chr, float power, float rate)
{
  Vec4 wind;
  float t;
  char *new_var;
  if ((*((signed char *) (chr + 0xC95))) != 0)
  {
    scaleXYZ(&wind, (Vec4 *) ((*((char **) (chr + 0x19C))) + 0x60), (rate * power) * (*((float *) ((*((char **) (chr + 0x1C0))) + 0x38))));
    if ((*((int *) (chr + 0x124))) != 0)
    {
      GetPlaneFittingVector(&wind, GetGeometryPointerSurfacePlane(chr + 0xC0), &wind);
    }
    *((signed char *) (chr + 0xC95)) = 0;
  }
  else
  {
__asm__ __volatile__("sq $0, 0x0(%0)" : : "r"(&wind) : "memory");
  }
  new_var = chr + 0x9D0;
  t = rate + rate;
  t = (1.0f <= t) ? (1.0f) : (t);
  lerp4((Vec4 *) new_var, &wind, (Vec4 *) (chr + 0x9D0), t);
  addXYZ(*((Vec4 **) (chr + 0x134)), *((Vec4 **) (chr + 0x134)), (Vec4 *) (chr + 0x9D0));
  return squareLength3((Vec4 *) (chr + 0x9D0)) > 9.99999902e-05f;
}
