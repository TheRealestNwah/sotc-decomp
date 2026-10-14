extern char B_00148CF0[];
extern void *D_00136C00;
extern void iosSprToMemDmaAdrCopy(void *, int, void *);

void LoopExecAfterLightColMan(void)
{
    iosSprToMemDmaAdrCopy(B_00148CF0, 0xBD, (void *)0x70000000);
    D_00136C00 = B_00148CF0;
}
