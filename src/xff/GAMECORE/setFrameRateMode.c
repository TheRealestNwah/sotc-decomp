extern long D_00179EB0;
extern long gcGlobalVar;
extern long iosGetTCount(void);
extern void func_0000C260(void);
void setFrameRateMode(void)
{
    long *p = &D_00179EB0;
    long t = iosGetTCount();
    *p = t;
    gcGlobalVar = t;
    func_0000C260();
}
