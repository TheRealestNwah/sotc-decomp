extern void ExchangeGeometryPointerCollisionEdgeOtherSideInfo(void *, void *);
extern char *GetCharacterClass(void *);
extern void charrootdyn_setVColFindFlag(void *, void *, float);
extern void charrootdyn_resetVColEdgeFindFlag(void *);
extern void *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);
extern int AddTwoWayLinkNext(void *, void *);
extern void CopyGeometryPointer(void *, void *);

void player_setDangerEdgeOtherSidePlanePoint(void *obj, char *edge)
{
    char *gp = edge + 0x10;
    char *c;

    ExchangeGeometryPointerCollisionEdgeOtherSideInfo(gp, gp);
    c = GetCharacterClass(obj);
    charrootdyn_setVColFindFlag(c, gp, 0.0f);
    charrootdyn_resetVColEdgeFindFlag(c);
    AddTwoWayLinkNext(GetLayoutClass(GetGeometryPointerObject(gp)) + 0x118, c + 0xF60);
    *(int *)(c + 0xE70) = 1;
    CopyGeometryPointer(c + 0xE90, gp);
}
