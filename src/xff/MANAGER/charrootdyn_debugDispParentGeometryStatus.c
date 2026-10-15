extern void GetGeometryPointerSurfacePlane(void *);
extern void GetCollisionDBLastPointOnCurrentPlane(float *, void *, int);

void charrootdyn_debugDispParentGeometryStatus(char *c)
{
    float p[4] __attribute__((aligned(16)));
    GetGeometryPointerSurfacePlane(c + 0xC0);
    GetCollisionDBLastPointOnCurrentPlane(p, c + 0xC0, *(int *)(c + 0x138));
}
