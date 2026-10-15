typedef struct { int count; int max_count; int init_count; int wait_threads; int attr; int option; } SemaParam;
extern int CreateSema(SemaParam *);
extern void LoaderSysEntryExternalSemaList(int);

int iosCreateSema(int init, int max)
{
    SemaParam p;
    int s;
    p.init_count = init;
    p.max_count = max;
    s = CreateSema(&p);
    LoaderSysEntryExternalSemaList(s);
    return s;
}
