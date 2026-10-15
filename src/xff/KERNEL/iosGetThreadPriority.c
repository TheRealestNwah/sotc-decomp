extern char *B_000516E0[];
extern int GetThreadId(void);

int iosGetThreadPriority(char *t)
{
    if (t == 0)
        t = B_000516E0[GetThreadId()];
    *(int *)(t + 0x14) = 0;
    return 0;
}
