extern void func_00069B70(void *a, char *b);

void motrootdyn_startpendulum_nochange_parent(void *a, char *b)
{
    func_00069B70(a, b);
    *(int *)(b + 0x6D0) = 0;
}
