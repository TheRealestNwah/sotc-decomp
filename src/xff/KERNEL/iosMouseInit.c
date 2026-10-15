extern int D_00040FC4;
extern void sceSifInitRpc(int mode);

/* The empty loop after the return gives the original order: the 0 return
   value is set before ra is restored. */
int iosMouseInit(void)
{
    D_00040FC4 = 0;
    sceSifInitRpc(0);
    return 0;
    do {
    } while (0);
}
