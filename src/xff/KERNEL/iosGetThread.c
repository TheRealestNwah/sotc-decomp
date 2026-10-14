extern int B_000516E0[];
extern int GetThreadId(void);
int iosGetThread(void)
{
    return B_000516E0[GetThreadId()];
}
