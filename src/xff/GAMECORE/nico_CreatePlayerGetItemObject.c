extern char rootPtn[];
extern char gcGlobalVar[];
extern float IdentityQuaternion[];
extern float ZeroPoint[];
extern void SetGeometryPointerNodePosState(void *, void *, int, float *, float *);
extern void loadObj(void *, void *, void *, void *, int, int);

typedef struct {
    int a[4];
    int b[3];
    int c;
    void *geom;
    int d[2];
    int e;
    int f[3];
} LoadReq;

/* req.e is assigned twice: gcc keeps one store, but the duplicate gives the
   original store order. */
void nico_CreatePlayerGetItemObject(void *node, void *parent)
{
    char geom[0x40];
    LoadReq req;

    SetGeometryPointerNodePosState(geom, node, 0x10000, IdentityQuaternion, ZeroPoint);
    req.e = 1;
    req.a[0] = 0;
    req.a[1] = 0;
    req.a[2] = 0;
    req.a[3] = 0;
    req.geom = geom;
    req.b[0] = 0;
    req.b[1] = 0;
    req.b[2] = 0;
    req.c = 1;
    req.d[0] = 0;
    req.d[1] = 0;
    req.e = 1;
    req.f[0] = 0;
    req.f[1] = 0;
    req.f[2] = 0;
    loadObj(parent, &req, rootPtn, gcGlobalVar + 0x280, 0, 4);
}
