extern unsigned char *B_000C5C0C;
extern void (*control_change_ev[])(void);

static void func_00024EB8(void)
{
    control_change_ev[B_000C5C0C[1]]();
}
