extern int iWakeupThread();

int iosiWakeupThread(int *p)
{
    return iWakeupThread(p[1]);
}
