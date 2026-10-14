extern void motrootdyn_parent_from_falldown();
extern void motrootdyn_startxzfit(int, int, int);

void motrootdyn_startxzfit_from_falldown(int arg0, int arg1, int arg2)
{
    motrootdyn_parent_from_falldown();
    motrootdyn_startxzfit(arg0, arg1, arg2);
}
