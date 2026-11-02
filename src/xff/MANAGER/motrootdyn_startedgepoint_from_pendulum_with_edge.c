extern float ZeroPoint[];
extern void charrootdyn_updateCharacterClassParentGeometry(char *, float *, char *);
extern int charrootdyn_isParentToEdge(char *);
extern void ExchangeGeometryPointerCollisionEdgeOtherSideInfo(void *, void *);
extern void SetLayoutClassRootQuaternion(char *, void *);
extern void *GetGeometryPointerSurfacePlane(void *);
extern int charrootdyn_getCompleteFittingYQFromYDir(void *, void *, void *);
extern void func_000677B8(void *, int);
extern void charrootdyn_getLocalOffsetFromParentGP(void *, void *, int, void *);
extern void ForceUnparentLayoutObj(void *);

void motrootdyn_startedgepoint_from_pendulum_with_edge(void *self, char *p)
{
    char *geometry = p + 0xC0;
    void *quat = *(void **)(p + 0x13C);

    charrootdyn_updateCharacterClassParentGeometry(p, ZeroPoint, p + 0xC10);
    if (charrootdyn_isParentToEdge(p) != 0) {
        if (*(char *)(p + 0xC2A) != 0) {
            ExchangeGeometryPointerCollisionEdgeOtherSideInfo(geometry, geometry);
            SetLayoutClassRootQuaternion(p, *(void **)(p + 0x13C));
        }
        charrootdyn_getCompleteFittingYQFromYDir(quat, GetGeometryPointerSurfacePlane(geometry), quat);
        func_000677B8(p, 0);
        charrootdyn_getLocalOffsetFromParentGP(p + 0x6D0, quat, *(int *)(p + 0x134), geometry);
    } else {
        ForceUnparentLayoutObj(self);
    }
}
