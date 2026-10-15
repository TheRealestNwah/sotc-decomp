extern void GetGeometryPointerPosition(float *, void *);

int checkdist(float *d, void *g)
{
    float p[4] __attribute__((aligned(16)));
    float y;
    GetGeometryPointerPosition(p, g);
    y = -p[1];
    if (y < *d) {
        *d = y;
        return 1;
    }
    return 0;
}
