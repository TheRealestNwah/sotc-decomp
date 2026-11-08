#ifdef NONMATCHING
/* Parked: 15 words differ (register allocation and float compare scheduling) */

extern float GAMEUTIL_get_dist_ratio(float, float, float);
static void func_000E26E8(float *a, float *b, float *v, char **pp, float fa, float fb)
{
  char *p = *pp;
  float xz;
  float y;
  if (((*((float *) (p + 0x68))) > 0.0f) && ((*((float *) (p + 0x80))) > 0.0f))
  {
 do { xz = (v[0] * v[0]) + (v[2] * v[2]); y = v[1] * v[1]; if ((xz > 0.0f) || (y > 0.0f)) { if (y < xz) { *b = GAMEUTIL_get_dist_ratio(y / xz, 0.5f, 1.0f) * fb; } else { *a = GAMEUTIL_get_dist_ratio(xz / y, 0.5f, 1.0f) * fa; } } } while (0);
  }
}
#endif
