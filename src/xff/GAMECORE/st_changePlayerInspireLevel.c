extern void func_000128E0(int);
extern void *stagemanager_createsubthread(void *, void *, int);
void *st_changePlayerInspireLevel(int argument, int b, int c, int d)
{
    return stagemanager_createsubthread((void *)func_000128E0, (void *)argument, 0);
}
