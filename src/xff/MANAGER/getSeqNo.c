extern unsigned short D_00136BE0[];

int getSeqNo(void)
{
    unsigned short *p = D_00136BE0;

    return (*p)++;
}
