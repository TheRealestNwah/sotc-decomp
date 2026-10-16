typedef int s128 __attribute__((mode(TI)));

extern char *GetSCRCharaAIWorkPtr(void *);

void sendArrowPos(s128 *out, void *a)
{
    *out = *(s128 *)(GetSCRCharaAIWorkPtr(a) + 0x10);
}
