extern void *GetSCRCharaAIWorkPtr(void *);
extern void nico_setHorseBridleTerminalParentPointIndep(void *, void *, int, const float *, int, const float *);
void nico_setHorseRidingStatusForHorseIndep(void *actor, void *parent, int firstNode, const float *firstPoint, int secondNode, const float *secondPoint)
{
    void *horse = *(void **)((char *)GetSCRCharaAIWorkPtr(actor) + 0x4248);
    if (horse)
        nico_setHorseBridleTerminalParentPointIndep(horse, parent, secondNode, secondPoint, firstNode, firstPoint);
}
