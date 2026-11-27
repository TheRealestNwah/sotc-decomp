/* Parked: 31 differing words, same size (was 105). Stick-input shaping step, the same body as func_0008F748 with other constants (+-1 / +-0.9 clamps, dead zone = arg * 2.5 degrees in radians): normalises each axis against the dead zone, raises the y ratio to 1.5 and interpolates x toward the dead-zone edge when its ratio is below, then calls func_0008E918. Remaining (as in func_0008F748): the prologue schedule and the final call's $f13 move order. */
#ifdef NONMATCHING
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern void func_0008E918(int, float, float, float, float);
extern float powf(float, float);

void func_0008F378(int arg0, float a, float b, float c, float d)
{
    float v[2];
    register float *p __asm__("$16") = v;
    register float cc __asm__("$f28") = c;
    register float dd __asm__("$f27") = d;
    register int ar __asm__("$17") = arg0;
    float rc = cc * 0.04363323003053665f;
    float rd = dd * 0.04363323003053665f;
    float maxA = 1.0f, minA = -1.0f, maxB = 0.9f, minB = -0.9f;
    float rb, ra;
    float r0;
    float nc = -rc, nd = -rd;

    v[1] = b;
    v[0] = a;
    if (maxA < a) maxA = a;
    if (a < minA) minA = a;
    if (maxB < b) maxB = b;
    if (b < minB) minB = b;
    if (0.0f <= b)
        r0 = GAMEUTIL_get_dist_ratio(b, rd, maxB);
    else
        r0 = 1.0f - GAMEUTIL_get_dist_ratio(b, minB, nd);
    rb = powf(r0, 1.5f);
    if (0.0f <= a)
        ra = 1.0f - GAMEUTIL_get_dist_ratio(a, rc, maxA);
    else
        ra = GAMEUTIL_get_dist_ratio(a, minA, nc);
    if (ra < rb) {
        if (0.0f <= a)
            *p = GAMEUTIL_get_interp_value(rc, a, rb - ra);
        else
            *p = GAMEUTIL_get_interp_value(nc, a, rb - ra);
    } else
        *p = a;
    v[1] = b;
    func_0008E918(ar, v[0], v[1], cc, dd);
}
#endif
