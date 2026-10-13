extern void scrRun();
extern int D_00179FF0;

void QuitCaptionSubThreadAll(void)
{
    D_00179FF0 = 1;
    scrRun();
    D_00179FF0 = 0;
}
