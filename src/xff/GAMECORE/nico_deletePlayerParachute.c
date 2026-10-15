extern char *GetSCRCharaAIWorkPtr(void *);
extern void unloadObj(void *);
extern void nico_ResetCharacterObjFallDownInfo(void *);

void nico_deletePlayerParachute(void *actor)
{
    void **p = (void **)(GetSCRCharaAIWorkPtr(actor) + 0x1C60);
    if (*p != 0) {
        unloadObj(*p);
        *p = 0;
    }
    nico_ResetCharacterObjFallDownInfo(actor);
}
