extern void scrRun();
extern int D_00179FE8;

void CancelCaptionSubThreadAll(void)
{
    D_00179FE8 = 0;
    scrRun();
    D_00179FE8 = 1;
}
