extern void func_000960C0();
extern void isysSleepSubThread();

void st_motionsyncanimation(void)
{
loop_1:
    func_000960C0();
    isysSleepSubThread();
    goto loop_1;
}
