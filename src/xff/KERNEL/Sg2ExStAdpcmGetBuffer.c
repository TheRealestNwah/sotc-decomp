int Sg2ExStAdpcmGetBuffer(char *st, int *a, int *b, int *c, int *d)
{
    *a = *(int *)(st + 0x230);
    *b = *(int *)(st + 0x234);
    *c = *(int *)(st + 0x238);
    *d = *(int *)(st + 0x23C);
    return 0;
}
