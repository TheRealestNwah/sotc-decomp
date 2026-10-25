typedef int s128 __attribute__((mode(TI)));
extern s128 All1Vector;
extern void GetMotionNodeGeoToolCoord(void *, void *, void *, void *, int, int);

void GetGeometryPointerScale(s128 *out, int *g)
{
    s128 a, b;
    if (g[12] == 1)
        GetMotionNodeGeoToolCoord(&a, &b, out, (void *)g[0], g[1], 1);
    else
        *out = All1Vector;
}
