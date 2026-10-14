typedef int s128 __attribute__((mode(TI)));

void setPosGazeCtrlWork(char *p, s128 *v)
{
    *(s128 *)(p + 0x20) = *v;
    *(int *)(p + 0x30) = 0;
}
