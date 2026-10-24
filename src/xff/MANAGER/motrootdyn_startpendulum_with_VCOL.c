extern int ParentLayoutObj(void *, char *);
extern int motrootdyn_startparentpointxzfit(int, int, int);
extern void func_00069B70(void *, char *, void *);

void motrootdyn_startpendulum_with_VCOL(void *object, char *character, void *params)
{
    if (*(int *)(character + 0xF3C) != 0) {
        ParentLayoutObj(object, character + 0xEF0);
        func_00069B70(object, character, params);
        *(int *)(character + 0x6D0) = 0;
    } else {
        motrootdyn_startparentpointxzfit((int)object, (int)character, (int)params);
        func_00069B70(object, character, params);
    }
}
