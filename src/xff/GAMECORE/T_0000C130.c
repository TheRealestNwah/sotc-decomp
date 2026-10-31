extern char gcGlobalVar[];
extern void texTransResolve(void);
extern long iosGetTCountExtension(void);
extern float iosUsedPacketBufferSize(void);
extern int ptclCounterGet(void);
extern int ptclCounterInit(void);

static void T_0000C130(void)
{
    char *g;

    texTransResolve();
    g = gcGlobalVar;
    *(long *)(g + 0x18) = iosGetTCountExtension();
    *(float *)(g + 0x1C0) = iosUsedPacketBufferSize();
    *(int *)(g + 0x1C4) = ptclCounterGet();
    ptclCounterInit();
    *(long *)(g + 0x1B0) += 1;
}
