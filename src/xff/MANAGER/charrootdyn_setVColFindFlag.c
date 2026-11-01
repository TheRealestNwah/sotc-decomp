typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern Link ZeroVector;
extern int DeleteTwoWayLink(Link *);
extern void *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);
extern void AddTwoWayLinkNext(void *, Link *);
extern void CopyGeometryPointer(void *, void *);
extern void GetGeometryPointerSurfaceAttribute(long *, void *);
extern float GetGeometryPointerSurfaceSlopeDegree(void *, void *);

void charrootdyn_setVColFindFlag(char *p, void *gp, float f)
{
    long attr;
    float slope;

    if (*(int *)(p + 0xF3C) != 0) {
        *(int *)(p + 0xF3C) = 0;
        DeleteTwoWayLink((Link *)(p + 0xF30));
    }
    AddTwoWayLinkNext(GetLayoutClass(GetGeometryPointerObject(gp)) + 0x118, (Link *)(p + 0xF30));
    CopyGeometryPointer(p + 0xEF0, gp);
    *(int *)(p + 0xF3C) = 1;
    GetGeometryPointerSurfaceAttribute(&attr, gp);
    *(long *)(p + 0xF40) = attr;
    slope = GetGeometryPointerSurfaceSlopeDegree(gp, &ZeroVector);
    *(float *)(p + 0xF48) = f;
    *(float *)(p + 0xF4C) = slope;
}
