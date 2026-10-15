extern void func_000128E0(int arg);
extern int stagemanager_createsubthread();

int st_changePlayerInspireLevel(int a, int b, int c, int d)
{
    return stagemanager_createsubthread((int)func_000128E0, a, 0, d);
}
