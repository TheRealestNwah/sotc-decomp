extern char *GetSCRCharaAIWorkPtr(void *);
extern void _SCRStartLWS(int, int, int, void *);

int torchExtinguished(void *a)
{
    char *w = GetSCRCharaAIWorkPtr(a);
    if (*(int *)(w + 0x8C) != 0) {
        _SCRStartLWS(*(int *)(w + 0x8C), -1, 3, w + 0x90);
        w[0x95] = 1;
        *(int *)(w + 0x88) = 0;
    }
}
