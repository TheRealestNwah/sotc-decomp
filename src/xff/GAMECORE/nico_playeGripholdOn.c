extern void *GetSCRCharaAIWorkPtr(void *);

void nico_playeGripholdOn(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x130)) = 1;
}
