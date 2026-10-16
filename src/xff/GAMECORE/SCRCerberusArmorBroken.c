extern char *GetSCRCharaAIWorkPtr(void *);
extern void _SCRStartLWS(int, int, int, int);

void SCRCerberusArmorBroken(void *a)
{
    char *ai = GetSCRCharaAIWorkPtr(a);

    _SCRStartLWS(*(int *)(ai + 0x41B0), -1, 4, 0);
    _SCRStartLWS(*(int *)(ai + 0x41C0), -1, 4, 0);
    _SCRStartLWS(*(int *)(ai + 0x41C4), -1, 4, 0);
    _SCRStartLWS(*(int *)(ai + 0x41B4), -1, 3, 0);
    _SCRStartLWS(*(int *)(ai + 0x41B8), -1, 3, 0);
    _SCRStartLWS(*(int *)(ai + 0x41BC), -1, 3, 0);
}
