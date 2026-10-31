extern char gcGlobalVar[];
extern long gpfinishctr;
extern long D_00179EC0;
extern long iosGetTCountExtension(void);

static void T_0000C180(void)
{
    char *g = gcGlobalVar;

    *(long *)(g + 0x20) = D_00179EC0;
    *(long *)(g + 0x28) = iosGetTCountExtension();
    gpfinishctr++;
}
