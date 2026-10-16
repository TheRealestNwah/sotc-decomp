extern int B_00065010;
extern int D_00040AF0;
extern void func_00013050(void);
extern unsigned int SignalSema(int sema);

void InitDL(void)
{
    volatile int *sema;
    volatile int *ready;

    func_00013050();
    sema = &B_00065010;
    SignalSema(*sema);
    ready = &D_00040AF0;
    *ready = 1;
}
