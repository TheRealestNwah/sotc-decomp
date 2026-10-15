extern char *GetCharacterClass(void *);
extern void charrootdyn_setHColFindStatus(char *, char *, float);
extern void charrootdyn_setVColFindFlag(char *, char *, float);
extern void CopyGeometryPointer(char *, char *);
extern void charrootdyn_setFallDownLandingOffset(char *, char *);

static inline void setHang(char *c, char *g)
{
    float z = 0.0f;
    charrootdyn_setHColFindStatus(c, g, z);
    charrootdyn_setVColFindFlag(c, g, z);
    CopyGeometryPointer(c + 0xE90, g);
    *(int *)(c + 0xE70) = 1;
    charrootdyn_setFallDownLandingOffset(c, g);
}

void player_setEdgeHangPointGeometry(void *a, char *b)
{
    setHang(GetCharacterClass(a), b + 0x70);
}
