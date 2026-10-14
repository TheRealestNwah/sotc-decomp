extern char *GetSCRCharaAIWorkPtr(int);
extern void nico_resetHorseBridleTerminalParentPoint(int);

void nico_resetHorseRidingStatusForHorse(int actor)
{
    int h = *(int *)(GetSCRCharaAIWorkPtr(actor) + 0x4248);

    if (h != 0) {
        nico_resetHorseBridleTerminalParentPoint(h);
    }
}
