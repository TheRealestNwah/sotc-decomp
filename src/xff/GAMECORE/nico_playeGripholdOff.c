extern void *GetSCRCharaAIWorkPtr();

void nico_playeGripholdOff(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x130)) = 0;
}
