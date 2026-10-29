extern void *GetSCRCharaAIWorkPtr(void *);
void nico_setHorseBridleObjToHorseWork(void *actor, void *bridle)
{
    *(void **)((char *)GetSCRCharaAIWorkPtr(actor) + 0x4248) = bridle;
}
