/* Parked: 10 diffs. is_sandwich's address registers (t1 before xa) and the result register (a0 vs v1) differ, so the final compare and return-1 reuse don't line up. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct 
{
  float x;
  float y;
  float z;
  float w;
} Vec4s __attribute__((aligned(8)));
typedef union 
{
  s128 q;
  float f[4];
} Vec4;
extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(void *, Vec4s *, float, Vec4s *);
extern int GAMEUTIL_act_pitch_rot(Vec4 *, Vec4 *, float, float, float, int);
inline static int rot_dir(Vec4 *out, Vec4 *cur, Vec4 *aim, int axis, float speed, float a, float b)
{
  Vec4s c = {cur->f[1], 0, cur->f[2], 0};
  Vec4s t = {aim->f[1], 0, aim->f[2], 0};
  int r;
  r = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(0, &c, 0.0f, &t);
  if (out != 0)
  {
    if (r == 0)
      out->q = cur->q;
    else
      if (r == 1)
      GAMEUTIL_act_pitch_rot(out, cur, speed, a, b, axis);
    else
      GAMEUTIL_act_pitch_rot(out, cur, -speed, a, b, axis);
  }
  return r;
}

inline static int is_sandwich(Vec4s *xa, Vec4s *xc, Vec4s *xb)
{
  Vec4 t1;
  Vec4 t2;
  Vec4 t3;
  int r;
__asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" "lqc2 vf06, 0x0(%2)\n" "vopmula.xyz ACC, vf05, vf06\n" "vopmsub.xyz vf07, vf06, vf05\n" "vsub.w vf07, vf07, vf07\n" "sqc2 vf07, 0x0(%0)\n" : : "r"(&t1), "r"(xb), "r"(xa) : "memory");
__asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" "lqc2 vf06, 0x0(%2)\n" "vopmula.xyz ACC, vf05, vf06\n" "vopmsub.xyz vf07, vf06, vf05\n" "vsub.w vf07, vf07, vf07\n" "sqc2 vf07, 0x0(%0)\n" : : "r"(&t2), "r"(xb), "r"(xc) : "memory");
  r = 0;
  if (t1.f[1] * t2.f[1] > 0.0f)
  {
__asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" "lqc2 vf06, 0x0(%2)\n" "vopmula.xyz ACC, vf05, vf06\n" "vopmsub.xyz vf07, vf06, vf05\n" "vsub.w vf07, vf07, vf07\n" "sqc2 vf07, 0x0(%0)\n" : : "r"(&t3), "r"(xa), "r"(xc) : "memory");
    r = (t2.f[1] * t3.f[1]) > 0.0f;
  }
  return r;
}

int GAMEUTIL_near_to_aim_pitch_dir(Vec4 *out, int *rot, Vec4 *cur, Vec4 *aim, int axis, float speed, float a, float b)
{
  Vec4 v;
  int r;
  v.q = cur->q;
  r = rot_dir(out, &v, aim, axis, speed, a, b);
  if (rot != 0)
  {
    *rot = r;
  }
  {
    Vec4s xa = {aim->f[1], 0, aim->f[2], 0};
    Vec4s xb = {v.f[1], 0, v.f[2], 0};
    Vec4s xc = {out->f[1], 0, out->f[2], 0};
    if (is_sandwich(&xa, &xc, &xb) != 1)
      return 0;
  }
  if (out)
    out->q = aim->q;
  return 1;
}
#endif
