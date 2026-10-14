extern char B_0004E5B0[];
extern int iosSendMsg();

int iosWaitIdleThread(int a, int b, int c, int d)
{
    return iosSendMsg((int)B_0004E5B0, 0, 1, d);
}
