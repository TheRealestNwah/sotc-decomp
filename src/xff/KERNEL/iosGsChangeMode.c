extern short D_00040B30;
extern short D_00040B34;
extern short D_00040B38;
extern void sceGsResetGraph(int, int, int, int);
extern void func_00014948(void);

void iosGsChangeMode(void)
{
    int inter = D_00040B30;
    int mode = D_00040B34;
    int ffmd = D_00040B38;
    *(volatile long *)0x12001000 = 0x200;
    sceGsResetGraph(0, inter & 1, mode, ffmd & 1);
    func_00014948();
}
