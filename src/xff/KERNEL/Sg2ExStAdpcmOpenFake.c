extern void *memset(void *, int, unsigned int);
extern int func_000200F0(char *);

int Sg2ExStAdpcmOpenFake(char *st)
{
    int *magic = (int *)(st + 0x28);
    if (*(int *)st != 0)
        return -3;
    if (*magic != 0x54535845)
        return -1;
    *(int *)(st + 0x2D4) = 0;
    *(int *)(st + 0x248) = 0;
    *(long *)(st + 0xA0) = 0;
    *(int *)(st + 0x228) = 0;
    *(int *)(st + 0x22C) = 0;
    memset(st + 0xA8, 0, 0x180);
    *(int *)(st + 8) = *(int *)(st + 0xC);
    if (func_000200F0(st))
        return -2;
    return 0;
}
