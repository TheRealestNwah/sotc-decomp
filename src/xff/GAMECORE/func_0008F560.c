/* Parked: 59 differing words (was 65: pinning c/d/p/arg0 to $f28/$f27/$s0/$s1 with `register ... asm` fixes the callee-saved assignment; remaining is float temp numbering and prologue scheduling) (c/d and s0/s1 register swaps, float scheduling).
   Siblings func_0008F748 and func_0008F930 have identical bodies.
   Permuter (40 min) found only semantics-changing variants. */
/* Parked: 65 differing words (c/d and s0/s1 register swaps, float scheduling).
   Siblings func_0008F748 and func_0008F930 have identical bodies.
   Permuter (40 min) found only semantics-changing variants. */
#ifdef NONMATCHING
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern void func_0008E918(int, float, float, float, float);
extern float powf(float, float);

void func_0008F560(int arg0, float a, float b, float c, float d)
{
    float v[2];
    register float *p __asm__("$16") = v;
    register float cc __asm__("$f28") = c;
    register float dd __asm__("$f27") = d;
    register int ar __asm__("$17") = arg0;
    float rc = cc * 0.0872664626f;
    float rd = dd * 0.0872664626f;
    float maxA = 1.2f, minA = -1.2f, maxB = 1.0f, minB = -1.0f;
    float rb, ra;
    float nc = -rc, nd = -rd;

    v[1] = b;
    v[0] = a;
    if (maxA < a) maxA = a;
    if (a < minA) minA = a;
    if (maxB < b) maxB = b;
    if (b < minB) minB = b;
    if (0.0f <= b)
        rb = GAMEUTIL_get_dist_ratio(b, rd, maxB);
    else
        rb = 1.0f - GAMEUTIL_get_dist_ratio(b, minB, nd);
    rb = powf(rb, 1.5f);
    if (0.0f <= a)
        ra = 1.0f - GAMEUTIL_get_dist_ratio(a, rc, maxA);
    else
        ra = GAMEUTIL_get_dist_ratio(a, minA, nc);
    if (ra < rb)
        *p = GAMEUTIL_get_interp_value(0.0f <= a ? rc : nc, a, rb - ra);
    else
        *p = a;
    v[1] = b;
    func_0008E918(ar, v[0], v[1], cc, dd);
}
#endif
