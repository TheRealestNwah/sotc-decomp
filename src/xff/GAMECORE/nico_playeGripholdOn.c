extern void *GetSCRCharaAIWorkPtr();

void nico_playeGripholdOn(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x130)) = 1;
}
