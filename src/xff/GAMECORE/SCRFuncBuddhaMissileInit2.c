/* The pointer temporary for the constant was found by decomp-permuter;
   it changes the register allocation to match. */
extern char *GetSCRCharaAIWorkPtr(void *);
extern float RO_0017D130;

void SCRFuncBuddhaMissileInit2(void *actor)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    float *speed = (float *)(w + 0x41B4);
    float *src;

    *(int *)(w + 0x41BC) = 1;
    *speed = *(src = &RO_0017D130);
    *(int *)(w + 0x41B8) = 0;
    *(int *)(w + 0x41C0) = 0;
}
