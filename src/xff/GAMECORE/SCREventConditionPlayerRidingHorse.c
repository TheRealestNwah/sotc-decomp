extern int *getSScriptWork(void *);
extern void *nico_GetPlayerCharacterRidingHorseObject(int);

int SCREventConditionPlayerRidingHorse(void *actor)
{
    int p = *getSScriptWork(actor);
    if (p == 0)
        return 0;
    return nico_GetPlayerCharacterRidingHorseObject(p) != 0;
}
