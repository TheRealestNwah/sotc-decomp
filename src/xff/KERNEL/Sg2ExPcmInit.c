extern int Sg2StPcmInit(int);
extern void Sg2ExPcmOutputCtrl(int);
extern void *memset(void *, int, unsigned int);
extern char B_000E2360[];
extern char B_000E2518[];

int Sg2ExPcmInit(int reserved)
{
    char *input;
    int i;

    Sg2StPcmInit(0);
    memset(B_000E2360, 0, 0x1B4);
    input = B_000E2518;
    for (i = 0; i < 4; ++i, input += 0x1D4) {
        *(int *)(input + 0x00) = 2;
        *(int *)(input + 0x1A0) = 0;
        *(int *)(input + 0x18) = 0;
        *(int *)(input + 0x1C) = 0;
        *(int *)(input + 0x34) = 0;
        *(int *)(input + 0x40) = 0;
        *(int *)(input + 0xDC) = 0;
        *(int *)(input + 0xE0) = 0;
        *(int *)(input + 0xF8) = 0;
        *(int *)(input + 0x104) = 0;
        *(int *)(input + 0x04) = 0;
        *(int *)(input + 0x0C) = 0;
        *(int *)(input + 0x14) = 0;
    }
    Sg2ExPcmOutputCtrl(2);
    return 0;
}

