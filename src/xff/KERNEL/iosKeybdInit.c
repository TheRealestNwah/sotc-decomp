extern int D_00040FBC;
extern void sceSifInitRpc(int mode);

/* The empty loop after the return (found by the permuter) gives the original
   epilogue order: s0 restored before ra. */
int iosKeybdInit(void)
{
    int *p = &D_00040FBC;

    *p = 0;
    sceSifInitRpc(0);
    return *p;
    do {
    } while (0);
}
