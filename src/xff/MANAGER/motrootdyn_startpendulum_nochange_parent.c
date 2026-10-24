extern void func_00069B70(void *, char *, void *);

void motrootdyn_startpendulum_nochange_parent(void *object, char *character, void *params)
{
    func_00069B70(object, character, params);
    *(int *)(character + 0x6D0) = 0;
}
