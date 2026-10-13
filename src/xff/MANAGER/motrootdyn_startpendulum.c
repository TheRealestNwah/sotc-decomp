extern void func_00069B70(int, int, int);
extern void motrootdyn_startparentpointxzfit();

void motrootdyn_startpendulum(int arg0, int arg1, int arg2)
{
    motrootdyn_startparentpointxzfit();
    func_00069B70(arg0, arg1, arg2);
}
