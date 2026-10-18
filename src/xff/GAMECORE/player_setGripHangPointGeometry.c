extern void *GetCharacterClass(void *);
extern void charrootdyn_setHColFindStatus(void *, int, float);
extern void charrootdyn_setVColFindFlag(void *, void *, float);
extern void charrootdyn_setFallDownLandingOffset(void *, void *);
static inline void setGripGeometry(void *character, char *geometry)
{
    float zero = 0.0f;
    charrootdyn_setHColFindStatus(character, (int)geometry, zero);
    charrootdyn_setVColFindFlag(character, geometry, zero);
    charrootdyn_setFallDownLandingOffset(character, geometry);
}
void player_setGripHangPointGeometry(void *actor, char *work)
{
    setGripGeometry(GetCharacterClass(actor), work + 0xB0);
}