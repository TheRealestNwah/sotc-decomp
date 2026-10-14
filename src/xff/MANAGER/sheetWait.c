extern void iosSleepThread();
extern int D_00139F1C;

void sheetWait(void)
{
    D_00139F1C = 1;
    iosSleepThread();
}
