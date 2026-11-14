/* Parked: 164 diffs. Word count close (194 vs 197); original keeps &pts in s3, &ends in s7 and arg in fp (register rotation). */
#ifdef NONMATCHING
extern char *GetLayoutClass();
extern void func_000999E0(float **, int, char *, int, int);
extern void func_0009AE78(float **, int, char *, int, int, int, int, int);
extern int RO_001407D8[];

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

typedef struct {
    int obj;
    unsigned int packed;
    int edge;
} Edge;

typedef struct {
    int obj;
    unsigned int packed;
    int edge;
    float t;
    int arg;
    char pad[0x1C];
    int kind;
} Result;

void GetGeometryPointerWithCollisionEdgeGlobalPoint(Result *out, Edge *e, float *p, int arg)
{
    unsigned int packed = e->packed;
    int node = (packed >> 24) & 0x7F;
    int low = packed & 0xFFFFFF;
    int idx = e->edge;
    char *layout = GetLayoutClass(e->obj, packed);
    float *ends[2];
    float *pts[4];
    float *a;
    float *b;
    float dx, dy, dz;
    float t;

    if ((int)e->packed < 0) {
        func_000999E0(pts, 0, layout, node, low);
    } else {
        char *sh = layout + 0x154;
        char *res = *(char **)(sh + 0x20);
        char *q = *(char **)(*(char **)(layout + 0x184) + 0x20);
        func_0009AE78(pts, 0, res + 0x28, *(int *)(res + 0x24), *(int *)(sh + 8), *(int *)(q + 8),
                      *(int *)(q + 0x14),
                      *(int *)(q + 0x18) + (*(int **)(*(int *)(q + 8) + node * 0x90 + 0x54))[low] * 64);
    }
    ends[0] = pts[idx];
    ends[1] = pts[RO_001407D8[idx]];
    a = ends[0];
    b = ends[1];
    dx = a[0] - b[0];
    dy = a[1] - b[1];
    dz = a[2] - b[2];
    if (ABS(dy) < ABS(dx) && ABS(dz) < ABS(dx))
        t = (p[0] - b[0]) / dx;
    else if (ABS(dx) < ABS(dy) && ABS(dz) < ABS(dy))
        t = (p[1] - b[1]) / dy;
    else
        t = (p[2] - b[2]) / dz;
    out->obj = e->obj;
    out->packed = e->packed;
    out->arg = arg;
    out->kind = 4;
    out->edge = e->edge;
    out->t = t;
}
#endif
