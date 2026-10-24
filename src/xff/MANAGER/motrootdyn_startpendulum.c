extern void func_00069B70(void *, char *, void *);
extern int motrootdyn_startparentpointxzfit(int, int, int);

void motrootdyn_startpendulum(void *object, char *character, void *params)
{
    motrootdyn_startparentpointxzfit((int)object, (int)character, (int)params);
    func_00069B70(object, character, params);
}
