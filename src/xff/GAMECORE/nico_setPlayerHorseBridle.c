extern void *GetCharacterClass(void *);
extern void nico_setHorseRidingStatusForHorse(void *, void *, int, const float *, float);
extern int *SkelFocusDef_PLAYER_HAND_A_L;
extern const float RO_0017E250[];
static inline void *getHorse(void *actor)
{
    void *horse = *(void **)((char *)GetCharacterClass(actor) + 0x950);
    if (horse != actor && *(short *)((char *)GetCharacterClass(horse) + 0x370) == 3)
        return horse;
    return 0;
}
void nico_setPlayerHorseBridle(void *actor)
{
    void *horse = getHorse(actor);
    if (horse)
        nico_setHorseRidingStatusForHorse(horse, actor, SkelFocusDef_PLAYER_HAND_A_L[2], RO_0017E250, 0.035f);
}
