extern char B_000C0710[];
extern int iosSendMsg();

int waitVscheduler(int a, int b, int c, int d)
{
    return iosSendMsg((int)B_000C0710, 0, 1, d);
}
