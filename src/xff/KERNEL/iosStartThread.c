extern int *B_000516E0[];
extern int GetThreadId(void);
extern int StartThread(int, void *);

int iosStartThread(int *t, void *arg)
{
    if (t == 0)
        t = B_000516E0[GetThreadId()];
    return StartThread(t[1], arg);
}
