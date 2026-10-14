extern void *GetSCRCharaAIWorkPtr(void *);
extern void nico_setHorseBridleTerminalParentPoint(void *, void *, int, const float *, float);

void nico_setHorseRidingStatusForHorse(void *actor, void *parent, int node, const float *point, float span)
{
    void *horse;

    horse = *(void **)((char *)GetSCRCharaAIWorkPtr(actor) + 0x4248);
    if (horse != 0) {
        nico_setHorseBridleTerminalParentPoint(horse, parent, node, point, span);
    }
}
