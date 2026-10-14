extern void *GetSCRCharaAIWorkPtr(void *);

void nico_playeGripholdOff(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x130)) = 0;
}
