extern char *GetCharacterClass(void *);
extern void charrootdyn_setVColFindFlag(char *, char *, float);
extern void charrootdyn_resetVColEdgeFindFlag(char *);
extern void *GetGeometryPointerObject(char *);
extern char *GetLayoutClass(void *);
extern int AddTwoWayLinkNext(char *, char *);
extern void CopyGeometryPointer(char *, char *);

void player_setDangerEdgePoint(void *a, char *b)
{
    char *g = b + 0x10;
    char *c = GetCharacterClass(a);
    charrootdyn_setVColFindFlag(c, g, 0.0f);
    charrootdyn_resetVColEdgeFindFlag(c);
    AddTwoWayLinkNext(GetLayoutClass(GetGeometryPointerObject(g)) + 0x118, c + 0xF60);
    *(int *)(c + 0xE70) = 1;
    CopyGeometryPointer(c + 0xE90, g);
}
