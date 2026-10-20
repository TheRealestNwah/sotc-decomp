extern int D_0017A960;
extern int D_0017A964;
extern int D_0017A938;
extern void func_0002F770(void);
extern void func_0002EBE0(void);
void bgmScriptTickProc(void)
{
    D_0017A960 = D_0017A964 = 0;
    func_0002F770();
    if (D_0017A938 < 3)
        func_0002EBE0();
}
